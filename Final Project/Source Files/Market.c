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

void swapResults(StockResult* a, StockResult* b) {
    StockResult temp = *a;
    *a = *b;
    *b = temp;
}

void sortResultsByprecentege(StockResult* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].precentege < arr[j + 1].precentege) {
                swapResults(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int findStockIndexByID(Market* market, int searchID) {
    int left = 0;
    int right = market->numStocks - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (market->stocks[mid].id == searchID) return mid;
        if (market->stocks[mid].id < searchID) left = mid + 1;
        else right = mid - 1;
        
    }
    return -1;
}

void showMarketStatus(Market* market, double currentTime) {
    if (!market) return;

    system("cls");
    printf("STOCK MARKET SIMULATION - Time: %.2f \n\n", currentTime,market->cash);
    printf("%-10s %-15s %-10s\n", "Symbol", "Id", "Price");

    for (int i = 0; i < market->numStocks; i++) {
        Stock* s = &market->stocks[i];
        printf("%-10s %-15d %-10.2f\n", s->symbol, s->id, s->currentPrice);
    }
}

void printPortfolio(Market* market) {
    printf("\n    YOUR CURRENT Holdings    ");
    printf("\n%-10s | %-15s | %-10s", "Symbol", "Amount Owned", "Market Value");
    for (int i = 0; i < market->numStocks; i++) {
        double value = market->ownedAmount[i] * market->stocks[i].currentPrice;
        printf("\n%-10s | %-15d | %-10.2f",
            market->stocks[i].symbol,
            market->ownedAmount[i],
            value);
    }
    printf("\nAvailable Cash: %.2f", market->cash);
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
	system("cls");
    if (!market || market->historyCols == 0) return;

    int n = market->numStocks;
    StockResult* results = (StockResult*)malloc(n * sizeof(StockResult));
    assert(results);

    int lastCol = market->historyCols - 1;

    for (int i = 0; i < n; i++) {
        double First = market->priceHistory[i][0];
        double Last = market->priceHistory[i][lastCol];

        strcpy(results[i].symbol, market->stocks[i].symbol);
        results[i].precentege = ((Last - First) / First) * 100.0;
    }

    sortResultsByprecentege(results, n);

    printf("\nFINAL MARKET PERFORMANCE REPORT (Sorted by Precentege)\n");
    printf("%-12s | %-10s\n", "Symbol", "(%)");
    for (int i = 0; i < n; i++) {
        printf("%-12s | %+.2f%%\n", results[i].symbol, results[i].precentege);
    }

    printf("\n");
    free(results);;
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

