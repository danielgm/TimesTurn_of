#pragma once

#include "ofMain.h"

class Distortionist {

  public:
    void setup(ofBaseVideoGrabber* videoGrabber);
    void update();
    bool isFrameNew();
    unsigned char* getPixels();

    /** Intensity of the distortion on a scale of 0 to 1. */
    void setIntensity(float intensity);

  private:
    ofBaseVideoGrabber* videoGrabber;

    /** The maximum number of frames that will be stored. */
    int maxFrameCount;

    /** The current frame count. Starts at zero and increments and wraps as frames are loaded. */
    int frameCount;

    /** The index of the most recent frame. Older frames have lower values. */
    int frameIndex;

    int frameWidth;
    int frameHeight;

    unsigned char* inputPixels;
    unsigned char* outputPixels;

    float intensity;
};
