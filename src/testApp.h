#pragma once

#include "ofMain.h"
#include "ofxSparkline.h"

#include "Distortionist.h"
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

  int frameWidth;
  int frameHeight;

  ofxMacamPs3Eye* ps3eye;
  Distortionist distortionist;
  ofImage drawImage;

  ofSerial serial;
  SerialTickReader* serialTickReader;
  ITickReader* tickReader;
  TickInterpreter tickInterpreter;

  bool isSparkPlaying;
  ofxSparkline rawSpark0;
  ofxSparkline rawSpark1;
  ofxSparkline thresholdSpark0;
  ofxSparkline thresholdSpark1;
  ofxSparkline thresholdRangeSpark0;
  ofxSparkline thresholdRangeSpark1;
  ofxSparkline velocitySpark0;
  ofxSparkline velocitySpark1;
  ofxSparkline differenceSpark;
};
