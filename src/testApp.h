#pragma once

#include "ofMain.h"
#include "ofxSparkline.h"

#include "RecordedTickReader.h"
#include "SerialTickReader.h"
#include "TickInterpreter.h"

class testApp : public ofBaseApp{

  public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

  void loadFrames(string folder);

  int frameCount;
  int frameWidth;
  int frameHeight;

  unsigned char* inputPixels;
  unsigned char* drawPixels;
  ofImage drawImage;

  ofSerial serial;
  ITickReader* tickReader;
  TickInterpreter tickInterpreter;

  ofxSparkline spark;
};
