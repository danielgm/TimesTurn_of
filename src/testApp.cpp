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

  SerialTickReader* serialTickReader = new SerialTickReader();
  serialTickReader->setup(serial, 2);
  tickReader = serialTickReader;
//*/

  tickInterpreter.setup(tickReader, 2);

  ofxSparkline::Settings settings;
  settings.width = 200;
  settings.annotations.label.display = true;
  settings.annotations.label.text = "{V}";
  settings.annotations.label.precision = 4;
  settings.axes.y.range.min = 0;
  settings.axes.y.range.max = 0.015;
  settings.styles.curve.area.display = true;
  spark = ofxSparkline(settings, 200);

  ps3eye = new ofxMacamPs3Eye();
  ps3eye->initGrabber(320, 240, false);

  distortionist.setup(ps3eye);
  drawImage.allocate(frameWidth, frameHeight, OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void testApp::update(){
  tickInterpreter.update();
  spark.push_back(tickInterpreter.getVelocity(0));

  distortionist.update();
  if (distortionist.isFrameNew()) {
    drawImage.setFromPixels(distortionist.getPixels(), frameWidth, frameHeight, OF_IMAGE_COLOR);
  }
}

//--------------------------------------------------------------
void testApp::draw(){
  ofBackground(255, 128, 0);

  ps3eye->draw(5, 100, 320, 240);
  drawImage.draw(330, 100, 320, 240);

  int currY = 5;
  ofPushMatrix();
  ofScale(3, 3);

  spark.draw(5, currY);
  currY += spark.getHeight() + 10;

  ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

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
