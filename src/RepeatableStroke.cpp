//
//  RepeatableStroke.cpp
//  performance
//
//  Created by Gal Sasson on 4/19/14.
//
//

#include "RepeatableStroke.h"

vector<float> RepeatableStroke::rotations;
vector<ofVec2f> RepeatableStroke::translates;
vector<ofVec2f> RepeatableStroke::scales;

RepeatableStroke::RepeatableStroke()
{
}

RepeatableStroke::~RepeatableStroke()
{
}

void RepeatableStroke::initTransformations()
{
    for (int i=0; i<1000; i++)
    {
        RepeatableStroke::rotations.push_back(ofRandom(360));
        RepeatableStroke::translates.push_back(ofVec2f(ofRandom(-400, 400), ofRandom(-400, 400)));
        RepeatableStroke::scales.push_back(ofVec2f(ofRandom(0.1, 0.6), ofRandom(0.1, 0.6)));
    }
}

void RepeatableStroke::addPoint(const ofVec2f& p)
{
    if (line.getPoints().size() == 0) {
        anchor = ofVec2f(p);
    }
    
    line.addPoint(p.x-anchor.x, p.y-anchor.y);
}

void RepeatableStroke::update()
{
    
}

void RepeatableStroke::draw()
{
    ofNoFill();
    ofSetColor(50);
    ofPushMatrix();
    ofTranslate(anchor);
    
    line.draw();

    for (int i=0; i<Params::repeatTimes; i++)
    {
        ofPushMatrix();
        ofRotate(RepeatableStroke::rotations[i] * Params::repeatRotateCoeff);
        ofTranslate(RepeatableStroke::translates[i].x * Params::repeatTransXCoeff, RepeatableStroke::translates[i].y * Params::repeatTransYCoeff);
        ofScale(RepeatableStroke::scales[i].x * Params::repeatScaleXCoeff, RepeatableStroke::scales[i].y * Params::repeatScaleYCoeff);
        line.draw();
        ofPopMatrix();
    }
    ofPopMatrix();
}
