/*
 * ==================================================================
 *
 *       Filename:  boost_foreach.cc
 *         Author:  Peng Wang
 *          Email:  pw2191195@gmail.com
 *        Created:  05/21/18 15:28:32
 *    Description:
 *
 * ==================================================================
 */

#include <map>
#include <vector>
#include <iostream>
#include <boost/typeof/typeof.hpp>
#include <boost/foreach.hpp>

// 1. 遍历vector
void TraverseVector(const std::vector<int>& v) {
  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] << '\n';
  }
}

// 2. 遍历map
void TraverseMap(const std::map<std::string, int>& m) {
  for (std::map<std::string, int>::const_iterator it = m.begin(); it != m.end();
       ++it) {
    std::cout << "first: " << it->first << ", second: " << it->second << '\n';
  }

  for (BOOST_AUTO(it, m.begin()); it != m.end(); ++it) {
    // do something
  }
}

// 3. 统一的遍历方式
void TraverseForeach() {
  std::vector<int> v;
  std::map<std::string, int> m;
  BOOST_FOREACH (int i, v) {
    // do something
  }
  typedef std::map<std::string, int>::value_type Pair;
  BOOST_FOREACH (const Pair& p, m) {
    // do something with p.first/p.second
  }

  // Even better
  // Comm/util/ForEach.h
  FOR_EACH(i, v) {}

  // copied Pair
  FOR_EACH(p, m) {}

  // reference
  FOR_EACH(&p, m) {}

  // const reference
  FOR_EACH(const& p, m) {}

  // c++11
  for (auto i : v) {
  }

  for (const auto& p : m) {
  }
}

int main() {}
