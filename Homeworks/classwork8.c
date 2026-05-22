#include <stdio.h>
#include <string.h>

int main() {
    printf("hello world");
    return 0;
}

void Get_string(char *str) {
    char *temp = str;

    while (temp != '\0') {
        scanf("%c", temp);
		temp++;
    }

	printf("%d", quest1(str, strlen(str)));
}

void swap(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

int quest1(char* str,int size) {
    char* start = str;
    char* end = str;
    int original = 1;

    while (*end != '\0') end++;
    end--;

    while (start < end) {
        if (*start != *end) original = 0;
		swap(start, end);
        start++;
        end--;
    }
    return original;
}

void quest2(char *str,int* small, int* big,int *num,int *elsee) {
    while (*str != '\0') {
        if (*str >= 'a' && *str <= 'z') {
            (*small)++;
        } else if (*str >= 'A' && *str <= 'Z') {
            (*big)++;
        } else if (*str >= '0' && *str <= '9') {
            (*num)++;
        } else {
            (*elsee)++;
        }
		str++;
    }

}

void quest3(char* str) {
    char* read = str;
    char* write = str;

    while (*read != '\0') {
        if (*read == ' ') {
            if (write > str && *(write - 1) != ' ') {
                *write = ' ';
                write++;
            }
        }
        else {
            *write = *read;
            write++;
        }
        read++;
    }
    *write = '\0';
}