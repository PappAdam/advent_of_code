#pragma once
#include <stdlib.h>
#include <string.h>

#define DEFINE_VEC(type)                                                                        \
    type##Vector new_##type##_vec(size_t capacity)                                              \
    {                                                                                           \
        type *ptr = malloc(capacity * sizeof(type));                                            \
                                                                                                \
        return (type##Vector){                                                                  \
            .ptr = ptr,                                                                         \
            .len = 0,                                                                           \
            .capacity = capacity,                                                               \
        };                                                                                      \
    }                                                                                           \
    void free_##type##_vec(type##Vector *vec)                                                   \
    {                                                                                           \
        free(vec->ptr);                                                                         \
        vec->len = 0;                                                                           \
        vec->capacity = 0;                                                                      \
    }                                                                                           \
                                                                                                \
    type##Vector copy_##type##_vec(type##Vector *vec)                                           \
    {                                                                                           \
        type *ptr = malloc(vec->len * sizeof(type));                                            \
        memcpy(ptr, vec->ptr, sizeof(type) * vec->len);                                         \
        return (type##Vector){                                                                  \
            .ptr = ptr,                                                                         \
            .len = vec->len,                                                                    \
            .capacity = vec->len,                                                               \
        };                                                                                      \
    }                                                                                           \
                                                                                                \
    void push_##type(type##Vector *vec, type value)                                             \
    {                                                                                           \
        if (vec->len + 1 >= vec->capacity)                                                      \
        {                                                                                       \
            vec->capacity *= 2;                                                                 \
            vec->ptr = realloc(vec->ptr, vec->capacity * sizeof(type));                         \
        }                                                                                       \
                                                                                                \
        if (vec->ptr)                                                                           \
        {                                                                                       \
            vec->ptr[vec->len] = value;                                                         \
        }                                                                                       \
        vec->len++;                                                                             \
    }                                                                                           \
                                                                                                \
    void append_##type##_vec(type##Vector *dest, type##Vector *src)                             \
    {                                                                                           \
        if (dest->capacity < dest->len + src->len)                                              \
        {                                                                                       \
            dest->ptr = realloc(dest->ptr, (dest->len + src->len) * sizeof(type));              \
        }                                                                                       \
        memcpy((dest->ptr + dest->len), src->ptr, sizeof(type) * src->len);                     \
    }                                                                                           \
                                                                                                \
    void join_##type##_vec(type##Vector *dest, type##Vector *src)                               \
    {                                                                                           \
        if (dest->capacity < dest->len + src->len)                                              \
        {                                                                                       \
            dest->ptr = realloc(dest->ptr, (dest->len + src->len) * sizeof(type));              \
        }                                                                                       \
        memcpy((dest->ptr + dest->len), src->ptr, sizeof(type) * src->len);                     \
        free_##type##_vec(src);                                                                 \
    }                                                                                           \
                                                                                                \
    type get_##type(type##Vector *vec, unsigned long index)                                     \
    {                                                                                           \
        return vec->ptr[index];                                                                 \
    }                                                                                           \
                                                                                                \
    void remove_##type(type##Vector *vec, size_t index, size_t n)                               \
    {                                                                                           \
        type *dst_ptr = vec->ptr + index;                                                       \
        type *src_ptr = vec->ptr + index + n;                                                   \
                                                                                                \
        memmove((void *)dst_ptr, (void *)src_ptr, (vec->len-- - index + n - 1) * sizeof(type)); \
    }

#define DEFINE_VEC_HEADER(type)                                      \
    typedef struct _##type##Vector                                   \
    {                                                                \
        type *ptr;                                                   \
        unsigned long capacity;                                      \
        unsigned long len;                                           \
    } type##Vector;                                                  \
                                                                     \
    type##Vector new_##type##_vec(size_t capacity);                  \
    void free_##type##_vec(type##Vector *vec);                       \
    type##Vector copy_##type##_vec(type##Vector *vec);               \
    void push_##type(type##Vector *vec, type value);                 \
    void append_##type##_vec(type##Vector *dest, type##Vector *src); \
    void join_##type##_vec(type##Vector *dest, type##Vector *src);   \
    type get_##type(type##Vector *vec, unsigned long index);         \
    void remove_##type(type##Vector *vec, size_t index, size_t n);
