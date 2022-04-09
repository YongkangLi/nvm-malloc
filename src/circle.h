//
// Created by Yongkang on 07/04/2022.
//

#ifndef NVM_MALLOC_CIRCLE_H
#define NVM_MALLOC_CIRCLE_H

#define MINIMUM 0
#define MAXIMUM ~0

#include <stdlib.h>

enum action {NONE, INSERT, OVERWRITE};

struct node {
    void *ph_addr;
    size_t len;
    void *src;
    struct node *prev;
    struct node *next;
};

typedef enum action action;
typedef struct node node;

void initialize();
action insert(void *ph_addr, size_t len);
void written();

#endif //NVM_MALLOC_CIRCLE_H
