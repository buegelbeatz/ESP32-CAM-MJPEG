#include "JpegReader.h"

int callback(JPEGDRAW *pDraw) {
  yield();
  uint8_t *buffer = (uint8_t *)pDraw->pPixels;
  size_t size = pDraw->iWidth * pDraw->iHeight;
  return JpegReader::segmentBlock->loop(buffer, size);
}

void JpegReader::setup() { Serial.println("Setup JpegReader..."); }

SegmentBlock *JpegReader::segmentBlock = new SegmentBlock();

JpegReader::JpegReader() { this->motion = new Motion(); }

JpegReader::~JpegReader() {}

void JpegReader::loop(uint8_t *buffer, size_t size) {
  //Serial.println("JpegReader::loop");
  JpegReader::segmentBlock->setup();
  if (this->jpeg.openFLASH(buffer, size, callback)) {
    //Serial.println("this->jpeg.openRAM");
    JpegReader::segmentBlock->imageWidth = this->jpeg.getWidth() / JPEG_READER_IMAGE_DIVIDER;
    JpegReader::segmentBlock->imageHeight = this->jpeg.getHeight() / JPEG_READER_IMAGE_DIVIDER;
    JpegReader::segmentBlock->pixelPerSegment =
        (JpegReader::segmentBlock->imageWidth *
         JpegReader::segmentBlock->imageHeight) /
        (SEGMENT_BLOCK_WIDTH * SEGMENT_BLOCK_HEIGHT);
    // Serial.print("imageWidth = ");Serial.println(JpegReader::segmentBlock->imageWidth);
    // Serial.print("imageHeight = ");Serial.println(JpegReader::segmentBlock->imageHeight);
    // Serial.print("pixelPerSegment = ");Serial.println(JpegReader::segmentBlock->pixelPerSegment);
    this->jpeg.setPixelType(JPEG_READER_IMAGE_TYPE);
    if (this->jpeg.decode(0, 0, JPEG_READER_IMAGE_SIZE)) {
      //Serial.println("this->jpeg.decode");
      yield();
      this->motion->loop(JpegReader::segmentBlock);
      //Serial.println("this->motion->loop done");
    }
    this->jpeg.close();
    //Serial.println("this->jpeg.close");
  }
  //free (current_frame_buffer);
}
