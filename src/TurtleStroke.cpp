//
//  TurtleStroke.cpp
//  performance
//
//  Created by Gal Sasson on 4/13/14.
//
//

#include "TurtleStroke.h"

TurtleStroke::TurtleStroke()
{
    privateSeed = ofRandom(1000);
}

TurtleStroke::~TurtleStroke()
{
    for (int i=0; i<steps.size(); i++)
    {
        delete steps[i];
    }
    
    steps.clear();
}

void TurtleStroke::setup(ofVec3f p)
{
    anchor = p;
}


void TurtleStroke::addPoint(ofVec3f p)
{
    ofVec3f lastPoint = getWorldSpace(steps.size()-1);
    
    ofVec3f diff = (p-lastPoint);
    float distance = diff.length();
    float angle = atan2(diff.y, diff.x);
    steps.push_back(new TurtleStep(angle, distance));
}

void TurtleStroke::update()
{
    for (int i=0; i<steps.size(); i++)
    {
        steps[i]->angleOffset = Params::angleOffset + (Params::angleIndexOffset*i) + sin(privateSeed + Params::angleIndexOffset2*i);
        steps[i]->lengthScale = Params::lengthScale * (pow(Params::lengthIndexScale,i));
    }
}

void TurtleStroke::draw()
{
    ofBeginShape();
    ofVertex(anchor);
    for (int i=0; i<steps.size(); i++)
    {
        ofVec3f pos = getWorldSpace(i);
        ofVertex(pos);
    }
    ofEndShape();
}

ofVec3f TurtleStroke::getWorldSpace(int index)
{
    ofVec3f pos = anchor;
    
    for (int i=0; i<=index; i++) {
        ofVec3f s(steps[i]->getLength(), 0, 0);
        s.rotate(steps[i]->getAngleDeg(), ofVec3f(0, 0, 1));
        pos += s;
    }
    
    return pos;
}