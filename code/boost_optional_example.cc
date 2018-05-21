/*
 * ==================================================================
 *
 *       Filename:  boost_optional_example.cc
 *         Author:  Peng Wang
 *          Email:  pw2191195@gmail.com
 *        Created:  05/21/18 14:42:07
 *    Description:
 *
 * ==================================================================
 */

#include <iostream>
#include <string>
#include <boost/optional.hpp>

// 1. 使用一个不可能存在的返回值
bool HasChar(const std::string& s, char c) {
  return s.find(c) == std::string::npos;
}

// 2. 使用单独的bool值标记
bool ParseInt(const std::string& in, int* out) {
  if (in.empty()) {
    return false;
  }
  return true;
}

// 3. 使用boost::optional
boost::optional<int> ParseInt(const std::string& in) {
  if (in.empty()) {
    return boost::none;
  }

  return 1024;
}

int main(int, char* argv[]) {
  boost::optional<int> optInt = ParseInt(argv[1]);
  if (!optInt) {
    // 解析失败
    return EXIT_FAILURE;
  }
  std::cout << "Int: " << optInt.get() << '\n';
  std::cout << "Int: " << optInt.get_value_or(1024) << '\n';
}
