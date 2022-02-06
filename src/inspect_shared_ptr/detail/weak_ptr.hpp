#ifndef WEAK_PTR_HPP_
#define WEAK_PTR_HPP_

/** \file weak_ptr.hpp */

#include "inspect_shared_ptr_def.h"
#include "PtrBase.hpp"
#include "enable_shared_from_this.hpp"

#include <type_traits>
#include <cstdint>
#include <atomic>

INSPECT_SHARED_PTR_NAMESPACE_START

/** a weak_ptr is a smart pointer that holds a weak reference to a resource
*/
template <typename T> class weak_ptr : public _PtrBase<T>
{
 public:
   /** ctor
   */
   weak_ptr<T>( ) noexcept
      : _PtrBase( ){ };

   /**
   */
   constexpr weak_ptr(std::nullptr_t) noexcept {}

   weak_ptr(T *ptr)
      : _PtrBase(ptr)
   {
   }

   /** ctor
    * create a weak_ptr from a shared_ptr
    *
    * \param shared  a shared pointer
   */
   weak_ptr<T>(shared_ptr<T> &shared)
      : _PtrBase(shared)
   {
      if (_ref_count)
      {
         _ref_count->increment_weak( );
      }
   }


   void swap(weak_ptr<T> &other) { _PtrBase::swap(other); }

   /** test if the resouce is expired
   * NOTE: if the resource is expired no new shared or weak ptr can be created from
   * this weak_ptr. Because of different threads a false result does not guarantee
   * that a supsequent lock will succeed.
   *
   * \return true if the source is expired
   */
   bool expired( ) { return use_count( ) == 0; }

   /** returns a shared_ptr if the resource is available
   * If the resource is not available a nullptr is returned.
   *
   * \code{.cpp}
   * auto weakPtr = weak_ptr<int> (new int);
   * auto sharedPtr = weak.lock();
   * if (sharedPtr) *sharedPtr->get() = 5;
   * \endcode
   * 
   * \return a shared_ptr to the resource or a shared_ptr pointing to nullptr
   */
   shared_ptr<T> lock( ) { return shared_ptr<T>(*this); }
};

template <typename T> void swap(weak_ptr<T> &left, weak_ptr<T> &right)
{
   left.swap(right);
}

INSPECT_SHARED_PTR_NAMESPACE_END


// Copyright Urs Karger, 2021. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#endif /* WEAK_PTR_HPP_ */
