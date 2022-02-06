#ifndef SHARED_PTR_HPP_
#define SHARED_PTR_HPP_

/** \file shared_ptr.hpp */

#include <type_traits>
#include <cstdint>
#include <atomic>

#include <intrin.h>

#include <boost/stacktrace.hpp>

#include "RefCounter.hpp"
#include "PtrBase.hpp"
#include "enable_shared_from_this.hpp"
#include <iostream>

#define INSPECT_SHARED_PTR_NAMESPACE inspect

namespace INSPECT_SHARED_PTR_NAMESPACE
{
template <typename T> class weak_ptr;

template <typename T> class shared_ptr : public _PtrBase<T>
{
 public:
   shared_ptr( ) noexcept
      : _PtrBase( )
   {
      std::cout << "===== CREATE SHARED_PTR >>>>\n";
      std::cout << boost::stacktrace::stacktrace( );
      std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
   }

   shared_ptr(T *t)
      : _PtrBase(t)
   {
      std::cout << "===== CREATE SHARED_PTR with Value >>>>\n";
      std::cout << boost::stacktrace::stacktrace( );
      std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";

       if constexpr (std::is_convertible<T, enable_shared_from_this<T>>( ))
      {
         enable_shared_from_this<T> *t_sft =
            reinterpret_cast<enable_shared_from_this<T> *>(t);
         t_sft->_weak_this = *this;
      }
   }

   shared_ptr(const shared_ptr &other) noexcept
   {
      std::cout << "===== COPY SHARED_PTR >>>>\n";
      std::cout << boost::stacktrace::stacktrace( );
      std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
      _ptr = other._ptr;
      _ref_count = other._ref_count;
      _ref_count->increment_ref( );
   }

   shared_ptr &operator=(const shared_ptr &other)
   {
      // Guard self assignment
      if (this == &other)
         return *this;

      tmp = shared_ptr(other);
      this->swap(tmp);
      return *this;
   }

   shared_ptr(const weak_ptr<T> &weak)
   {
      if (!this->shared_from_weak(weak))
      {
         throw std::bad_weak_ptr( );
      }
   }

   template <typename Tx, typename Dx>
   shared_ptr(Tx *t, Dx deleter)
      : _PtrBase(t)
   {
      _PtrBase::_ref_count = new _RefCounterWithDeleter(t, std::move(deleter));
   }

   void swap(shared_ptr &other) { this->_swap(other); }
   void reset( ) noexcept { shared_ptr( ).swap(*this); }
   template <typename _Tx> void reset(_Tx *t) { shared_ptr(t).swap(*this); }
   explicit operator bool( ) const noexcept { return get( ) != nullptr; }
};

template <typename T, typename... Args> shared_ptr<T> make_shared(Args &&...args)
{
   return shared_ptr<T>(new T(args...));
}

template <typename T> void swap(shared_ptr<T> &left, shared_ptr<T> &right)
{
   left.swap(right);
}

}  // namespace INSPECT_SHARED_PTR_NAMESPACE


// Copyright Urs Karger, 2021. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#endif /* SHARED_PTR_HPP_ */
