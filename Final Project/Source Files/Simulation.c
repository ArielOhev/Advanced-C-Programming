#include "Defines.h"


void printEvents(Event* head) {
    printf("--- Current FEL Schedule ---\n");
    Event* temp = head;
    while (temp != NULL) {
        printf("[Time: %.2f | Type: %d | StockID: %d] -> ",
            temp->eventTime, temp->type, temp->stockID);
        temp = temp->next;
    }
    printf("NULL\n---------------------------\n");
}

void insertEvent(Event** head, double time, int type, int stockID) {

	Event* newEvent = (Event*)malloc(sizeof(Event));
	assert(newEvent);

	newEvent->eventTime = time;
	newEvent->type = type;
	newEvent->stockID = stockID;
	newEvent->next = NULL;

    if (*head == NULL || time < (*head)->eventTime) {
        newEvent->next = *head;
        *head = newEvent;       
        return;
    }

    Event* current = *head;
    while (current->next != NULL && current->next->eventTime < time) {
        current = current->next;
    }

    newEvent->next = current->next;
    current->next = newEvent;


}

Event* popEvent(Event** head) {
    if (*head == NULL) {
        return NULL;
    }

    Event* temp = *head;
    *head = (*head)->next;
    temp->next = NULL;

    return temp;
}