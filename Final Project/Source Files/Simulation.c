#include "Defines.h"
#include "Simulation.h"
#include "Market.h"


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

void insertEvent(Event** head, double time, int type, int stockID, int amount) {

	Event* newEvent = (Event*)malloc(sizeof(Event));
	assert(newEvent);

	newEvent->eventTime = time;
	newEvent->type = type;
	newEvent->stockID = stockID;
    newEvent->amount = amount; 
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

void freeEvents(Event* head){
	Event* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

}

void processPriceUpdate(Market* market, int stockID, double time, Event** head, FILE* logFile) {
    Stock* s = &market->stocks[stockID];

    // new price
    double changePercent = ((rand() % 4001) - 2000) / 100000.0;
    double oldPrice = s->currentPrice;
    s->currentPrice *= (1 + changePercent);

    // 2. Log
    if (logFile) {
        fprintf(logFile, "[Time %.2f] Stock %s: Price changed from %.2f to %.2lf\n",
            time, s->symbol, oldPrice, s->currentPrice);
    }

    // 3. Rescheduling

    double nextUpdateTime = time + (rand() % 10 + 1);
    insertEvent(head, nextUpdateTime, PRICE_UPDATE, stockID, 0);
}

void processTrade(Market* market, int stockID, double time, int amount, int isBuy, FILE* logFile) {
    Stock* s = &market->stocks[stockID];
    double totalCost = amount * s->currentPrice;

    if (isBuy) {
        if (market->cash >= totalCost) {
            market->cash -= totalCost;
			market->ownedAmount[stockID] += amount;

            printf("SUCCESS: Bought %d shares of %s at %.2f\n", amount, s->symbol, s->currentPrice);
            if (logFile) {
                fprintf(logFile, "[Time %.2f] BUY SUCCESS: %d %s for total %.2f. Remaining cash: %.2f\n",
                    time, amount, s->symbol, totalCost, market->cash);
            }
        }
        else {
            printf("REJECTED: Not enough cash to buy %d shares of %s\n", amount, s->symbol);
            if (logFile) {
                fprintf(logFile, "[Time %.2f] BUY FAILED: Insufficient funds for %d %s\n", time, amount, s->symbol);
            }
        }
    }
    else {
        if (market->ownedAmount[stockID] >= amount) {
            market->cash += totalCost;
            market->ownedAmount[stockID] -= amount;

            printf("SUCCESS: Sold %d shares of %s at %.2f\n", amount, s->symbol, s->currentPrice);
            if (logFile) {
                fprintf(logFile, "[Time %.2f] SELL SUCCESS: %d %s for total %.2f. New cash: %.2f\n",
                    time, amount, s->symbol, totalCost, market->cash);
            }
        }
        else {
            printf("REJECTED: You don't own %d shares of %s to sell\n", amount, s->symbol);
            if (logFile) {
                fprintf(logFile, "[Time %.2f] SELL FAILED: Not enough shares of %s\n", time, s->symbol);
            }
        }
    }
}

void handleEvent(Market* market, Event* event, Event** head, FILE* logFile) {
    if (event == NULL) return;

    switch (event->type) {
    case PRICE_UPDATE:
        processPriceUpdate(market, event->stockID, event->eventTime, head, logFile);
        recordPriceHistory(market);
        break;

    case BUY_ORDER:
        processTrade(market, event->stockID, event->eventTime, event->amount, 1, logFile);
        break;

    case SELL_ORDER:
        processTrade(market, event->stockID, event->eventTime, event->amount, 0, logFile);
        break;

    default:
        printf("Unknown event type %d\n", event->type);
    }

    free(event);
}

