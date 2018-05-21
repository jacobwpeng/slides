/*
 * ==================================================================
 *
 *       Filename:  boost_local_function.cc
 *         Author:  Peng Wang
 *          Email:  pw2191195@gmail.com
 *        Created:  05/21/18 15:48:50
 *    Description:
 *
 * ==================================================================
 */

#include <map>
#include <vector>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/local_function.hpp>

struct Monster {
  int ID;
};
typedef std::map<int, int> PriorityMap;

PriorityMap priorityMap;
std::vector<Monster> monsters;

static bool SortByPriorityMap(const Monster& lhs,
                              const Monster& rhs,
                              const std::map<int, int>& priorityMap);

struct SortByPriority {
  SortByPriority(const PriorityMap& priorityMap) : priorityMap(priorityMap) {}

  bool operator()(const Monster& lhs, const Monster& rhs) const {
    return SortByPriorityMap(lhs, rhs, priorityMap);
  }

  PriorityMap priorityMap;
};

void SortByStruct() {
  std::sort(monsters.begin(), monsters.end(), SortByPriority(priorityMap));
}

static bool SortByPriorityMap(const Monster& lhs,
                              const Monster& rhs,
                              const std::map<int, int>& priorityMap) {
  PriorityMap localMap = priorityMap;
  return localMap[lhs.ID] < localMap[rhs.ID];
}

void SortByStaticFunction() {
  std::sort(monsters.begin(),
            monsters.end(),
            boost::bind(SortByPriorityMap, _1, _2, priorityMap));
}

void SortByLocalFunction() {
  bool BOOST_LOCAL_FUNCTION(
      const bind& priorityMap, const Monster& lhs, const Monster& rhs) {
    PriorityMap localMap = priorityMap;
    return localMap[lhs.ID] < localMap[rhs.ID];
  }
  BOOST_LOCAL_FUNCTION_NAME(SortByPriorityMapLocal);
  std::sort(monsters.begin(), monsters.end(), SortByPriorityMapLocal);
}

int main() {}
