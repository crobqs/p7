#ifndef P7_LIST_H
#define P7_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int val;
    struct List* next;
} List;

void List_push_back(List** head, int val) {
    List* n = (List*)calloc(1, sizeof(List));
    while (*head && (*head)->next) head = &((*head)->next);
    (*head ? (*head)->next : *head) = (n->val = val, n);
}

void List_push_front(List** head, int val) {
    List* n = (List*)calloc(1, sizeof(List));
    n->next = *head, *head = (n->val = val, n);
}

void List_pop_back(List** head) {
    if (!*head || !(*head)->next) {
        free(*head);
        *head = NULL;
        return;
    }
    while ((*head)->next->next) head = &((*head)->next);
    free((*head)->next);
    (*head)->next = NULL;
}

void List_pop_front(List** head) {
    if (!*head) return;
    List* tmp = *head;
    *head = (*head)->next;
    free(tmp);
}

void List_print(List* head) {
    while (head) printf("%d ", head->val), head = head->next;
    printf("\n");
}

void List_clean(List** head) {
    while (*head) {
        List* tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
    *head = NULL;
}

#endif /* P7_LIST_H */
