#include "SegmentBlock.h"

void SegmentBlock::loadPartialBuffer(uint8_t value, size_t position) {
  size_t x = floor(((position % this->imageWidth) * SEGMENT_BLOCK_WIDTH) /
                   this->imageWidth);
  size_t y = floor((floor(position / this->imageWidth) * SEGMENT_BLOCK_HEIGHT) /
                   this->imageHeight);
  this->segment[x][y] += (long)value;
}

SegmentBlock::SegmentBlock() {}

SegmentBlock::~SegmentBlock() {}

void SegmentBlock::setup() {
  this->currentBufferPosition = 0;
  memset(this->segment, 0, sizeof this->segment);
}

void SegmentBlock::clone(SegmentBlock *segmentBlockRef) {
  //Serial.println("SegmentBlock::clone");
  memcpy(this->segment, segmentBlockRef->segment,
         SEGMENT_BLOCK_HEIGHT * SEGMENT_BLOCK_WIDTH * sizeof(long));
  this->imageWidth = segmentBlockRef->imageWidth;
  this->imageHeight = segmentBlockRef->imageHeight;
  this->pixelPerSegment = this->imageWidth * this->imageHeight /
                          (SEGMENT_BLOCK_WIDTH * SEGMENT_BLOCK_HEIGHT);
  //Serial.print("SegmentBlock::clone this->pixelPerSegment = ");Serial.println(this->pixelPerSegment);
}

void SegmentBlock::serialHeatPrint(){
  char level[] = SEGMENT_BLOCK_GREYSCALE;
  size_t pps = this->imageWidth * this->imageHeight / (SEGMENT_BLOCK_WIDTH * SEGMENT_BLOCK_HEIGHT);
  size_t factor = 256 * pps / 10;
  for (size_t y = 0; y < SEGMENT_BLOCK_HEIGHT; ++y) {
    for (size_t x = 0; x < SEGMENT_BLOCK_WIDTH; ++x) {
      size_t index = this->get(x, y) / factor;
      //Serial.print(index);Serial.print(" ");
      Serial.print(level[index]);
    }
    Serial.println(""); // start new line of output
  }
  Serial.println("");
}

void SegmentBlock::serialPrint() {
    //Serial.println("SegmentBlock::serialPrint");
  for (size_t y = 0; y < SEGMENT_BLOCK_HEIGHT; ++y) {
    for (size_t x = 0; x < SEGMENT_BLOCK_WIDTH; ++x) {
      long v = this->get(x, y);
      if (v > 0) {
        Serial.print(v);
      } else {
        Serial.print('.');
      }

      Serial.print("");
    }
    Serial.println(""); // start new line of output
  }
  Serial.println("");
}

int SegmentBlock::loop(uint8_t *buffer, size_t size) {
  // Serial.println("SegmentBlock::loop");
  for (size_t i = 0; i < size; ++i)
    this->loadPartialBuffer(buffer[i], this->currentBufferPosition + i);
  this->currentBufferPosition += size;
  return 1;
}

long SegmentBlock::get(size_t x, size_t y) { return this->segment[x][y]; }

void SegmentBlock::set(size_t x, size_t y, long value) {
  this->segment[x][y] = value;
}
