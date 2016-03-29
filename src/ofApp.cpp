#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	
	ofSetFrameRate(60);
	
	kinect.init(true);
	kinect.open();

	ofSetWindowShape(kinect.width * 2, kinect.height);
	
	db.allocate(kinect.width, kinect.height);
	
	
	willShoot = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	
	kinect.update();
	
	if (willClear) {
		db.clear();
		willClear  = false;
	}
	
	if (kinect.isFrameNew()) {
		
//		kinect.get
		ofTexture &rgbTex = kinect.getTexture();
		ofTexture &depthTex = kinect.getDepthTexture();
		
		db.blendDepth(depthTex);
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	
	int w = kinect.width;
	int h = kinect.height;
	
	ofClear(0);
	
	ofSetColor(255);
	
	db.draw(kinect.getTexture(), willShoot);
	
	willShoot = false;
	
	
//	db.pingPongMask.src->draw(w * 1.5, 0, w / 2, h / 2);
	
	db.bgTex.draw(w * 1.5, 0, w / 2, h / 2);
	db.pingPongMask.dst->draw(w * 1.5, h / 2, w / 2, h / 2);
	
	
	kinect.draw(w, 0, w / 2, h / 2);
	kinect.drawDepth(w, h / 2, w / 2, h / 2);


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	if (key == ' ') {
		willShoot = true;
	}


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
	cout << button << endl;
	
	if (button == 0) {
		willShoot = true;
	} else if (button == 2) {
		willClear = true;
	}

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
