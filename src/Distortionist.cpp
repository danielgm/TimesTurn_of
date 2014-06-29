#include "Distortionist.h"

void Distortionist::setup(ofBaseVideoGrabber* grabber) {
  videoGrabber = grabber;

  // TODO: Factor these values out.
  maxFrameCount = 255;
  frameCount = 0;
  frameIndex = -1;
  frameWidth = 320;
  frameHeight = 240;

  inputPixels = new unsigned char[maxFrameCount * frameWidth * frameHeight * 3];
  outputPixels = new unsigned char[frameWidth * frameHeight * 3];
}

void Distortionist::update() {
  videoGrabber->update();
  if (videoGrabber->isFrameNew()) {
    frameCount++;
    if (frameCount > maxFrameCount) frameCount = maxFrameCount;

    frameIndex++;
    if (frameIndex >= frameCount) frameIndex = 0;

    unsigned char* pixels = videoGrabber->getPixels();

    // Copy pixels from video grabber into our array.
    for (int x = 0; x < frameWidth; ++x) {
      for (int y = 0; y < frameHeight; ++y) {
        int i = (y * frameWidth + x);
        for (int c = 0; c < 3; ++c) {
          inputPixels[frameIndex * frameWidth * frameHeight * 3 + i * 3 + c] = pixels[i * 3 + c];
        }
      }
    }

    for (int x = 0; x < frameWidth; ++x) {
      for (int y = 0; y < frameHeight; ++y) {
        int i = (y * frameWidth + x);
        int f = (frameIndex + (int)ofMap(x, 0, frameWidth, 0, frameCount)) % frameCount;
        for (int c = 0; c < 3; ++c) {
          outputPixels[i * 3 + c] = inputPixels[f * frameWidth * frameHeight * 3 + i * 3 + c];
        }
      }
    }
  }
}

bool Distortionist::isFrameNew() {
  return videoGrabber->isFrameNew();
}

unsigned char* Distortionist::getPixels() {
  return outputPixels;
}
