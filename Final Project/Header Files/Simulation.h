#ifndef SIMULATION_H
#define SIMULATION_H

#include "Defines.h"

/* * Adds a new event to the list in chronological order.
 * Parameters: head (list start), time, type, stockID.
 */
void insertEvent(Event** head, double time, int type, int stockID);

/* * Removes and returns the earliest event from the list.
 * Returns: Pointer to the event. Caller must free memory.
 */
Event* popEvent(Event** head);

/* * Prints all scheduled events in the list for debugging.
 */
void printEvents(Event* head);

/* * Frees all memory allocated for events in the list.
 */
void freeEvents(Event* head);

#endif