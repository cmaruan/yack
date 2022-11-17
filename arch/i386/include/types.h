#if !defined(ARCH_I386_TYPES_H)
#define ARCH_I386_TYPES_H

#ifndef __ASSEMBLY__
#include <stddef.h>
#endif

#ifdef __INT8_TYPE__
#ifdef __ASSEMBLY__
#define i8 __INT8_TYPE__
#else
typedef __INT8_TYPE__ i8;
#endif  // __ASSEMBLY__
#endif

#ifdef __UINT8_TYPE__
#ifdef __ASSEMBLY__
#define u8 __UINT8_TYPE__
#else
typedef __UINT8_TYPE__ u8;
#endif  // __ASSEMBLY__
#endif

#ifdef __INT16_TYPE__
#ifdef __ASSEMBLY__
#define i16 __INT16_TYPE__
#else
typedef __INT16_TYPE__ i16;
#endif  // __ASSEMBLY__
#endif

#ifdef __UINT16_TYPE__
#ifdef __ASSEMBLY__
#define u16 __UINT16_TYPE__
#else
typedef __UINT16_TYPE__ u16;
#endif  // __ASSEMBLY__
#endif

#ifdef __INT32_TYPE__
#ifdef __ASSEMBLY__
#define i32 __INT32_TYPE__
#else
typedef __INT32_TYPE__ i32;
#endif  // __ASSEMBLY__
#endif

#ifdef __UINT32_TYPE__
#ifdef __ASSEMBLY__
#define u32 __UINT32_TYPE__
#else
typedef __UINT32_TYPE__ u32;
#endif  // __ASSEMBLY__
#endif

#ifdef __INT64_TYPE__
#ifdef __ASSEMBLY__
#define i64 __INT64_TYPE__
#else
typedef __INT64_TYPE__ i64;
#endif  // __ASSEMBLY__
#endif

#ifdef __UINT64_TYPE__
#ifdef __ASSEMBLY__
#define u64 __UINT64_TYPE__
#else
typedef __UINT64_TYPE__ u64;
#endif  // __ASSEMBLY__
#endif

#ifdef __SSIZE_TYPE__
#ifdef __ASSEMBLY__
#define ssize_t __SSIZE_TYPE__
#else
typedef __SSIZE_TYPE__ ssize_t;
#endif  // __ASSEMBLY__
#else
#ifdef __ASSEMBLY__
#define ssize_t __INT64_TYPE__
#else
typedef __INT64_TYPE__ ssize_t;
#endif  // __ASSEMBLY__
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#endif  // ARCH_I386_TYPES_H
