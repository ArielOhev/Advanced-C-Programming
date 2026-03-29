#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"


void PrintLinkedList(item* head);
item* Quest1(int* A, int size);
item* Quest3A(item* A, item Item);
void Quest3B(item** A, item* Item);
void Quest4(item* head);
void Quest5(item** head);

int main() {
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	item* head = Quest1(arr, 9);

	printf("Linked List (Odds then Evens):\n");
	PrintLinkedList(head);

	item newItem;
	newItem.data = 100;
	head = Quest3A(head, newItem);

	printf("After adding 100:\n");
	PrintLinkedList(head);

	Quest4(&head);
	PrintLinkedList(head);

	Quest5(&head);
	PrintLinkedList(head);

    return 0;
}

void PrintLinkedList(item* head) {
	item* current = head;
	while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

item* Quest1(int* A,int size) {
	item* head = NULL;
	item* current = NULL;

	for(int i=0;i<size;i++){
		if(A[i]%2!=0){
			item* newNode = (item*)malloc(sizeof(item));
			newNode->data = A[i];
			newNode->next = NULL;

			if (head == NULL) {
				head = newNode;
				current = head;
			}
			else {
				current->next = newNode;
				current = newNode;
			}
		}
	}
	for (int i = 0;i < size;i++) {
		if (A[i] % 2 == 0) {
			item* newNode = (item*)malloc(sizeof(item));
			newNode->data = A[i];
			newNode->next = NULL;

			if (head == NULL) {
				head = newNode;
				current = head;
			}
			else {
				current->next = newNode;
				current = newNode;
			}
		}
	}
	return head;
}

item* Quest3A(item* head, item ItemData) {
	item* newNode = (item*)malloc(sizeof(item));
	if (newNode == NULL) return head;
	newNode->data = ItemData.data;
	newNode->next = head;

	return newNode;
}
	
void Quest3B(item** A, item *Item) {
	item* newNode = (item*)malloc(sizeof(item));
	if (newNode == NULL) return;

	newNode->data = Item->data;
	newNode->next = *A;

	*A = newNode;
}

void Quest4(item **head){
	if (*head == NULL) return;
	item* newNode;

	newNode = *head;
	*head = (*head)->next;
	free(newNode);
}

void Quest5(item** head) {
	if ((*head) == NULL) return;

	item* current = (*head);
	
	while (current->next->next != NULL) {
		current = current->next;
	}
	item* temp = current->next;
	current->next = NULL;
	free(temp);
	
}
