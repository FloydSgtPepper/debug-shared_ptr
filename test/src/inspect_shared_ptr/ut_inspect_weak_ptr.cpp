/** \file ut_dbg_weak_ptr.cpp */

#include <dbg_shared_ptr/dbg_shared_ptr.hpp>

#include <catch.hpp>

#define USE_DEBUG

#ifdef USE_DEBUG
namespace ptr = debug;
#else
namespace ptr = std;
#include <memory>
#endif

namespace ut
{

SCENARIO("weak_ptr", "[smoke_tests]")
{
    GIVEN("a weak ptr")
    {
        auto ptr1 = ptr::make_shared<int>(5);
        ptr::weak_ptr<int> w_ptr (ptr1);
        WHEN("the weak ptr is turned into a shared pointer it can access the underlying value")
        {
            auto ptr2 = w_ptr.lock( );
            *ptr2.get( ) = 7;
            THEN("AND the new value is read back")
            {
                REQUIRE(*ptr1.get( ) == 7);
            }
        }

        WHEN("the shared pointer is reset")
        {
            ptr1.reset( );
            THEN("the weak pointer cannot be turned into a shared pointer anymore")
            {
                ptr::shared_ptr<int> ptr3 = w_ptr.lock( );
                REQUIRE(ptr3.get( ) == nullptr);
                REQUIRE(w_ptr.expired( ) == true);
            }
        }

    }
}

}  // namespace ut

// Copyright Urs Karger, 2021. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)
