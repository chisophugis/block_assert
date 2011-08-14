
//          Copyright Sean Silva 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if __has_feature(cxx_decltype)

#define BLOCK_ASSERT_TYPEGETTER decltype
#include "typegetter.hpp"

#else

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#define BLOCK_ASSERT_CLANG_ADD_TYPES_TO_PARAMSEQ(paramseq) \
  BOOST_PP_SEQ_FOR_EACH_I(                                 \
    BLOCK_ASSERT_CLANG_TYPE_ADD_HELPER,                    \
    ~,                                                     \
    paramseq                                               \
  )

// The use of this in the SEQ_FOR_EACH_I will effectively make a new SEQ,
// since the expansion is in parentheses. Essentially getting the same
// effect as a "SEQ_TRANSFORM_I" function.
#define BLOCK_ASSERT_CLANG_TYPE_ADD_HELPER(r, data, i, elem) \
  (BOOST_PP_CAT(T,i) elem)

#define BLOCK_ASSERT_HELPER_FUNCTION_HEADER(paramseq)                   \
  template <BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(paramseq), class T)> \
  static bool assert_test(                                              \
    BOOST_PP_SEQ_ENUM(                                                  \
      BLOCK_ASSERT_CLANG_ADD_TYPES_TO_PARAMSEQ(paramseq)                \
    )                                                                   \
  )

#endif
