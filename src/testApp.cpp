#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  // TODO: Factor out these values.
  frameWidth = 320;
  frameHeight = 240;

/*
  RecordedTickReader* recordedTickReader = new RecordedTickReader();
  recordedTickReader->setup("longsteady.csv", 2);
  tickReader = recordedTickReader;
/*/
  serial.listDevices();
  serial.setup(0, 9600);

  serialTickReader = new SerialTickReader();
  serialTickReader->setup(serial, 2);
  tickReader = serialTickReader;
//*/

  tickInterpreter.setup(tickReader, 2);

  isSparkPlaying = true;

  ofxSparkline::Settings settings;
  settings.width = 200;
  settings.annotations.label.display = true;
  settings.annotations.label.text = "Raw 0\n{V}";
  settings.annotations.label.precision = 4;
  settings.axes.y.range.min = 0;
  settings.axes.y.range.max = 1024;
  settings.styles.curve.area.display = true;
  rawSpark0 = ofxSparkline(settings, 200);

  settings = ofxSparkline::Settings();
  settings.width = 200;
  settings.annotations.label.display = true;
  settings.annotations.label.text = "Raw 1\n{V}";
  settings.annotations.label.precision = 4;
  settings.axes.y.range.min = 0;
  settings.axes.y.range.max = 1024;
  settings.styles.curve.area.display = true;
  rawSpark1 = ofxSparkline(settings, 200);

  settings = ofxSparkline::Settings();
  settings.width = 200;
  settings.annotations.label.display = true;
  settings.annotations.label.text = "Threshold 0\n{V}";
  settings.annotations.label.precision = 4;
  settings.axes.y.range.min = -1;
  settings.axes.y.range.max = 1;
  settings.styles.curve.area.display = true;
  thresholdSpark0 = ofxSparkline(settings, 200);

  settings = ofxSparkline::Settings();
  settings.width = 200;
  settings.annotations.label.display = true;
  settings.annotations.label.text = "Threshold 1\n{V}";
  settings.annotations.label.precision = 4;
  settings.axes.y.range.min = -1;
  settings.axes.y.range.max = 1;
  settings.styles.curve.area.display = true;
  thresholdSpark1 = ofxSparkline(settings, 200);

  settings = ofxSparkline::Settings();
  settings.width = 200;
  settings.annotations.label.display = true;
  settings.annotations.label.text = "Threshold range 0\n{V}";
  settings.annotations.label.precision = 4;
  settings.axes.y.range.min = serialTickReader->getLowerThreshold(0);
  settings.axes.y.range.max = serialTickReader->getUpperThreshold(0);
  settings.styles.curve.area.display = true;
  thresholdRangeSpark0 = ofxSparkline(settings, 200);

  settings = ofxSparkline::Settings();
  settings.width = 200;
  settings.annotations.label.display = true;
  settings.annotations.label.text = "Threshold range 1\n{V}";
  settings.annotations.label.precision = 4;
  settings.axes.y.range.min = serialTickReader->getLowerThreshold(1);
  settings.axes.y.range.max = serialTickReader->getUpperThreshold(1);
  settings.styles.curve.area.display = true;
  thresholdRangeSpark1 = ofxSparkline(settings, 200);

  settings = ofxSparkline::Settings();
  settings.width = 200;
  settings.annotations.label.display = true;
  settings.annotations.label.text = "Velocity 0\n{V}";
  settings.annotations.label.precision = 4;
  settings.axes.y.range.min = 0;
  settings.axes.y.range.max = 0.015;
  settings.styles.curve.area.display = true;
  velocitySpark0 = ofxSparkline(settings, 200);

  settings = ofxSparkline::Settings();
  settings.width = 200;
  settings.annotations.label.display = true;
  settings.annotations.label.text = "Velocity 1\n{V}";
  settings.annotations.label.precision = 4;
  settings.axes.y.range.min = 0;
  settings.axes.y.range.max = 0.015;
  settings.styles.curve.area.display = true;
  velocitySpark1 = ofxSparkline(settings, 200);

  ps3eye = new ofxMacamPs3Eye();
  ps3eye->initGrabber(320, 240, false);

  distortionist.setup(ps3eye);
  drawImage.allocate(frameWidth, frameHeight, OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void testApp::update(){
  tickInterpreter.update();

  if (isSparkPlaying) {
    rawSpark0.push_back(serialTickReader->getReading(0));
    rawSpark1.push_back(serialTickReader->getReading(1));
    thresholdSpark0.push_back((serialTickReader->getReading(0) > serialTickReader->getUpperThreshold(0))
          ? 1 : (serialTickReader->getReading(0) < serialTickReader->getLowerThreshold(0)) ? -1 : 0);
    thresholdSpark1.push_back((serialTickReader->getReading(1) > serialTickReader->getUpperThreshold(1))
          ? 1 : (serialTickReader->getReading(1) < serialTickReader->getLowerThreshold(1)) ? -1 : 0);
    thresholdRangeSpark0.push_back(serialTickReader->getReading(0));
    thresholdRangeSpark1.push_back(serialTickReader->getReading(1));
    velocitySpark0.push_back(tickInterpreter.getVelocity(0));
    velocitySpark1.push_back(tickInterpreter.getVelocity(1));
  }

  distortionist.update();
  if (distortionist.isFrameNew()) {
    drawImage.setFromPixels(distortionist.getPixels(), frameWidth, frameHeight, OF_IMAGE_COLOR);
  }
}

//--------------------------------------------------------------
void testApp::draw(){
  ofBackground(255, 128, 0);

  ps3eye->draw(5, 5, 320, 240);
  drawImage.draw(330, 5, 320, 240);

  int currY = 250 / 2;
  ofPushMatrix();
  ofScale(2, 2);

  rawSpark0.draw(5, currY);
  currY += rawSpark0.getHeight() + 10;

  rawSpark1.draw(5, currY);
  currY += rawSpark1.getHeight() + 10;

  thresholdSpark0.draw(5, currY);
  currY += thresholdSpark0.getHeight() + 10;

  thresholdSpark1.draw(5, currY);
  currY += thresholdSpark1.getHeight() + 10;

  thresholdRangeSpark0.draw(5, currY);
  currY += thresholdRangeSpark0.getHeight() + 10;

  thresholdRangeSpark1.draw(5, currY);
  currY += thresholdRangeSpark1.getHeight() + 10;

  velocitySpark0.draw(5, currY);
  currY += velocitySpark0.getHeight() + 10;

  velocitySpark1.draw(5, currY);
  currY += velocitySpark1.getHeight() + 10;

  ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
  switch (key) {
    case ' ':
      isSparkPlaying = !isSparkPlaying;
      break;
  }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
  distortionist.setIntensity(ofClamp(ofMap(x, 0, ofGetWidth(), 0, 1), 0, 1));
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
