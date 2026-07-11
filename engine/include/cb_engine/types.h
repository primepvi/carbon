#ifndef CB_TYPES_H
#define CB_TYPES_H

// unsigned int types definitions.
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

// signed int types definitions.
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

// float types definitions.
typedef float f32;
typedef double f64;

// boolean types definitions.
typedef char b8;
typedef int b32;

// defining boolean literals.
#define true 1
#define false 0

// asserting types size.
_Static_assert(sizeof(u8) == 1, "Type u8 size must be 1 byte.");
_Static_assert(sizeof(u16) == 2, "Type u16 size must be 2 bytes.");
_Static_assert(sizeof(u32) == 4, "Type u32 size must be 4 bytes.");
_Static_assert(sizeof(u64) == 8, "Type u64 size must be 8 bytes.");

_Static_assert(sizeof(i8) == 1, "Type i8 size must be 1 byte.");
_Static_assert(sizeof(i16) == 2, "Type i16 size must be 2 bytes.");
_Static_assert(sizeof(i32) == 4, "Type i32 size must be 4 bytes.");
_Static_assert(sizeof(i64) == 8, "Type i64 size must be 8 bytes.");

_Static_assert(sizeof(f32) == 4, "Type f32 size must be 4 bytes.");
_Static_assert(sizeof(f64) == 8, "Type f64 size must be 8 bytes.");

_Static_assert(sizeof(b8) == 1, "Type b8 size must be 1 byte.");
_Static_assert(sizeof(b32) == 4, "Type b32 size must be 4 bytes.");

// exports.
#define CB_API __attribute__((visibility("default")))

#endif
