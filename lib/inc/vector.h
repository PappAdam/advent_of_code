#pragma once
#include <stdlib.h>
#include <string.h>

#define DEFINE_VEC(type)                                                                        \
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
    void free_##type##_vec(type##Vector *vec)                                                   \
    {                                                                                           \
        free(vec->content);                                                                     \
        vec->len = 0;                                                                           \
        vec->capacity = 0;                                                                      \
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
    void append_##type##_vec(type##Vector *dest, type##Vector *src)                             \
    {                                                                                           \
        if (dest->capacity < dest->len + src->len)                                              \
        {                                                                                       \
            dest->content = realloc(dest->content, (dest->len + src->len) * sizeof(type));      \
        }                                                                                       \
        memcpy((dest->content + dest->len), src->content, sizeof(type) * src->len);             \
    }                                                                                           \
                                                                                                \
    void join_##type##_vec(type##Vector *dest, type##Vector *src)                               \
    {                                                                                           \
        if (dest->capacity < dest->len + src->len)                                              \
        {                                                                                       \
            dest->content = realloc(dest->content, (dest->len + src->len) * sizeof(type));      \
        }                                                                                       \
        memcpy((dest->content + dest->len), src->content, sizeof(type) * src->len);             \
        free_##type##_vec(src);                                                                 \
    }                                                                                           \
                                                                                                \
    type get_##type(type##Vector *vec, unsigned long index)                                     \
    {                                                                                           \
        return vec->content[index];                                                             \
    }                                                                                           \
                                                                                                \
    void remove_##type(type##Vector *vec, size_t index, size_t n)                               \
    {                                                                                           \
        type *dst_ptr = vec->content + index;                                                   \
        type *src_ptr = vec->content + index + n;                                               \
                                                                                                \
        memmove((void *)dst_ptr, (void *)src_ptr, (vec->len-- - index + n - 1) * sizeof(type)); \
    }

#define DEFINE_VEC_HEADER(type)                                      \
    typedef struct _##type##Vector                                   \
    {                                                                \
        type *content;                                               \
        unsigned long capacity;                                      \
        unsigned long len;                                           \
    } type##Vector;                                                  \
                                                                     \
    type##Vector new_##type##_vec(size_t capacity);                  \
    void free_##type##_vec(type##Vector *vec);                       \
    void push_##type(type##Vector *vec, type value);                 \
    void append_##type##_vec(type##Vector *dest, type##Vector *src); \
    void join_##type##_vec(type##Vector *dest, type##Vector *src);   \
    type get_##type(type##Vector *vec, unsigned long index);         \
    void remove_##type(type##Vector *vec, size_t index, size_t n);