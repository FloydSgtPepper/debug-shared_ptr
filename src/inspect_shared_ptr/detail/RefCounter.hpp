#ifndef REFCOUNTER_HPP_
#define REFCOUNTER_HPP_

/** \file RefCounter.hpp */

#include <type_traits>
#include <cstdint>
#include <atomic>

#define INSPECT_SHARED_PTR_NAMESPACE inspect

namespace INSPECT_SHARED_PTR_NAMESPACE
{

template <typename T> class shared_ptr;
template <typename T> class weak_ptr;
template <typename T> class enable_shared_from_this;


struct _RefCounterBase
{
   using Value_t = std::uint32_t;

   std::atomic<Value_t> _uses;
   std::atomic<Value_t> _weaks;

   _RefCounterBase( ) noexcept
      : _uses(1)
      , _weaks(1)
   {
   }

   _RefCounterBase(const _RefCounterBase &) = delete;
   _RefCounterBase &operator=(_RefCounterBase &rhs) = delete;
   virtual ~_RefCounterBase( ) = default;
   _RefCounterBase(_RefCounterBase &&other) noexcept
      : _uses(other._uses.load(std::memory_order_relaxed))
      , _weaks(other._weaks.load(std::memory_order_relaxed))
   {
   }

   _RefCounterBase &operator=(_RefCounterBase &&rhs) noexcept
   {
      _uses.store(rhs._uses.load(std::memory_order_relaxed), std::memory_order_relaxed);
      _weaks.store(rhs._weaks.load(std::memory_order_relaxed), std::memory_order_relaxed);

      return *this;
   }

   /** destroy managed resource */
   virtual void _Destroy( ) noexcept = 0;
   /** self destruct */
   virtual void _Delete_this( ) noexcept = 0;


   Value_t use_count( ) const { return _uses.load(std::memory_order_relaxed); }
   Value_t weak_count( ) const { return _uses.load(std::memory_order_relaxed); }

   void increment_ref( ) { (void)_uses.fetch_add(1, std::memory_order_relaxed); }

   /** decrement the ref count *
    *
    * \return value before the decrement
    */
   Value_t decrement_ref( ) { return _uses.fetch_sub(1, std::memory_order_relaxed); }
   bool increment_ref_when_not_zero( )
   {
      bool success = false;
      Value_t count = _uses.load(std::memory_order_relaxed);
      while (!success && count != 0)
      {
         Value_t new_value{count + 1};
         success =
            _uses.compare_exchange_weak(count, new_value, std::memory_order_relaxed);
      }

      return success;
   }

   void increment_weak( ) { (void)_weaks.fetch_add(1, std::memory_order_relaxed); }
   Value_t decrement_weak( ) { return _weaks.fetch_sub(1, std::memory_order_relaxed); }
};

template <typename T> class _RefCounterResource : public _RefCounterBase
{
 public:
   _RefCounterResource(T *t)
      : _ptr(t)
   {
   }

   /** destroy managed resource */
   void _Destroy( ) noexcept override
   {
      delete _ptr;
      _ptr = nullptr;
   }

   /** self destruct */
   void _Delete_this( ) noexcept override { _Destroy( ); }

 private:
   T *_ptr;
};


template <typename T, typename D> class _RefCounterWithDeleter : public _RefCounterBase
{
 public:
   _RefCounterWithDeleter(T *t, D deleter)
      : _ptr(t)
      , _deleter(std::move(deleter))
   {
   }

   /** destroy managed resource */
   void _Destroy( ) noexcept override
   {
      _deleter(_ptr);
      _ptr = nullptr;
   }

   /** self destruct */
   void _Delete_this( ) noexcept override { delete this; }

 private:
   T *_ptr;
   D _deleter;
};

}  // namespace INSPECT_SHARED_PTR_NAMESPACE


// Copyright Urs Karger, 2021. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#endif /* REFCOUNTER_HPP_ */
