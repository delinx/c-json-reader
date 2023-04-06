#ifndef TYPES_HPP
#define TYPES_HPP

#include <stdbool.h>
#include <stddef.h>

// 1 byte
typedef char i8;
typedef unsigned char u8;
// 2 bytes
typedef short int i16;
typedef unsigned short int u16;
// 4 bytes
typedef int i32;
typedef unsigned int u32;
typedef float f32;
// 8 bytes
typedef long i64;
typedef unsigned long u64;
typedef double f64;
// 16 bytes
typedef long double f96;
// size_t
typedef size_t usize;

// Copied and adapted some code from https://github.com/travisvroman/ below
// ORIGINAL AUTHORS COPYRIGHT NOTICE / LICENSE:
/**
 * @file defines.h
 * @author Travis Vroman (travis@kohiengine.com)
 * @brief This file contains global type definitions which are used
 * throughout the entire engine and applications referencing it.
 * Numeric types are asserted statically to gurantee expected size.
 * @version 1.0
 * @date 2022-01-10
 *
 * @copyright Kohi Game Engine is Copyright (c) Travis Vroman 2021-2022
 *
 */

// Properly define static assertions.
#if defined(__clang__) || defined(__gcc__)
/** @brief Static assertion */
#define STATIC_ASSERT _Static_assert
#else

/** @brief Static assertion */
#define STATIC_ASSERT static_assert
#endif

// Ensure all types are of the correct size.
STATIC_ASSERT(sizeof(i8) == 1, "Expected i8 to be 1 byte.");
STATIC_ASSERT(sizeof(u8) == 1, "Expected u8 to be 1 byte.");
STATIC_ASSERT(sizeof(i16) == 2, "Expected i16 to be 2 bytes.");
STATIC_ASSERT(sizeof(u16) == 2, "Expected u16 to be 2 bytes.");
STATIC_ASSERT(sizeof(i32) == 4, "Expected i32 to be 4 bytes.");
STATIC_ASSERT(sizeof(u32) == 4, "Expected u32 to be 4 bytes.");
STATIC_ASSERT(sizeof(i64) == 8, "Expected i64 to be 8 bytes.");
STATIC_ASSERT(sizeof(u64) == 8, "Expected u64 to be 8 bytes.");
STATIC_ASSERT(sizeof(f32) == 4, "Expected f32 to be 4 bytes.");
STATIC_ASSERT(sizeof(f64) == 8, "Expected f64 to be 8 bytes.");
STATIC_ASSERT(sizeof(f96) == 16, "Expected f94 to be 16 bytes.");
STATIC_ASSERT(sizeof(usize) == 8, "Expected f94 to be 16 bytes.");

#endif
