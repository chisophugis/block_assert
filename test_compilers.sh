#!/bin/bash

die () {
  echo "$@"
  exit 1
}

for compiler in 'clang++' 'g++' 'g++ -std=c++0x' 'g++ -std=gnu++0x'
do
  echo -n "Testing '$compiler' ... "
  $compiler example.cc 2>&1 -o example >/dev/null \
    || die "Error when compiling with '$compiler'."
  ./example 2>&1 | grep -q 'permutations of each other' \
    || die "BLOCK_ASSERT didn't trigger for '$compiler'."
  rm example
  echo "OK."
done
