/*
 * ==================================================================
 *
 *       Filename:  boost_multi_index.cc
 *         Author:  Peng Wang
 *          Email:  pw2191195@gmail.com
 *        Created:  05/21/18 17:14:59
 *    Description:
 *
 * ==================================================================
 */

#define BOOST_BIND_NO_PLACEHOLDERS

#include <stdint.h>
#include <vector>
#include <set>
#include <boost/lambda/lambda.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>

struct Entry {
  uint64_t id;         // 唯一
  uint64_t uin;        // 唯一
  uint64_t score;      // 不唯一
  uint64_t timestamp;  // 添加时间, 不唯一
};

class RankMap {
 public:
  bool AddEntry(const Entry& entry) {
    if (idIndexSet.find(entry) != idIndexSet.end()) {
      return false;
    }
    if (uinIndexSet.find(entry) != uinIndexSet.end()) {
      return false;
    }
    idIndexSet.insert(entry);
    uinIndexSet.insert(entry);
    scoreIndexSet.insert(entry);
    timestampIndexSet.insert(entry);
    return true;
  }

  Entry FindByUin(uint64_t uin) const;

  std::vector<Entry> FindByScore(uint64_t score) const;

  std::vector<Entry> FindInTimeRange(uint64_t from, uint64_t to) const {
    Entry fromEntry;
    fromEntry.timestamp = from;
    fromEntry.uin = 0;

    Entry toEntry;
    toEntry.timestamp = to;
    toEntry.uin = std::numeric_limits<uint64_t>::max();

    BOOST_AUTO(begin, timestampIndexSet.lower_bound(fromEntry));
    BOOST_AUTO(end, timestampIndexSet.upper_bound(toEntry));

    std::vector<Entry> entries;
    while (begin != end) {
      entries.push_back(*begin);
      ++begin;
    }

    return entries;
  }

 private:
  struct CompByID {
    bool operator()(const Entry& lhs, const Entry& rhs) const {
      return lhs.id < rhs.id;
    }
  };

  struct CompByUin {
    bool operator()(const Entry& lhs, const Entry& rhs) const {
      return lhs.uin < rhs.uin;
    }
  };

  struct CompByScore {
    bool operator()(const Entry& lhs, const Entry& rhs) const {
      if (lhs.score != rhs.score) {
        return lhs.score < rhs.score;
      }
      return lhs.uin < rhs.uin;
    }
  };

  struct CompByTimestamp {
    bool operator()(const Entry& lhs, const Entry& rhs) const {
      if (lhs.timestamp != rhs.timestamp) {
        return lhs.timestamp < rhs.timestamp;
      }
      return lhs.uin < rhs.uin;
    }
  };

  std::set<Entry, CompByID> idIndexSet;
  std::set<Entry, CompByUin> uinIndexSet;
  std::set<Entry, CompByScore> scoreIndexSet;
  std::set<Entry, CompByTimestamp> timestampIndexSet;
};

namespace bmi = boost::multi_index;

class MultiIndexRankMap {
 public:
  bool Add(const Entry& entry) {
    BOOST_AUTO(p, s.insert(entry));
    return p.second;
  }

  std::vector<Entry> FindInTimeRange(uint64_t from, uint64_t to) const {
    std::vector<Entry> entries;
    BOOST_AUTO(const& view, s.get<ByTimestamp>());
    using namespace boost::lambda;
    BOOST_AUTO(rng, view.range(from <= _1, _1 <= to));
    while (rng.first != rng.second) {
      entries.push_back(*rng.first);
    }
    return entries;
  }

 private:
  // tags
  struct ByID {};
  struct ByUin {};
  struct ByScore {};
  struct ByTimestamp {};

  typedef bmi::ordered_unique<bmi::tag<ByID>,
                              bmi::member<Entry, uint64_t, &Entry::id> >
      IndexByID;

  typedef bmi::hashed_unique<bmi::tag<ByUin>,
                             bmi::member<Entry, uint64_t, &Entry::uin> >
      IndexByUin;

  typedef bmi::ordered_non_unique<bmi::tag<ByScore>,
                                  bmi::member<Entry, uint64_t, &Entry::score> >
      IndexByScore;

  typedef bmi::ordered_non_unique<
      bmi::tag<ByTimestamp>,
      bmi::member<Entry, uint64_t, &Entry::timestamp> >
      IndexByTimestamp;

  typedef boost::multi_index_container<
      Entry,
      bmi::indexed_by<IndexByID, IndexByUin, IndexByScore, IndexByTimestamp> >
      internalSet;

  internalSet s;
};

int main() {}
