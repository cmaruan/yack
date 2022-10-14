#if !defined(ARCH_I386_TYPES_H)
#define ARCH_I386_TYPES_H

#ifdef __INT8_TYPE__
#ifdef __ASSEMBLY__
#define int8_t __INT8_TYPE__
#else
typedef __INT8_TYPE__ int8_t;
#endif  // __ASSEMBLY__
#endif

#ifdef __UINT8_TYPE__
#ifdef __ASSEMBLY__
#define uint8_t __UINT8_TYPE__
#else
typedef __UINT8_TYPE__ uint8_t;
#endif  // __ASSEMBLY__
#endif

#ifdef __INT16_TYPE__
#ifdef __ASSEMBLY__
#define int16_t __INT16_TYPE__
#else
typedef __INT16_TYPE__ int16_t;
#endif  // __ASSEMBLY__
#endif

#ifdef __UINT16_TYPE__
#ifdef __ASSEMBLY__
#define uint16_t __UINT16_TYPE__
#else
typedef __UINT16_TYPE__ uint16_t;
#endif  // __ASSEMBLY__
#endif

#ifdef __INT32_TYPE__
#ifdef __ASSEMBLY__
#define int32_t __INT32_TYPE__
#else
typedef __INT32_TYPE__ int32_t;
#endif  // __ASSEMBLY__
#endif

#ifdef __UINT32_TYPE__
#ifdef __ASSEMBLY__
#define uint32_t __UINT32_TYPE__
#else
typedef __UINT32_TYPE__ uint32_t;
#endif  // __ASSEMBLY__
#endif

#ifdef __INT64_TYPE__
#ifdef __ASSEMBLY__
#define int64_t __INT64_TYPE__
#else
typedef __INT64_TYPE__ int64_t;
#endif  // __ASSEMBLY__
#endif

#ifdef __UINT64_TYPE__
#ifdef __ASSEMBLY__
#define uint64_t __UINT64_TYPE__
#else
typedef __UINT64_TYPE__ uint64_t;
#endif  // __ASSEMBLY__
#endif

#define NULL ((void *)0)

#endif  // ARCH_I386_TYPES_H
