/** \file ut_dbg_shared_ptr.cpp */

//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this
                           // in one cpp file
#include <catch.hpp>

#include <string>

#define USE_DEBUG

#ifdef USE_DEBUG
#include <inspect_shared_ptr/inspect_shared_ptr.hpp>
namespace ptr = inspect;
#else
#include <memory>
namespace ptr = std;
#endif

namespace ut
{
class Enabled : public ptr::enable_shared_from_this<Enabled>
{
 public:
   Enabled( ) = delete;

   std::string get( ) { return _msg; }
   void set(std::string msg) { _msg = std::move(msg); }
   ptr::shared_ptr<Enabled> getPtr( ) { return shared_from_this( ); }

   static ptr::shared_ptr<Enabled> create(const std::string msg) {
      return ptr::shared_ptr<Enabled>(new Enabled(msg));
   }

 private:
   Enabled(const std::string &msg)
      : _msg{msg}
   {
   }
   std::string _msg;
};

class NotEnabled
{
 public:
   explicit NotEnabled(const std::string &msg)
      : _msg{msg}
   {
   }

   std::string get( ) { return _msg; }
   void set(const std::string &msg) { _msg = msg; }
   void set(std::string msg) { _msg = std::move(msg); }


 private:
   std::string _msg;
};


SCENARIO("enable_shared_from_this creatable", "[enable_shared_from_this]")
{
   GIVEN("an enabled class")
   {
      std::string str{"foobar"};
      auto shared_ptr1 = Enabled::create(str);
      WHEN("a new shared ptr is requested with shared_from_this function")
      {
         auto shared_ptr2 = shared_ptr1->shared_from_this( );
         shared_ptr2->set(std::string("bar"));
         THEN("both pointer point to the same instance")
         {
            REQUIRE(shared_ptr1->get( ) == std::string("bar"));
            REQUIRE(shared_ptr2->get( ) == std::string("bar"));
         }
      }
   }
}

SCENARIO("sharing an object", "[enable_shared_from_this]")
{
   GIVEN("an enabled class")
   {
      std::string str{"foobar"};
      auto shared_ptr1 = Enabled::create(str);
      WHEN("a new shared ptr is requested with shared_from_this function and the first is reset")
      {
         auto shared_ptr2 = shared_ptr1->shared_from_this( );
         shared_ptr1.reset( );
         shared_ptr2->set(std::string("bar"));
         THEN("the newly created pointer keeps the instance alive")
         {
            REQUIRE(shared_ptr1.get( ) == nullptr);
            REQUIRE(shared_ptr2.use_count( ) == 1);
            REQUIRE(shared_ptr2->get( ) == std::string("bar"));
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
