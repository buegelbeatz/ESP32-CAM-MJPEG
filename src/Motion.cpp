#include "Motion.h"
#include "JpegReader.h"

void Motion::analyzeSegment(size_t x, size_t y, size_t dx, size_t dy, int number = 1) {
  if (this->markedBlock->get(x, y) == 0) {
    if ((abs(this->currentBlock->get(x, y) - this->backupBlock->get(x, y)) / this->backupBlock->pixelPerSegment) > MOTION_THERESOLD) {
      this->markedBlock->set(x, y, 1);
    } else {
      int xCheckPossible = ((dx > 0 && x > 0) || (dx < 0 && x < SEGMENT_BLOCK_WIDTH - 1)) ? 1 : 0;
      int yCheckPossible = ((dy > 0 && y > 0) || (dy < 0 && y < SEGMENT_BLOCK_HEIGHT - 1)) ? 1 : 0;
      if (xCheckPossible && yCheckPossible &&
          this->markedBlock->get(x - dx, y) > 0 &&
          this->markedBlock->get(x, y - dy) > 0) {
        this->markedBlock->set(x, y, number);
      } else {
        int xCheckNextPossible = ((dx > 0 && x < SEGMENT_BLOCK_WIDTH - 1) || (dx < 0 && x > 0)) ? 1 : 0;

        if (xCheckPossible && xCheckNextPossible &&
            this->markedBlock->get(x - dx, y) > 0 &&
            this->markedBlock->get(x + dx, y) > 0) {
          this->markedBlock->set(x, y, number);
        } else {
          int yCheckNextPossible = ((dy > 0 && y < SEGMENT_BLOCK_HEIGHT - 1) || (dy < 0 && y > 0)) ? 1 : 0;
          if (yCheckPossible && yCheckNextPossible &&
              this->markedBlock->get(x, y - dy) > 0 &&
              this->markedBlock->get(x, y + dy) > 0) {
            this->markedBlock->set(x, y, number);
          }
        }
      }
    }
  }
}

Motion::~Motion() {}

void Motion::setup() { Serial.println("Setup Motion..."); }

Motion::Motion() {
  this->backupBlock = new SegmentBlock();
  this->markedBlock = new SegmentBlock();
  this->currentBlock = new SegmentBlock();
}

void Motion::loop(SegmentBlock *analyzeBlock) {
  this->currentBlock->clone(analyzeBlock);
  delete this->markedBlock;
  this->markedBlock = new SegmentBlock();
  if (this->initialized) {
    this->clusterCount = 0;
    this->clusterInfo = "";
    for (size_t y = 0; y < SEGMENT_BLOCK_HEIGHT; ++y)
      for (size_t x = 0; x < SEGMENT_BLOCK_WIDTH; ++x) {
        yield();
        this->analyzeSegment(x, y, 1, 1, 1);
        this->analyzeSegment(SEGMENT_BLOCK_WIDTH - x - 1, y, -1, 1, 2);
        this->analyzeSegment(x, SEGMENT_BLOCK_HEIGHT - y - 1, 1, -1, 3);
        this->analyzeSegment(SEGMENT_BLOCK_WIDTH - x - 1,
                             SEGMENT_BLOCK_HEIGHT - y - 1, -1, -1, 4);
      }
    for (size_t y = 0; y < SEGMENT_BLOCK_HEIGHT - 3; ++y)
      for (size_t x = 0; x < SEGMENT_BLOCK_WIDTH - 3; ++x) {
        if (this->markedBlock->get(x, y) > 0 &&
            (x == 0 || this->markedBlock->get(x - 1, y) == 0) &&
            (y == 0 || this->markedBlock->get(x, y - 1) == 0)) {
          size_t dx = 0;
          size_t dy = 0;
          for (dx = x + 1; dx < SEGMENT_BLOCK_WIDTH; ++dx) {
            if (this->markedBlock->get(dx, y) == 0) {
              dx = dx - x;
              break;
            }
          }
          if (dx > 2 && dx < (SEGMENT_BLOCK_WIDTH / 3)) {
            for (dy = y + 1; dy < SEGMENT_BLOCK_HEIGHT; ++dy) {
              if (this->markedBlock->get(x, dy) == 0) {
                dy = dy - y;
                break;
              }
            }
            if (dy > 2 && dy < (SEGMENT_BLOCK_HEIGHT / 3)) {
              if(this->clusterCount <= MOTION_CLUSTER_MAX){
                this->clusterInfo += to_string(x * this->currentBlock->imageWidth * JPEG_READER_IMAGE_DIVIDER / SEGMENT_BLOCK_WIDTH) + "," +
                to_string(y * this->currentBlock->imageHeight * JPEG_READER_IMAGE_DIVIDER / SEGMENT_BLOCK_HEIGHT) + "," +
                to_string(dx * this->currentBlock->imageWidth * JPEG_READER_IMAGE_DIVIDER / SEGMENT_BLOCK_WIDTH) + "," +
                to_string(dy * this->currentBlock->imageHeight * JPEG_READER_IMAGE_DIVIDER / SEGMENT_BLOCK_HEIGHT) + ";";
                this->clusterCount += 1;
              }
            }
          }
        }
      }
  }
  this->backupBlock->clone(analyzeBlock);
  this->initialized = 1;
}
