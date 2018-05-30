/*
 * ==================================================================
 *
 *       Filename:  named_type.cc
 *         Author:  jacobwpeng
 *          Email:  jacobwpeng@tencent.com
 *        Created:  05/08/18 11:11:05
 *    Description:
 *
 * ==================================================================
 */

template <typename T, typename Tag>
class NamedType {
 public:
  explicit NamedType(T val) : val_(val) {}

  operator T() const { return val_; }

  T val() const { return val_; }

 private:
  T val_;
};

struct PlayIDTag {};
struct MaxPointTag {};
struct BaseScoreTag {};
struct MinimalCoinNumTag {};

typedef NamedType<int, PlayIDTag> PlayID;
typedef NamedType<int, MaxPointTag> MaxPoint;
typedef NamedType<int, BaseScoreTag> BaseScore;
typedef NamedType<int, MinimalCoinNumTag> MinimalCoinNum;

void Check(int playID, int maxPoint, int baseScore, int minimalCoinNum) {}

void BetterCheck(PlayID playID,
                 MaxPoint maxPoint,
                 BaseScore baseScore,
                 MinimalCoinNum minimalCoinNum) {
  int local = playID;
}

int main() {
  int playID = 1;
  int maxPoint = 2;
  int baseScore = 3;
  int minimalCoinNum = 4;

  Check(playID, baseScore, maxPoint, minimalCoinNum);
  Check(playID, maxPoint, baseScore, minimalCoinNum);
  // BetterCheck(1, 2, 3, 4);  // Compile failed
  BetterCheck(PlayID(playID),
              MaxPoint(maxPoint),
              BaseScore(baseScore),
              MinimalCoinNum(minimalCoinNum));
}
