#ifndef SegmentBlock_h
#define SegmentBlock_h 1

#include "header.h"

#define SEGMENT_BLOCK_WIDTH      60
#define SEGMENT_BLOCK_HEIGHT     45
#define SEGMENT_BLOCK_GREYSCALE  " .:-=+*#%@"

// #include "clock.h"
// #define SEGMENT_BLOCK_DELAY    300L

class SegmentBlock {
public:
  //SegmentBlock(size_t imageWidth, size_t imageHeight);
  SegmentBlock();
  virtual ~SegmentBlock();
  virtual void setup();
  virtual void serialPrint();
  virtual void serialHeatPrint();
  // void loop();
  virtual int loop(uint8_t *buffer, size_t size);
  virtual long get(size_t x, size_t y);
  virtual void set(size_t x, size_t y, long value);
  virtual void clone(SegmentBlock *segmentBlockRef);
  long pixelPerSegment = 1;
  size_t imageWidth = 0;
  size_t imageHeight = 0;
private:
  size_t currentBufferPosition = 0;
  long segment[SEGMENT_BLOCK_WIDTH][SEGMENT_BLOCK_HEIGHT] = { { 0 } };
  // Clock *clock;
  virtual void loadPartialBuffer(uint8_t value, size_t position);
};

#endif
