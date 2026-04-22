#include "Defines.h"
#include "Market.h"
#include "Simulation.h"

int main() {

    FILE* logFile = fopen("simulation_log.txt", "w");
    double maxSimulationTime = 100.0; 
    double currentTime = 0.0;

    Market* market = initMarket("stocks.txt");

    Event* eventList = NULL;
    for (int i = 0; i < market->numStocks; i++) {
        insertEvent(&eventList, 0.0, PRICE_UPDATE,0,i);
    }

    printf("\nSimulation Started\n");

    insertEvent(&eventList, 5.0, BUY_ORDER, 0, 10);
    insertEvent(&eventList, 15.0, SELL_ORDER, 0, 5);
    insertEvent(&eventList, 20.0, BUY_ORDER, 1, 999999);

    while (eventList != NULL && currentTime < maxSimulationTime) {

        Event* currentEvent = popEvent(&eventList);
        currentTime = currentEvent->eventTime;
        handleEvent(market, currentEvent, &eventList, logFile);
        showMarketStatus(market, currentTime);


        Sleep(500);
    }

    printf("\nSimulation reached Max Time. Cleaning up...\n");
	printMarketHistory(market);

	freeMarket(market);
    freeEvents(eventList);
    fclose(logFile);

    return 0;
}