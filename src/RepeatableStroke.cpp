//
//  RepeatableStroke.cpp
//  performance
//
//  Created by Gal Sasson on 4/19/14.
//
//

#include "RepeatableStroke.h"

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
    for (int i=0; i<50; i++)
    {
        RepeatableStroke::translates.push_back(ofVec2f(ofRandom(-300, 300), ofRandom(-300, 300)));
        RepeatableStroke::scales.push_back(ofVec2f(ofRandom(0.1, 2), ofRandom(0.1, 2)));
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
    ofPushMatrix();
    ofTranslate(anchor);
    
    ofBeginShape();
    for (int i=0; i<points.size(); i++)
    {
        ofVertex(points[i]->x, points[i]->y);
    }
    ofEndShape();

    for (int i=0; i<50; i++)
    {
        ofPushMatrix();
        ofTranslate(RepeatableStroke::translates[i]);
        ofScale(RepeatableStroke::scales[i].x, RepeatableStroke::scales[i].y);
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
