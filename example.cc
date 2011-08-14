#include <algorithm>
#include <iterator>
#include <vector>

#include "block_assert.hpp"


template <class RandomAccessIterator>
void requires_permutations(RandomAccessIterator f,  RandomAccessIterator l,
                           RandomAccessIterator f1, RandomAccessIterator l1)
{
  BLOCK_ASSERT("[f,l) and [f1,l1) must be permutations of each other",
    (f)(l)(f1)(l1), (
      typedef typename std::iterator_traits<
        RandomAccessIterator
      >::value_type value_type;

      // no multiple declarators, so that it works with or without
      // __VA_ARGS__ (see the README for more information)
      std::vector<value_type> v(f,l);
      std::vector<value_type> v1(f1,l1);

      std::sort(v.begin(), v.end());
      std::sort(v1.begin(), v1.end());
      if (v != v1) BLOCK_ASSERT_FAIL;
      BLOCK_ASSERT_SUCCEED;
  ));

  // ... do something that requires them to be permutations of each other
}


int main() {
  const char s[] = "foo";

  // should succeed
  const char s1[] = "oof";
  requires_permutations(s, s+3, s1, s1+3);

  // should fail
  const char s2[] = "bar";
  requires_permutations(s, s+3, s2, s2+3);
}


// Some examples of problems when __VA_ARGS__ isn't used. It is protected
// so that it doesn't fail the whole compilation, since these are
// *designed* to fail the compilation if BLOCK_ASSERT_NO_VA_ARGS is
// defined.
#if !defined(BLOCK_ASSERT_NO_VA_ARGS)
template <class,class>
struct takes_multiple_args {};

void multiple_template_params_fail(int dummy) {
  BLOCK_ASSERT("this will fail to compile without __VA_ARGS__", (dummy), (
    takes_multiple_args<int,int> m;
    //                     ^ the culprit
    BLOCK_ASSERT_FAIL;
  ));
}

void multiple_declarators_fail(int *dummy) {
  BLOCK_ASSERT("this will fail to compile without __VA_ARGS__", (dummy), (
    int foo = 0, bar = 1;
    //         ^ the culprit
    BLOCK_ASSERT_FAIL;
  ));
}

void comma_operator_fail(int **dummy) {
  BLOCK_ASSERT("this will fail to compile without __VA_ARGS__", (dummy), (
    int foo = 0;
    int bar = 1;
    foo = 1, foo = 2;
    //     ^ the culprit
    BLOCK_ASSERT_FAIL;
  ));
}
#endif
