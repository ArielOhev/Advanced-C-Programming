#ifndef DEFINES_H
#define DEFINES_H

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_SYMBOL 10       
#define MAX_TIME 100.0      
#define INITIAL_CASH 10000

#define PRICE_UPDATE 1
#define TRADE_ORDER 2


// 1. Single stock representation
typedef struct {
    char symbol[MAX_SYMBOL]; 
    double currentPrice;     
    int id;                  
} Stock;

// 2. Shared event structure for both price updates and trade orders
typedef struct Event {
    double eventTime;        
    int type;                
    int stockID;             
    int amount;              
    struct Event* next;      
} Event;

// 3. market structure to hold stocks, cash, and owned amounts
typedef struct {
    Stock* stocks;          
    int numStocks;           
    double cash;             
    int* ownedAmount;        


    double** priceHistory;
    int historyCols;
} Market;

#endif