#include "Defines.h"


// Function to initialize the market from a file
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

    fclose(file);
    return market;
}