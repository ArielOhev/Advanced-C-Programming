#include "Defines.h"


Market* initMarket(char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", fileName);
        return NULL;
    }

    Market* market = (Market*)malloc(sizeof(Market));
    assert(market);

    fscanf(file, "%d", &(market->numStocks));

    market->cash = INITIAL_CASH;
    market->stocks = (Stock*)malloc(market->numStocks * sizeof(Stock));
	assert(market->stocks);

    market->ownedAmount = (int*)calloc(market->numStocks, sizeof(int));
	assert(market->ownedAmount);


    for (int i = 0; i < market->numStocks; i++) {
        fscanf(file, "%s %lf", market->stocks[i].symbol, &(market->stocks[i].currentPrice));
        market->stocks[i].id = i;
    }

    market->historyCapacity = 5;
    market->historyCols = 0;
    market->priceHistory = (double**)malloc(market->numStocks * sizeof(double*));
	assert(market->priceHistory);

    for (int i = 0; i < market->numStocks; i++) {
        market->priceHistory[i] = (double*)malloc(market->historyCapacity * sizeof(double));
		assert(market->priceHistory[i]);
        market->priceHistory[i][0] = market->stocks[i].currentPrice;
    }
    market->historyCols = 1;

    fclose(file);
    return market;
}

void showMarketStatus(Market* market, double currentTime) {
    if (!market) return;

    system("cls");
    printf("==========================================\n");
    printf("   STOCK MARKET SIMULATION - Time: %.2f\n", currentTime);
    printf("==========================================\n");
    printf("%-10s %-15s %-10s\n", "Symbol", "Id", "Price");
    printf("------------------------------------------\n");

    for (int i = 0; i < market->numStocks; i++) {
        Stock* s = &market->stocks[i];
        printf("%-10s %-15d %-10.2f\n", s->symbol, s->id, s->currentPrice);
    }
    printf("==========================================\n");
}

void recordPriceHistory(Market* market) {

    if (market->historyCols >= market->historyCapacity) {
        int newCapacity = market->historyCapacity * 2;

        for (int i = 0; i < market->numStocks; i++) {
            double* temp = (double*)realloc(market->priceHistory[i], newCapacity * sizeof(double));

            if (temp == NULL) {
                printf("Error\n");
                return;
            }
            market->priceHistory[i] = temp;
        }
        market->historyCapacity = newCapacity;
        printf(">> The new price is: %d\n", newCapacity);
    }

    for (int i = 0; i < market->numStocks; i++) {
        market->priceHistory[i][market->historyCols] = market->stocks[i].currentPrice;
    }

    market->historyCols++;
}

void printMarketHistory(Market* market) {
    printf("\n--- FINAL PRICE HISTORY REPORT ---\n");
    printf("Time Step | ");
    for (int i = 0; i < market->numStocks; i++) {
        printf("%s\t", market->stocks[i].symbol);
    }
    printf("\n----------------------------------\n");

    for (int j = 0; j < market->historyCols; j++) {
        printf("Step %d:   | ", j);
        for (int i = 0; i < market->numStocks; i++) {
            printf("%.2f\t", market->priceHistory[i][j]);
        }
        printf("\n");
    }
}

void freeMarket(Market* market) {
    if (!market) return;

    for (int i = 0; i < market->numStocks; i++) {
        free(market->priceHistory[i]);
    }

    free(market->priceHistory);
    free(market->ownedAmount);
    free(market->stocks);
    free(market);

    printf(">> System: All memory cleared successfully.\n");
}