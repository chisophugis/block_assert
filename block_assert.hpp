
//          Copyright Sean Silva 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BLOCK_ASSERT_HPP_INCLUDED)
#define BLOCK_ASSERT_HPP_INCLUDED

// The assertion is ultimately handed off to good-ol' assert, so that
// BLOCK_ASSERT's disappear when clients expect them to.
#include <cassert>

// To add a new platform, just detect it and include an appropriate
// "config/*" file (write a new one if necessary).
#if defined(__clang__)

// clang imitates GCC well enough that it will actually work with the GCC
// configuration header, but this shows a different implementation
// technique (and one of clang's quirks, template member functions for
// local structs).
# include "config/clang.hpp"

#elif defined(__GNUC__)
# include "config/gcc.hpp"
#else

// Since I have found no way to make this work portably within the current
// C++ language standard (will be able to with C++0x decltype), fail to
// compile except for platforms that are known to work.

# error "Unknown compiler: Please add appropriate configuration macros to 'block_assert.hpp'"
#endif

#if defined(BLOCK_ASSERT_NO_VA_ARGS)
# define REMOVE_PARENS(tokens) tokens
#else
# define REMOVE_PARENS(...) __VA_ARGS__
#endif

#define BLOCK_ASSERT_HELPER_FUNCTION_INVOKE(paramseq) \
  BLOCK_ASSERT_helper_struct::assert_test(            \
    BOOST_PP_SEQ_ENUM(paramseq)                       \
  )

#define BLOCK_ASSERT(msg, paramseq, the_block_in_parens) \
  struct BLOCK_ASSERT_helper_struct {                    \
    BLOCK_ASSERT_HELPER_FUNCTION_HEADER(paramseq)        \
    { REMOVE_PARENS the_block_in_parens }                \
  };                                                     \
  ((BLOCK_ASSERT_HELPER_FUNCTION_INVOKE(paramseq))       \
  ? assert(true)                                         \
  : assert(msg && false))

#endif // !defined(BLOCK_ASSERT_HPP_INCLUDED)
