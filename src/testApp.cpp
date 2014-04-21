#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSeedRandom();
    ofSetFrameRate(60);
    ofHideCursor();
    CGDisplayHideCursor(NULL);
    
//    ofEnableSmoothing();
    ofSetBackgroundAuto(false);
    ofEnableAlphaBlending();
    
    control.setup("Performance", 6000);
    
//    control.addOutput("nStrokes", &canvas.nStrokes);
    control.addInput("Noise Level", &canvas.noiseLevel);
    control.addInput("Noise Rate", &canvas.noiseRate);
    control.addInput("Noise Spatial Rate", &canvas.noiseSpatialRate);
    control.addInput("Random Level", &canvas.randomLevel);
    control.addInput("X Frequency", &canvas.xFrequency);
    control.addInput("X Amplitude", &canvas.xAmplitude);
    control.addInput("Angle Offset", &Params::angleOffset);
    control.addInput("Angle Offset Per Index", &Params::angleOffsetPerIndex);
    control.addInput("lengthScale", &Params::lengthScale);
    control.addInput("lengthIndexScale", &Params::lengthIndexScale);
    
    control.addInput("Repeat Times", &Params::repeatTimes);
    control.addInput("Repeat rotation", &Params::repeatRotateCoeff);
    control.addInput("Repeat trans X", &Params::repeatTransXCoeff);
    control.addInput("Repeat trans Y", &Params::repeatTransYCoeff);
    control.addInput("Repeat scale X", &Params::repeatScaleXCoeff);
    control.addInput("Repeat scale Y", &Params::repeatScaleYCoeff);
    
    canvas.setup(ofGetWindowWidth(), ofGetWindowHeight());
}

//--------------------------------------------------------------
void testApp::update(){
    canvas.update();
}

//--------------------------------------------------------------
void testApp::draw(){
//    ofClear(0);
    canvas.draw();
    
    ofSetColor(50, 50, 50, 130);
    ofEllipse(ofGetMouseX(), ofGetMouseY(), 15, 15);
    
    stringstream ss;
    ss << ofGetFrameRate();
    ofDrawBitmapString(ss.str(), 0, ofGetWindowHeight());
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    cout << "key pressed: "<<key<<endl;
    canvas.keyPressed(key);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    canvas.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    canvas.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    canvas.mouseReleased(x, y, button);
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
