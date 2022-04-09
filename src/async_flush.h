//
// Created by Yongkang on 07/04/2022.
//

#ifndef NVM_MALLOC_ASYNC_FLUSH_H
#define NVM_MALLOC_ASYNC_FLUSH_H

#include <stdlib.h>

#define KEY 1985L

#define THRESHOLD 10000

struct msg_buf {
    long msg_type;
    void *ph_addr;
    size_t len;
};

typedef struct msg_buf msg_buf;

#endif //NVM_MALLOC_ASYNC_FLUSH_H
