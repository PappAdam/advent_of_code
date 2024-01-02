#ifndef VECTOR
#define VECTOR
#include <stdlib.h>
#include <string.h>

#define DEFINE_VEC(type)                                                                        \
    typedef struct _##type##Vector                                                              \
    {                                                                                           \
        type *content;                                                                          \
        unsigned long capacity;                                                                 \
        unsigned long len;                                                                      \
    } type##Vector;                                                                             \
                                                                                                \
    type##Vector new_##type##_vec(size_t capacity)                                              \
    {                                                                                           \
        type *content = malloc(capacity * sizeof(type));                                        \
                                                                                                \
        return (type##Vector){                                                                  \
            .content = content,                                                                 \
            .len = 0,                                                                           \
            .capacity = capacity,                                                               \
        };                                                                                      \
    }                                                                                           \
                                                                                                \
    void push_##type(type##Vector *vec, type value)                                             \
    {                                                                                           \
        if (vec->len + 1 >= vec->capacity)                                                      \
        {                                                                                       \
            vec->capacity *= 2;                                                                 \
            vec->content = realloc(vec->content, vec->capacity * sizeof(type));                 \
        }                                                                                       \
                                                                                                \
        if (vec->content)                                                                       \
        {                                                                                       \
            vec->content[vec->len] = value;                                                     \
        }                                                                                       \
        vec->len++;                                                                             \
    }                                                                                           \
                                                                                                \
    void remove_##type(type##Vector *vec, size_t index, size_t n)                               \
    {                                                                                           \
        type *dst_ptr = vec->content + index;                                                   \
        type *src_ptr = vec->content + index + n;                                               \
                                                                                                \
        memmove((void *)dst_ptr, (void *)src_ptr, (vec->len-- - index + n - 1) * sizeof(type)); \
    }

#endif