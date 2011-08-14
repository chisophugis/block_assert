
//          Copyright Sean Silva 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This header provides the core functionality to properly define
// BLOCK_ASSERT_HELPER_FUNCTION_HEADER when the compiler supports some
// native way to get at the type of a name (a "typegetter").
//
// To do so, define the function-like macro BLOCK_ASSERT_TYPEGETTER so that
// the invocation 'BLOCK_ASSERT_TYPEGETTER(name)' will evaluate to the type
// of 'name'.
//
// The header "use_decltype.hpp" contains a simple example, where "decltype" is
// used as the typegetter.

#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/transform.hpp>

#ifndef BLOCK_ASSERT_TYPEGETTER
# error "No typegetter"
#endif

#define BLOCK_ASSERT_ADD_TYPE(s,data,elem) BLOCK_ASSERT_TYPEGETTER(elem) elem

#define BLOCK_ASSERT_HELPER_FUNCTION_HEADER(paramseq)            \
  static bool assert_test(                                       \
    BOOST_PP_SEQ_ENUM(                                           \
      BOOST_PP_SEQ_TRANSFORM(BLOCK_ASSERT_ADD_TYPE, ~, paramseq) \
    )                                                            \
  )
