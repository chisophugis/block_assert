Block Assert
============

Include "block_assert.hpp" in order to use the `BLOCK_ASSERT` macro. The
usage is as follows::

  BLOCK_ASSERT("Your message about the condition being tested",
    (a)(SEQ)(of)(variables)(to)(pass)(in), (
      int foo = a;
      some_type bar(a, SEQ, in);
      return foo.something() == bar.mutate_in_some_way();
  ));

A "SEQ" is a sequence where each element is enclosed in parentheses. It is
one of the primary data structures of the Boost Preprocessor library. You
cannot pass in an empty one, since they don't exist. It is perfectly OK to
pass in a variable and not use it though.

The variables you pass in are made available in the block under the same
name you passed them in with.

The parenthesis-enclosed block passed in should return true if the
assertion succeeds and false otherwise.

See the file "example.cc" for a more-or-less real example of usage.


Caveats
=======

The `__VA_ARGS__` macro is used. There is a not-fully-equivalent workaround
that can be enabled by defining `BLOCK_ASSERT_NO_VA_ARGS`, but it restricts
the function to having only a single declarator per declaration, not using
the comma operator, and not having templates that take multiple arguments.
The limitation is caused by the preprocessor thinking that commas that
aren't enclosed in a balanced pair of parentheses are delimiting multiple macro
arguments when the parentheses of the passed-in block are removed. Without
`__VA_ARGS__`, the macro that removes those parentheses is limited to a
fixed number of "unenclosed commas" in the block (which is arbitrarily set
to be zero).


Compatibility and Portability
=============================

Depends on the Boost Preprocessor library.

Tested with GCC and Clang. It can be made to work on any compiler that has
`decltype`, a native "typeof" of any kind, or template member functions for
local structs.


Legal Stuff
===========

All headers files are under the Boost Software License. See the file
LICENSE_1_0.txt for more information. Do whatever you want with everything
else.
