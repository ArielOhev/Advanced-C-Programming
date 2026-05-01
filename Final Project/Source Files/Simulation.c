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

    // 1. new price
    double changePercent = ((rand() % 20001) - 10000) / 100000.0;
    double oldPrice = s->currentPrice;
    s->currentPrice *= (1 + changePercent);

	//Validate the number is not negative or zero
    if (s->currentPrice < 0.01) {
        s->currentPrice = 0.01; 
    }


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

        Sleep(1000);
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
        Sleep(1000);
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

    case USER_MENU:
        processUserMenu(market, event->eventTime, head);
        break;

    default:
        printf("Unknown event type %d\n", event->type);
    }

    free(event);
}

void processUserMenu(Market* market, double currentTime, Event** head) {
    int choice;
    int searchID, qty, index;

    printPortfolio(market);

    printf("\n\nPAUSED AT TIME %.2f | Available CASH: %.2f\n", currentTime, market->cash);
    printf("\n1. Buy Stock");
    printf("\n2. Sell Stock");
    printf("\n3. Continue Simulation (Press Any Key to continue)");
    printf("\nChoice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
    case 2:
        printf("Enter Stock ID: ");
        scanf("%d", &searchID);
        index = findStockIndexByID(market, searchID);

        if (index == -1) {
            printf("\n[!] Error: Stock ID %d not found!\n", searchID);
            printf("Press Any Key to continue...");
            while (getchar() != '\n'); getchar();
            break;
        }

        printf("Enter Quantity: ");
        scanf("%d", &qty);
        insertEvent(head, currentTime, (choice == 1 ? BUY_ORDER : SELL_ORDER), index, qty);
        break;

    case 3:
        printf("\nResuming simulation. Press Any Key to continue...");
        while (getchar() != '\n'); getchar();
        break;

    default:
        break;
    }

    insertEvent(head, currentTime + 10.0, USER_MENU, 0, 0);
}