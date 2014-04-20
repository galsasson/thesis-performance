//
//  FlowField.cpp
//  performance
//
//  Created by Gal Sasson on 4/17/14.
//
//

#include "FlowField.h"

FlowField::FlowField()
{
    field = NULL;
}

FlowField::~FlowField()
{
    if (field) {
        for (int i=0; i<nWidth; i++)
        {
            delete field[i];
        }
        delete field;
    }
}

void FlowField::setup(int w, int h, int nw, int nh)
{
    size = ofVec2f(w, h);
    squareSize = ofVec2f(size.x / nw, size.y / nh);
    nWidth = nw+1;
    nHeight = nh+1;
    
    
    field = new ofVec2f*[nWidth];
    for (int i=0; i<nWidth; i++)
    {
        field[i] = new ofVec2f[nHeight];
    }
    
    reset();
}

void FlowField::update()
{
    
}

void FlowField::draw()
{
    ofSetColor(150);
    for (int x=0; x<nWidth; x++)
    {
        for (int y=0; y<nHeight; y++)
        {
            drawArrow(squareSize * ofVec2f(x, y), field[x][y]);
        }
    }
}

void FlowField::reset()
{
    for (int x=0; x<nWidth; x++)
    {
        for (int y=0; y<nHeight; y++)
        {
            field[x][y] = ofVec2f(0, 1);
        }
    }
}

void FlowField::addAttractor(ofVec2f p, float rad, float force)
{
    for (int x=0; x<nWidth; x++)
    {
        for (int y=0; y<nHeight; y++)
        {
            ofVec2f pos = ofVec2f(x, y)*squareSize;
            ofVec2f offset = p-pos;
            float distance = offset.length();
            if (distance < rad) {
                float f = (rad - distance) / rad * force;
                offset.normalize();
                field[x][y] += offset * f;
                field[x][y].limit(10);
            }
        }
    }
}

void FlowField::addForce(ofVec2f p, float rad, ofVec2f force)
{
    for (int x=0; x<nWidth; x++)
    {
        for (int y=0; y<nHeight; y++)
        {
            ofVec2f pos = ofVec2f(x, y)*squareSize;
            ofVec2f offset = p-pos;
            float distance = offset.length();
            if (distance < rad) {
                ofVec2f f = force * (rad - distance) / rad;
                field[x][y] += f;
//                offset.normalize();
//                field[x][y] += offset * f;
                field[x][y].limit(10);
            }
        }
    }
}

void FlowField::applyStrokeForces(Stroke* stroke)
{
    vector<ofVec2f*> points = stroke->getPoints();
    addAttractor(*points[0], 40, 1);
    
    for (int i=1; i<points.size(); i++)
    {
        addForce(*points[i], 40, (*points[i] - *points[i-1])/5);
    }
}

ofVec2f FlowField::getForce(ofVec2f p) const
{
    int x = (int)(p.x / squareSize.x);
    int y = (int)(p.y / squareSize.y);
    
    if (x >= nWidth ||
        y >= nHeight ||
        x<0 ||
        y<0) {
        return ofVec2f(0, 0);
    }
    
    // TODO: interpolate between four corners
    return field[x][y];
}

void FlowField::drawArrow(ofVec2f s, ofVec2f t)
{
    float length = t.length();
    if (length == 0) {
        ofLine(s, s+ofVec2f(1, 0));
        return;
    }
    
    ofPushMatrix();
    ofTranslate(s);
    
    ofRotate(ofRadToDeg(atan2(t.y, t.x)));
    ofLine(0, 0, length, 0);
    ofLine(length, 0, length-3, -2);
    ofLine(length, 0, length-3, 2);
    
    ofPopMatrix();
}


