/** \file ut_dbg_shared_ptr.cpp */

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this
                           // in one cpp file
#include <catch.hpp>


#define USE_DEBUG
// #define CUSTOM_DELETE_FUNCTION

#ifdef USE_DEBUG
#include <inspect_shared_ptr/inspect_shared_ptr.hpp>
namespace ptr = inspect;
#else
#include <memory>
namespace ptr = std;
#endif


namespace ut
{

SCENARIO("smoke test", "[smoke_test]")
{
   GIVEN("two shared pointer")
   {
      ptr::shared_ptr<int> ptr1(new int(1));
      ptr::shared_ptr<int> ptr2 = ptr1;

      WHEN("the value is changed through the first ptr")
      {
         *ptr1.get( ) = 5;
         THEN("the new value is also read via the second ptr")
         {
            REQUIRE(*ptr1.get( ) == 5);
            REQUIRE(*ptr2.get( ) == 5);
            REQUIRE(ptr1.get( ) == ptr2.get( ));
         }
      }
   }
}

SCENARIO("reset", "[reset]")
{
   GIVEN("a shared ptr")
   {
      ptr::shared_ptr<int> ptr1(new int(1));

      WHEN("the shared_ptr reset function is called with no parameter")
      {
         ptr1.reset( );
         THEN("the shared_ptr is pointing to a nullptr")
         {
            REQUIRE(ptr1.get( ) == nullptr);
         }
      }
      AND_WHEN("the shared_ptr reset function is called with a new ptr")
      {
         int *int_ptr = new int(7);
         ptr1.reset(int_ptr);
         THEN("the shared_ptr is pointing to the new value")
         {
            REQUIRE(ptr1.get( ) == int_ptr);
            REQUIRE(*ptr1.get( ) == 7);
         }
      }
   }
}

SCENARIO("operator bool", "[operator]")
{
   GIVEN("a shared ptr")
   {
      ptr::shared_ptr<int> ptr1(new int(1));

      WHEN("the shared_ptr is evaluated in a bool context")
      {
         auto result = (bool)ptr1;
         THEN("the result is true") { REQUIRE(result == true); }
      }
      AND_WHEN("a default constructed shared ptr is evaluated")
      {
         ptr::shared_ptr<int> ptr2;
         auto result = (bool)ptr2;
         THEN("the result must be false") { REQUIRE(result == false); }
      }
   }
}


SCENARIO("make_shared", "[smoke_tests]")
{
   GIVEN("a shared pointer created with make_shared")
   {
      auto ptr1 = ptr::make_shared<int>(5);
      WHEN("the value is changed")
      {
         *ptr1.get( ) = 7;
         THEN("the new value is now the value of the underlying object")
         {
            REQUIRE(*ptr1.get( ) == 7);
         }
      }
   }
}

#ifdef CUSTOM_DELETE_FUNCTION
SCENARIO("custom deleter", "[smoke_tests]")
{
   bool fct_called = false;
   auto fct = [&fct_called](int *value) {
      fct_called = true;
      delete value;
   };
   GIVEN("a shared_ptr with a custom deleter")
   {
      auto ptr1 = ptr::shared_ptr<int>(new int(5), fct);

      WHEN("the shared ptr is reset")
      {
         ptr1.reset( );
         THEN("the custom delete functions gets called") { REQUIRE(fct_called == true); }
      }
   }
}
#endif

SCENARIO("sharing and use count", "[use_count, copy_ctr]")
{
   GIVEN("a shared_ptr")
   {
      auto ptr1 = ptr::shared_ptr<int>(new int(5));

      WHEN("the shared is copied")
      {
         ptr::shared_ptr<int> ptr2 = ptr1;
         THEN("the use count must be 2") { REQUIRE(ptr1.use_count( ) == 2); }
      }

      AND_WHEN("the first pointer is reset")
      {
         ptr::shared_ptr<int> ptr2(ptr1);
         ptr1.reset( );
         THEN("the 2nd pointer must still be valid")
         {
            REQUIRE(ptr2.use_count( ) == 1);
            *ptr2.get( ) = 3;
            REQUIRE((*ptr2.get( )) == 3);
         }
      }

      AND_WHEN("ptr1 is reset and ptr2 is out of scope")
      {

         THEN("the use count must be zero") { REQUIRE(ptr1.use_count( ) == 1); }
      }
   }
}

SCENARIO("sharing, reseating and use count", "[use_count, copy_ctr,reset]")
{
   GIVEN("a shared_ptr")
   {
      auto ptr1 = ptr::shared_ptr<int>(new int(5));

      WHEN("the pointer is copied and the original is reset")
      {
         ptr::shared_ptr<int> ptr2(ptr1);
         ptr1.reset(new int(9));
         THEN("the pointers must be distinct")
         {
            REQUIRE(ptr1.use_count( ) == 1);
            REQUIRE((*ptr1.get( )) == 9);
            REQUIRE(ptr2.use_count( ) == 1);
            REQUIRE((*ptr2.get( )) == 5);
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
