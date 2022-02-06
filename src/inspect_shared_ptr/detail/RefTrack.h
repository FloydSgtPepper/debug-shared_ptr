#ifndef REFTRACK_H_
#define REFTRACK_H_

/** \file RefTrack.h */

#include <utils/architecture.h>

#include <type_traits>
#include <cstdint>
#include <mutext>

#define INSPECT_SHARED_PTR_NAMESPACE inspect

namespace INSPECT_SHARED_PTR_NAMESPACE
{

template <typename T> class shared_ptr;
template <typename T> class weak_ptr;
template <typename T> class enable_shared_from_this;


struct _RefTrack
{
#ifdef ARCH_32BIT
   using Address_t = std::uint32_t;
#else
   using Address_t = std::uint64_t;
#endif


};

}  // namespace INSPECT_SHARED_PTR_NAMESPACE


// Copyright Urs Karger, 2021. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#endif /* REFCOUNTER_HPP_ */
