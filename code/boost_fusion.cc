/*
 * ==================================================================
 *
 *       Filename:  boost_fusion.cc
 *         Author:  Peng Wang
 *          Email:  pw2191195@gmail.com
 *        Created:  05/21/18 16:43:26
 *    Description:
 *
 * ==================================================================
 */

#include <string>
#include <iostream>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

struct Foo {
  int val;
  std::string answer;
};

BOOST_FUSION_ADAPT_STRUCT(Foo, (int, val)(std::string, answer));

struct ValuePrinter {
  template <typename T>
  void operator()(const T& v) const {
    std::cout << v << '\n';
  }
};

void PrintMemberValue() {
  Foo foo;
  foo.val = 42;
  foo.answer = "1024";

  boost::fusion::for_each(foo, ValuePrinter());
}

// Even better
// #include "util/ForEachMember.h"
struct MemberValuePrinter {
  template <typename T>
  void operator()(const char* memberName, const T& v) const {
    std::cout << "Name: " << memberName << ", value: " << v << '\n';
  }
};

void PrintMemberNameAndValue() {
  Foo foo;
  foo.val = 42;
  foo.answer = "1024";

  boost::fusion::ForEachMember(foo, MemberValuePrinter());
}

int main() {}
