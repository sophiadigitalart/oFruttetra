#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofEnableAlphaBlending();

	videoPlayer.loadMovie("movies/fingers.mov");
	videoPlayer.play();
	ofSetWindowTitle("RuttEtra");


	// initialize Spout with a sender name, and a texture size
	//ofxSpout::init("RuttEtra sender", ofGetWidth(), ofGetHeight(), true);

	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	fbo.begin();
	ofClear(0);
	fbo.end();

	//tweakable shizz
	xStep = 204;
	yStep = 153;

	amp = 0.4;
	threshold = 50;


	//white on black
	lineColor = ofColor(255, 255, 255, 150);
	fillColor = ofColor(0, 0, 0, 255);
	webcam.initGrabber(1280, 720);
	//black on white
	//lineColor = ofColor(0, 0, 0, 255);
	//fillColor = ofColor(255, 255, 255, 255);

	//assign pixel colour to line segments
	color = true;

}

//--------------------------------------------------------------
void ofApp::update() {
	videoPlayer.update();
	webcam.update();
	pixels = videoPlayer.getPixelsRef();
}

//--------------------------------------------------------------
void ofApp::draw() {
	// init sender if it's not already initialized
	//ofxSpout::initSender();

	fbo.begin();
	ofClear(fillColor);


	ofSetColor(lineColor);

	int stepWidth = ofGetWidth() / xStep;
	int stepWidthCam = videoPlayer.getWidth() / xStep;

	int stepHeight = ofGetHeight() / yStep;
	int stepHeightCam = videoPlayer.getHeight() / yStep;


	ofSetColor(lineColor);
	ofSetLineWidth(3);

	int cY = 0;
	
	for (cY = 0; cY < yStep; cY++)
	{

		ofPoint lastpoint;;
		ofColor currentColor;

		for (int i = 1; i < xStep; i++)
		{

			currentColor = pixels.getColor(i * stepWidthCam, cY * stepHeightCam);
			ofPoint thisPoint(i * stepWidth, cY * stepHeight - currentColor.getBrightness() * amp + stepHeight);


			if (currentColor.getBrightness() >= threshold)
			{
				//apply pixel colour to line segement.
			if (color)
				{
					currentColor = ofColor(currentColor[0], currentColor[1], currentColor[2], 200);
					ofSetColor(currentColor);
				}
				else
				{
					//adjust alpha of line segement according to brightness of pixel
					ofSetColor(lineColor.r, lineColor.g, lineColor.b, ofMap(currentColor.getBrightness(), threshold, 255, 0, 255));
				}

				if (i == 1)
				{
					lastpoint = thisPoint;
				}

				ofLine(lastpoint[0], lastpoint[1], thisPoint[0], thisPoint[1]);

			}
			lastpoint = thisPoint;

		}
	}
	
	fbo.end();

	//Shader ready to do any post required.

	//shader.begin();
	//shader.setUniformTexture( "tex0", fbo.getTextureReference(), 0 );
	ofSetColor(255);
	fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
	webcam.draw(500, 0);
	//shader.end();
	videoPlayer.draw(20, 20);
	// send screen to Spout
	
	spout.sendTexture(webcam.getTexture(), "RuttEtra");
}
void ofApp::exit() {
	spout.exit();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
