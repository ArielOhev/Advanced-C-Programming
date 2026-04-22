#ifndef MARKET_H
#define MARKET_H

#include "Defines.h"



/* * Initializes the market structure by reading the stock file.
 * Parameters:
 * fileName: The name of the text file containing stock data.
 * Return: A pointer to the initialized Market structure.
 */
Market* initMarket(char* fileName);

/* * Displays a formatted table of the current market prices and user assets.
 * Parameters:
 * market: Pointer to the market data structure.
 * currentTime: The current virtual time of the simulation.
 */
void showMarketStatus(Market* market, double currentTime);


/* * Archives current stock prices into a dynamic 2D history matrix.
 * Parameters:
 * market: Pointer to the market structure containing the prices and the matrix.
 */
void recordPriceHistory(Market* market);


/* * Prints a complete chronological report of price changes for all stocks.
 * Parameters:
 * market: Pointer to the market structure containing the archived history.
 */
void printMarketHistory(Market* market);


/* * Frees each row of the matrix.
 * Parameters:
 * market: Pointer to the market structure to be deallocated.
 */
void freeMarket(Market* market);

#endif