//
// Created by Yongkang on 07/04/2022.
//

#include "circle.h"

#include <stdio.h>
#include <stdlib.h>

node *head = NULL;
node *tail = NULL;
node *current = NULL;

void initialize() {
    // initialize the head node with the minimum address
    head = (node *) malloc(sizeof(node));
    head->ph_addr = MINIMUM;
    head->len = 0;

    // initialize the tail node with the maximum address
    tail = (node *) malloc(sizeof(node));
    tail->ph_addr = (void *) MAXIMUM;
    head->len = 0;

    // connect the head node and the tail node as a circle
    head->prev = tail;
    head->next = tail;
    tail->prev = head;
    tail->next = head;

    current = head;
}

action insert(void *ph_addr, size_t len) {
    if (len == 0) {
        return NONE;
    }

    node *tmp = current;
    while(!((tmp->ph_addr <= ph_addr) && (ph_addr < tmp->next->ph_addr))) {
        tmp = tmp->next;
    }
    if (ph_addr == tmp->ph_addr) {
        // TODO: cover the current node
        tmp->len = len;
        return OVERWRITE;
    } else {
        // TODO: write the log
        node *added = (node *) malloc(sizeof(node));
        added->ph_addr = ph_addr;
        added->len = len;
        added->prev = tmp;
        added->next = tmp->next;
        tmp->next->prev = added;
        tmp->next = added;
        return INSERT;
    }
}

void written() {
    // TODO: write the log
    node *tmp = current;
    current = tmp->next;
    tmp->prev->next = current;
    current->prev = tmp->prev;
    free(tmp);
}
