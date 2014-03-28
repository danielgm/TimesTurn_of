#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	loadFrames("input");
	
	drawPixels = new unsigned char[frameWidth * frameHeight * 4];
}

//--------------------------------------------------------------
void testApp::update(){
	float leftValue = (float)mouseY / frameHeight;
	float rightValue = (float)mouseX / frameWidth;
	
	for (int w = 0; w < frameWidth; w++) {
		for (int h = 0; h < frameHeight; h++) {
			int frameIndex = ofClamp(ofMap(ofMap(w, 0, frameWidth, leftValue, rightValue), 0, 1, 0, frameCount), 0, frameCount);
			for (int c = 0; c < 4; c++) {
				drawPixels[frameWidth * h * 4 + w * 4 + c] = inputPixels[												   frameIndex * frameWidth * frameHeight * 4 + frameWidth * h * 4 + w * 4 + c];
			}
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(255, 128, 0);
	drawImage.setFromPixels(drawPixels, frameWidth, frameHeight, OF_IMAGE_COLOR_ALPHA);
	drawImage.draw(0, 0);
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

void testApp::loadFrames(string folder) {
	frameCount = 0;
	frameWidth = 0;
	frameHeight = 0;
	
	char indexString[5];
	sprintf(indexString, "%04d", frameCount + 1);

	ofFile file;
	sprintf(indexString, "%04d", frameCount + 1);
	while (file.doesFileExist(folder + "/frame" + indexString + ".jpg")) {
		frameCount++;
		sprintf(indexString, "%04d", frameCount + 1);
	}
	
	if (frameCount <= 0) return;
	
	// Determine image size from the first frame.
	ofImage image;
	image.loadImage(folder + "/frame0001.jpg");
	frameWidth = image.width;
	frameHeight = image.height;
	
	if (frameWidth <= 0 || frameHeight <= 0) return;
	
	cout << "Loading " << frameCount << " frames at " << frameWidth << "x" << frameHeight << "... ";
	
	if (inputPixels) delete[] inputPixels;
	inputPixels = new unsigned char[frameCount * frameWidth * frameHeight * 4];
	
	unsigned char* copyPixels;
	for (int frameIndex = 0; frameIndex < frameCount; frameIndex++) {
		sprintf(indexString, "%04d", frameIndex + 1);
		image.loadImage(folder + "/frame" + indexString + ".jpg");
		
		copyPixels = image.getPixels();
		for (int i = 0; i < frameWidth * frameHeight; i++) {
			inputPixels[frameIndex * frameWidth * frameHeight * 4 + i * 4 + 0] = copyPixels[i * 3 + 0];
			inputPixels[frameIndex * frameWidth * frameHeight * 4 + i * 4 + 1] = copyPixels[i * 3 + 1];
			inputPixels[frameIndex * frameWidth * frameHeight * 4 + i * 4 + 2] = copyPixels[i * 3 + 2];
			inputPixels[frameIndex * frameWidth * frameHeight * 4 + i * 4 + 3] = 255;
		}
	}
	
	cout << "done." << endl;
}