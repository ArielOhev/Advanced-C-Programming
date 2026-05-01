#include "Defines.h"
#include "Market.h"
#include "Simulation.h"

int main() {

	//Open log file for writing
    FILE* logFile = fopen("simulation_log.txt", "w");

    Market* market = initMarket("stocks.txt");
    Event* eventList = NULL;
    double maxSimulationTime = MAX_TIME; 
    double currentTime = 0.0;

	// Schedule first price updates for all stocks
    for (int i = 0; i < market->numStocks; i++) {
        insertEvent(&eventList, 0.0, PRICE_UPDATE,i,0);
    }

	// start user menu at 10.0 seconds
    insertEvent(&eventList, 10.0, USER_MENU, 0, 0);

	//start simulation loop
    printf("\nSimulation Started\n");
    while (eventList != NULL && currentTime < maxSimulationTime) {

        Event* currentEvent = popEvent(&eventList);
        currentTime = currentEvent->eventTime;
        handleEvent(market, currentEvent, &eventList, logFile);
        showMarketStatus(market, currentTime);


        Sleep(500);
    }

	// End of simulation
    printf("\nSimulation reached Max Time. Cleaning up...\n");
	printMarketHistory(market);

	freeMarket(market);
    freeEvents(eventList);
    fclose(logFile);

    return 0;
}