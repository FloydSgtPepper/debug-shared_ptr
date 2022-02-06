#ifndef PTRBASE_HPP_
#define PTRBASE_HPP_

/** \file PtrBase.hpp */

#include <type_traits>
#include <cstdint>
#include <atomic>

#define INSPECT_SHARED_PTR_NAMESPACE inspect

namespace INSPECT_SHARED_PTR_NAMESPACE
{

template <typename T> class shared_ptr;
template <typename T> class weak_ptr;
template <typename T> class enable_shared_from_this;


/** base class for shared and weak pointer
*/
template <typename T> class _PtrBase
{
 public:
   using element_t = std::remove_all_extents_t<T>;

 private:
   template <typename U> friend class shared_ptr;

   template <typename V> friend class weak_ptr;
   template <typename W> friend class _PtrBase;

   _RefCounterBase *_ref_count;
   T *_ptr;

 protected:
   _PtrBase( ) noexcept
      : _ref_count(nullptr)
      , _ptr(nullptr)
   {
   }

   _PtrBase(T *t)
      : _ref_count{nullptr}
      , _ptr(t)
   {
      if (_ptr)
      {
         _ref_count = new _RefCounterResource(_ptr);
      }
   }

   _PtrBase(const shared_ptr<T> &shared)
      : _ref_count(shared._ref_count)
      , _ptr(shared._ptr)
   {
      _ref_count->increment_ref( );
   }

   _PtrBase(const weak_ptr<T> &weak)
   {
      if (!this->shared_from_weak(weak))
      {
         throw bad
      }
   }

   virtual ~_PtrBase( )
   {
      if (_ref_count)
      {
         auto ref_count = _ref_count->decrement_ref( );
         if (ref_count == 0)
         {
            //_deleter(_ptr);
            delete _ptr;
            _ptr = nullptr;
         }
         if (_ref_count->weak_count( ) == 0)
         {
            delete _ref_count;
            _ref_count = nullptr;
         }
      }
   }

   void _swap(_PtrBase &other) noexcept
   {
      using std::swap;
      swap(this->_ref_count, other._ref_count);
      swap(this->_ptr, other._ptr);
   }

   template <typename Tx> bool shared_from_weak(const weak_ptr<Tx> &other)
   {
      if (other._ref_count && other._ref_count->increment_ref_when_not_zero( ))
      {
         _ptr = other._ptr;
         _ref_count = other._ref_count;
         return true;
      }
      return false;
   }

   void release( )
   {
      if (_ref_count->decrement_ref( ) == 0)
      {
         _ref_count->_Destroy( );
         if (_ref_count->decrement_weak( ) == 0)
         {
            _ref_count->_Delete_this( );
         }
      }
   }



 public:
   explicit operator bool( ) const noexcept { return (_ptr != nullptr); }


   _RefCounterBase::Value_t use_count( )
   {
      return _ref_count ? _ref_count->use_count( ) : 0;
   }
   [[nodiscard]] element_t *get( ) const noexcept { return _ptr; }
   [[nodiscard]] element_t *operator->( ) const noexcept { return get( ); }
};


}  // namespace INSPECT_SHARED_PTR_NAMESPACE


// Copyright Urs Karger, 2022. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#endif /* PTRBASE_HPP_ */
