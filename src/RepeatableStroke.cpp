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
    for (int i=0; i<points.size(); i++)
    {
        delete points[i];
    }
    points.clear();
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
    if (points.size() == 0) {
        anchor = ofVec2f(p);
    }
    
    points.push_back(new ofVec2f(p-anchor));
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
    
    ofBeginShape();
    for (int i=0; i<points.size(); i++)
    {
        ofVertex(points[i]->x, points[i]->y);
    }
    ofEndShape();

    for (int i=0; i<Params::repeatTimes; i++)
    {
        ofPushMatrix();
        ofRotate(RepeatableStroke::rotations[i] * Params::repeatRotateCoeff);
        ofTranslate(RepeatableStroke::translates[i].x * Params::repeatTransXCoeff, RepeatableStroke::translates[i].y * Params::repeatTransYCoeff);
        ofScale(RepeatableStroke::scales[i].x * Params::repeatScaleXCoeff, RepeatableStroke::scales[i].y * Params::repeatScaleYCoeff);
        ofBeginShape();
        for (int p=0; p<points.size(); p++)
        {
            ofVertex(points[p]->x, points[p]->y);
        }
        ofEndShape();
        ofPopMatrix();
    }
    ofPopMatrix();
}
