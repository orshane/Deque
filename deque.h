#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>
#include <stdbool.h>

// Macro to declare a stack-based fixed-size deque
#define DECLARE_STACK_DEQUE(TYPE, NAME, CAPACITY)                           \
typedef struct {                                                            \
    TYPE buffer[CAPACITY];                                                  \
    size_t front;                                                          \
    size_t back;                                                           \
    size_t size;                                                           \
} NAME;                                                                    \
                                                                           \
static inline void NAME##_init(NAME *d) {                                  \
    d->front = 0;                                                          \
    d->back = 0;                                                           \
    d->size = 0;                                                           \
}                                                                          \
                                                                           \
static inline bool NAME##_push_back(NAME *d, TYPE value) {                 \
    if (d->size >= CAPACITY) return false;                                 \
    d->buffer[d->back] = value;                                            \
    d->back = (d->back + 1) % CAPACITY;                                    \
    d->size++;                                                            \
    return true;                                                           \
}                                                                          \
                                                                           \
static inline bool NAME##_push_front(NAME *d, TYPE value) {                \
    if (d->size >= CAPACITY) return false;                                 \
    d->front = (d->front + CAPACITY - 1) % CAPACITY;                       \
    d->buffer[d->front] = value;                                           \
    d->size++;                                                            \
    return true;                                                           \
}                                                                          \
                                                                           \
static inline bool NAME##_pop_back(NAME *d, TYPE *out) {                   \
    if (d->size == 0) return false;                                        \
    d->back = (d->back + CAPACITY - 1) % CAPACITY;                         \
    if (out) *out = d->buffer[d->back];                                    \
    d->size--;                                                            \
    return true;                                                           \
}                                                                          \
                                                                           \
static inline bool NAME##_pop_front(NAME *d, TYPE *out) {                  \
    if (d->size == 0) return false;                                        \
    if (out) *out = d->buffer[d->front];                                   \
    d->front = (d->front + 1) % CAPACITY;                                  \
    d->size--;                                                            \
    return true;                                                           \
}                                                                          \
                                                                           \
static inline size_t NAME##_size(const NAME *d) {                          \
    return d->size;                                                        \
}                                                                          \
                                                                           \
static inline bool NAME##_empty(const NAME *d) {                           \
    return d->size == 0;                                                   \
}                                                                          \
                                                                           \
static inline bool NAME##_full(const NAME *d) {                            \
    return d->size == CAPACITY;                                            \
}                                                                          \
                                                                           \
/* Access element at index i (0-based from front). Returns NULL if i out of range */\
static inline TYPE* NAME##_element(NAME *d, size_t i) {                    \
    if (i >= d->size) return NULL;                                         \
    size_t idx = (d->front + i) % CAPACITY;                               \
    return &d->buffer[idx];                                                \
}

#endif // DEQUE_H

