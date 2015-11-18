/**********************
 * Deque in c
 * ********************/
#include <stddef.h>
#include <stdbool.h>

#ifndef _H_DEQUE
#define _H_DEQUE

#define BLOCKLEN 62
#define CENTER ((BLOCKLEN - 1) / 2)
#define MAXFREEBLOCKS 10

typedef struct BLOCK {
    void   *data[BLOCKLEN];
    struct BLOCK *rightlink;
    struct BLOCK *leftlink;
} block;

typedef struct {
    block  *leftblock;
    block  *rightblock;    
    size_t leftindex; //the leftest one
    size_t rightindex; //the rightest one
    size_t len;
    long   state; // record opt count
    size_t maxlen;
} deque;

#define TRIM(d, popfunction) \
    if (d->maxlen != -1 && d->len > d->maxlen) { \
        popfunction(d, NULL); \
    } \

static size_t numfreeblocks = 0;
static block *freeblocks[MAXFREEBLOCKS];

static block* newBlock(block *leftlink, block *rightlink, size_t len);
static void   freeBlock(block *b);

static deque* newDeque();
static void   destroy(deque* d);
static void   show(deque* d);
static void*  append(deque* d, void* item);
static void*  appendleft(deque* d, void* item);
static void*  pop(deque* d);
static void*  popleft(deque* d);
static void   extend(deque* d, deque* e);
static void   extendleft(deque* d, deque* e);
static void   clear(deque* d);
static bool   empty(deque* d);
static bool   contain(deque* d, void* item);

#endif
