#ifndef INSPECT_SHARED_STACKTRACE_HPP_
#define INSPECT_SHARED_STACKTRACE_HPP_

/** \file inspect_shared_stacktrace.h */

#include <boost/stacktrace/stacktrace_fwd.hpp>

namespace boost
{
namespace stacktrace
{
    #if 0

// example from
// https://www.boost.org/doc/libs/1_77_0/doc/html/stacktrace/getting_started.html
template <class CharT, class TraitsT, class Allocator>
std::basic_ostream<CharT, TraitsT> &do_stream_st(
   std::basic_ostream<CharT, TraitsT> &os, const basic_stacktrace<Allocator> &bt);

template <class CharT, class TraitsT>
std::basic_ostream<CharT, TraitsT> &
operator<<(std::basic_ostream<CharT, TraitsT> &os, const stacktrace &bt)
{
   return do_stream_st(os, bt);
}

template <class CharT, class TraitsT, class Allocator>
std::basic_ostream<CharT, TraitsT> &do_stream_st(
   std::basic_ostream<CharT, TraitsT> &os, const basic_stacktrace<Allocator> &bt)
{
   const std::streamsize w = os.width( );
   const std::size_t frames = bt.size( );
   for (std::size_t i = 0; i < frames; ++i)
   {
      os.width(2);
      os << i;
      os.width(w);
      os << "# ";
      os << bt[i].name( );
      os << '\n';
   }

   return os;
}
#endif
}  // namespace stacktrace
}  // namespace boost

// Copyright Urs Karger, 2021. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#endif /* INSPECT_SHARED_STACKTRACE_HPP_ */
