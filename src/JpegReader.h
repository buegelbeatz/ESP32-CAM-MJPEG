#ifndef JpegReader_h
#define JpegReader_h 1

#include "header.h"
#include <JPEGDEC.h>
// https://github.com/bitbank2/JPEGDEC/wiki
// https://github.com/bitbank2/JPEGDEC/blob/master/examples/M5Stack/M5StickCPlus/M5StickCPlus.ino
#include "SegmentBlock.h"
#include "Motion.h"
#include <string>
using namespace std;

#define JPEG_READER_IMAGE_TYPE    EIGHT_BIT_GRAYSCALE
#define JPEG_READER_IMAGE_SIZE    JPEG_SCALE_QUARTER
#define JPEG_READER_IMAGE_DIVIDER 4

class JpegReader {
public:
  JpegReader();
  virtual ~JpegReader();
  virtual void setup();
  virtual void loop(uint8_t *buffer, size_t size);
//protected:
  //virtual int callback(JPEGDRAW *pDraw);
  static SegmentBlock *segmentBlock;
  string clusterInfo = "";
private:
  //static SegmentBlock *segmentBlock;
  Motion *motion;
  JPEGDEC jpeg;
};

#endif
