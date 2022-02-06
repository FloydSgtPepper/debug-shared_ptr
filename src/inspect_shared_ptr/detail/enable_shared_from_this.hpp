#ifndef ENABLE_SHARED_FROM_THIS_HPP_
#define ENABLE_SHARED_FROM_THIS_HPP_

/** \file enable_shared_from_this.hpp */

#include "inspect_shared_ptr_def.h"
#include "shared_ptr.hpp"
#include "weak_ptr.hpp"


INSPECT_SHARED_PTR_NAMESPACE_START

template <typename T> class shared_ptr;
template <typename T> class weak_ptr;

/** create a shared_ptr from a class instance
* The class must be initially created as a shared_ptr. 
*/
template <typename T> class enable_shared_from_this
{
   template <typename U> friend class shared_ptr;


 public:
   /** ctor
   */
   enable_shared_from_this( )
      : _weak_this{nullptr}
   {
   }

   /** get a shared_ptr from this class instance
   *
   * \return a shared_ptr, throws
   */
   [[nodiscard]] shared_ptr<T> shared_from_this( ) { return shared_ptr<T>(_weak_this); }

   /** get a weak_ptr from this class instance
   *
   * \return a weak_ptr, throws
   */
   [[nodiscard]] weak_ptr<T> weak_from_this( ) { return weak_ptr<T>(_weak_this); }

 private:
   weak_ptr<T> _weak_this;
};

INSPECT_SHARED_PTR_NAMESPACE_END


// Copyright Urs Karger, 2021. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#endif /* ENABLE_SHARED_FROM_THIS_HPP_ */
