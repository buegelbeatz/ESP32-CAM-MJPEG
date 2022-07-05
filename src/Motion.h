#ifndef Motion_h
#define Motion_h 1

#include "header.h"
#include "SegmentBlock.h"
#include <iostream>
#include <string>

using namespace std;

#define MOTION_THERESOLD      4
#define MOTION_CLUSTER_MAX    3

class Motion {
public:
  Motion();
  virtual ~Motion();
  virtual void setup();
  virtual void loop(SegmentBlock *analyzeBlock);
  string clusterInfo = "";
private:
  virtual void analyzeSegment(size_t x, size_t y, size_t dx, size_t dy, int number);
  SegmentBlock *backupBlock;
  SegmentBlock *currentBlock;
  SegmentBlock *markedBlock;
  int initialized = 0;
  int clusterCount = 0;
};

#endif
