#ifndef LIST_H
#define LIST_H

// הגדרת המבנה עבור איבר ברשימה מקושרת
typedef struct item {
    int data;
    struct item* next; // כאן חייב להיות רשום item (או השם שנתת אחרי ה-struct)
} item;

#endif#pragma once
