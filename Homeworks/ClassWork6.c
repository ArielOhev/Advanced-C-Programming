#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <assert.h>


typedef struct item {
	char ch;
	struct item* next;
} item;


void printlinkedList(item* head);
void Quest1(item** head, char ch);
void Quest2(item** head, int num);
void Quest3(item** head);
void freeLinkedList(item** head);

int main()
{
	item* head = NULL;
	Quest2(&head, 5);
    
	printf("The linked list is: ");
	printlinkedList(head);

	Quest3(&head);

	printf("Reversed list: ");
	printlinkedList(head);

	freeLinkedList(&head);




	
	return 0;
}

void printlinkedList(item* head)
{
	item* current = head;
	while (current != NULL)
	{
		printf("%c ", current->ch);
		current = current->next;
	}
	printf("\n");
}

void freeLinkedList(item** head) {
	item* current = *head;
	item* nextNode;

	while (current != NULL) {
		nextNode = current->next;
		free(current);
		current = nextNode;
	}

	*head = NULL;
}

void Quest1(item** head, char ch)
{
    item* newItem = (item*)malloc(sizeof(item));
	assert(newItem);

    newItem->ch = ch;


    if (*head == NULL || ch < (*head)->ch) {
		newItem->next = *head;
        *head = newItem;
		return;
    }
    
     item* temp = *head;
     while (temp->next != NULL && temp->next->ch <= ch) {
        temp = temp->next;
     }
		
     newItem->next = temp->next;
     temp->next = newItem;
}

void Quest2(item** head,int num) {
	char ch;

	for (int i = 0;i < num;i++) {
		scanf(" %c", &ch);
		Quest1(head, ch);
	}
}

void Quest3(item** head) {
	item* prev=NULL;
	item* current=*head;
	item* next;

	while(current!=NULL){
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	*head = prev;
}










