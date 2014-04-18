//
//  FlowField.h
//  performance
//
//  Created by Gal Sasson on 4/17/14.
//
//

#ifndef __performance__FlowField__
#define __performance__FlowField__

#include <iostream>
#include "ofMain.h"

class FlowField
{
public:
    FlowField();
    ~FlowField();
    void setup(int w, int h, int nWidth, int nHeight);
    void update();
    void draw();
    
    void addAttractor(ofVec2f p, float rad, float force);
    ofVec2f getForce(ofVec2f p) const;
    
private:
    int nWidth, nHeight;
    ofVec2f size;
    ofVec2f squareSize;
    ofVec2f **field;
    
    void drawArrow(ofVec2f s, ofVec2f t);
};

#endif /* defined(__performance__FlowField__) */
