#ifndef SIMULATION_H
#define SIMULATION_H

#include "Defines.h"

/* * Adds a new event to the list.
 * Parameters:
 * head: The address of the list pointer.
 * time: The specific virtual time when this event is scheduled to occur.
 * type: The category of the event.
 * stockID: The unique index of the stock this event refers to.
 * amount: The number of shares involved in a trade event.
 */
void insertEvent(Event** head, double time, int type, int stockID, int amount);


/* * Removes and returns the first event from the list.
 * Parameters:
 * head: The address of the list pointer.
 * Return: A pointer to the Event structure.
 */
Event* popEvent(Event** head);



/* * Prints all scheduled events in the list for debugging.
 * Parameters:
 * head: A pointer to the beginning of the event list.
 */
void printEvents(Event* head);



/* * Frees all memory allocated for events in the list.
 * Parameters:
 * head: A pointer to the first event in the list to begin the cleanup process.
 */
void freeEvents(Event* head);


/* * Updates a stock's price with a random time and schedules the next update.
 * Parameters:
 * - market: Pointer to the market data structure.
 * - stockID: The ID of the stock to be updated.
 * - time: The current virtual time of the simulation.
 * - head: Double pointer to the event list for rescheduling.
 * - logFile: Pointer to the output file for logging price changes.
 */
void processPriceUpdate(Market* market, int stockID, double time, Event** head, FILE* logFile);


/* * Handles the execution of a stock transaction (Buy or Sell).
 * * Parameters:
 * market:  A pointer to the central Market structure. T
 * stockID: The unique index (ID) of the stock. 
 * time: The current virtual simulation time.
 * amount: The number of shares the user intends to trade in this transaction.
 * isBuy: A logic flag used to determine the transaction.
 * logFile: A pointer to the open simulation log file.
 */
void processTrade(Market* market, int stockID, double time, int amount, int isBuy, FILE* logFile);


/* * The Central Manager: Routes the event to the correct handler based on type.
 * Parameters:
 * market: Pointer to the central market structure containing stocks and cash.
 * event: Pointer to the specific event currently being executed.
 * head: The address of the list pointer, required for scheduling future events.
 * logFile: The file stream where the simulation history will be saved.
 */
void handleEvent(Market* market, Event* event, Event** head, FILE* logFile);







#endif