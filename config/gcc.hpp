
//          Copyright Sean Silva 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if defined(__GXX_EXPERIMENTAL_CXX0X__)

// Can just use decltype
# include "use_decltype.hpp"

#else

// GCC still has typeof to fall back on
#define BLOCK_ASSERT_TYPEGETTER(name) typeof(name)
#include "typegetter.hpp"

#endif
