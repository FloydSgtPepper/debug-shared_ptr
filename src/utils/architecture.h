#ifndef ARCHITECTURE_H_
#define ARCHITECTURE_H_

/** \file architecture.h
 * macros that define the processor architecture
*/

// Check MSVC
// see https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?redirectedfrom=MSDN&view=msvc-170#microsoft-specific-predefined-macros
#ifdef _MSC_VER
#ifdef _M_X64
#define ARCH_64BIT
#else
#define ARCH_32BIT
#endif
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ARCH_64BIT
#else
#define ARCH_32BIT
#endif
#endif 


// Copyright Urs Karger, 2022. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#endif /* ARCHITECTURE_H_ */
