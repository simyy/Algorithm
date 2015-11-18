#include <stdio.h>
#include "deque.h"

static block* newBlock(block *leftlink, block *rightlink, size_t len)
{
    block* b;

    // set a check function to prevent len from overflowing, then refuse to
    // allocate new blocks if the current len is nearning overflow.
    // wait to add !!!
    
    if (numfreeblocks) {
        numfreeblocks--;
        b = freeblocks[numfreeblocks];
    } else {
        b = (struct block*)malloc(sizeof(block));
        if (b == NULL) {
            //perror("newblock malloc error");
            return NULL;
        }
    }
    b->leftlink = leftlink;
    b->rightlink = rightlink;
    return b;
}

static void freeBlock(block *b)
{
    if (numfreeblocks < MAXFREEBLOCKS) {
        freeblocks[numfreeblocks] = b;
        numfreeblocks++;
    } else {
        free(b);
        b = NULL;
    }
}

static deque* newDeque()
{
    deque* d;
    block* b;

    d = (struct deque*)malloc(sizeof(deque));
    if (d == NULL)
        return NULL;

    b = newBlock(NULL, NULL, 0);
    if (b == NULL) {
        return NULL;
    }

    d->leftblock = b;
    d->rightblock = b;
    // leftindex-- when appendleft, and rightindex++ when append
    // assign is after moving, then left and right one can't be conflict
    d->leftindex = CENTER + 1; 
    d->rightindex = CENTER;
    d->len = 0;
    d->state = 0; // incremented whenever the indices move
    d->maxlen = -1; // -1 means no limit

    return d;
}

static void destroy(deque* d)
{
    if (d->len == 0) {
        freeBlock(d->leftblock);
        d->leftblock = NULL;
        free(d);
        d == NULL;
    } else {
        clear(d);
        destroy(d);
    }
}

static void* append(deque* d, void* item)
{
    d->state++;   
    if (d->rightindex == BLOCKLEN - 1) {
        block* b = newBlock(d->rightblock, NULL, d->len);
        if (b == NULL)
            return NULL;
        d->rightblock->rightlink = b;
        d->rightblock = b;
        d->rightindex = -1;
    }

    d->len++; // block.len + 1
    d->rightindex++; // right append
    d->rightblock->data[d->rightindex] = item;
    //TRIM(d, popLeft)
}

static void* appendleft(deque* d, void* item)
{
    d->state++;
    if (d->leftindex == 0) {
        block* b = newBlock(NULL, d->rightblock, d->len);
        if (b == NULL)
            return NULL;
        d->leftblock->leftlink = b;
        d->leftblock = b;
        d->leftindex = BLOCKLEN;
    }   

    d->len++;
    d->leftindex--;
    d->leftblock->data[d->leftindex] = item;
    // TRIM(d, pop)
}

static void* pop(deque* d)
{
    void* item;
    block* prevBlock;

    if (d->len == 0) 
        return NULL;

    item = d->rightblock->data[d->rightindex];
    d->rightindex--;
    d->len--;
    d->state++;

    // remove block if it is empty
    if (d->rightindex == -1) {
        if (d->len == 0) {
            d->leftindex = CENTER + 1;
            d->rightindex = CENTER;
        } else {
            prevBlock = d->rightblock->leftlink;
            freeBlock(d->rightblock);
            d->rightblock = prevBlock;
            d->rightblock->rightlink = NULL;
            d->rightindex = BLOCKLEN - 1;
        }
    }
    return item;
}

static void* popleft(deque* d)
{
    void*  item;
    block* nextBlock;  

    if (d->len == 0)
        return NULL;

    item = d->leftblock->data[d->leftindex];
    d->len--;
    d->leftindex++;
    d->state++;

    if (d->leftindex == BLOCKLEN) {
        if (d->len == 0) {
            d->leftindex = CENTER + 1;
            d->rightindex = CENTER;
        } else {
            nextBlock = d->leftblock->rightlink;
            freeBlock(d->leftblock);
            d->leftblock = nextBlock;
            d->leftindex = -1;
            d->leftblock->leftlink = NULL;
        }
    }
    return item;
}

static void extend(deque* d, deque* e)
{
    if (e->len == 0)
        return;

    void* r;
    while ((r = popleft(e)) != NULL) {
        append(d, r);
    }
}

static void extendleft(deque* d, deque* e)
{
    if (e->len == 0)
        return;

    void* r;
    while ((r = pop(e)) != NULL) {
        appendleft(d, r);
    }
}

static void show(deque* d)
{
    if (d->len == 0)
        return;

    if (d->len <= BLOCKLEN) {
        int i;
        for (i = d->leftindex; i < d->len + d->leftindex; i++) {
            printf("index %d\t", i);
            printf("value:%d\n", *(int*)d->leftblock->data[i]);
        }
    }
}

static void clear(deque* d) 
{
    void* r;
    while ((r = pop(d)) != NULL) {
        if (r != NULL) {
            //free(r);
            r = NULL;
        }
    }
}

static bool empty(deque* d)
{
    if (d->len == 0) {
        return true;
    }
    return false;
}

static bool contain(deque* d, void* item)
{
    int start, end;
    block* b = d->leftblock;
    start = d->leftindex;
    if (b->rightlink == NULL)
        end = d->rightindex;
    else
        end = BLOCKLEN;
    while (b != NULL) {
        int i;
        for (i = start; i < end; i++) {
            if (b->data[i] == item)
                return true;
        }
        b = b->rightlink;
        if (b != NULL) {
            start = 0;
            if (b->rightlink == NULL)
                end = d->rightindex + 1;
            else
                end = BLOCKLEN;
        }
    }
    return false;
}

int main(int argc, char** argv)
{
    deque* d = newDeque();
    int x = 1;
    int y = 2;
    printf("append 1\n");
    append(d, &x);
    printf("appendleft 2\n");
    appendleft(d, &y);
    printf("deque len: %d\n", (int)d->len);
    show(d);

    printf("--------------------\n");

    void *r = pop(d);
    printf("pop: %d\n", *(int*)r);
    show(d);

    printf("--------------------\n");

    printf("append 3\n");
    append(d, &x);
    show(d);
    r = popleft(d);
    printf("popleft: %d\n", *(int*)r);
    show(d);

    printf("--------------------\n");

    deque* e = newDeque();
    int z = 3;
    append(e, &z);
    printf("deque e:\n");
    show(e);

    printf("extend d e\n");
    extend(d, e);
    show(d);

    append(e, &z);
    printf("extendleft d e\n");
    extendleft(d, e);
    show(d);

    printf("--------------------\n");

    if (contain(d, &z))
        printf("deque contain: %d\n", z);
    else
        printf("deque not contain: %d\n", z);

    printf("--------------------\n");

    printf("clear\n");
    clear(d);
    show(d);
    printf("destroy\n");
    destroy(d);
    show(d);

    return 1;
}
