//
//  RepeatableStroke.h
//  performance
//
//  Created by Gal Sasson on 4/19/14.
//
//

#ifndef __performance__RepeatableStroke__
#define __performance__RepeatableStroke__

#include <iostream>
#include "ofMain.h"
#include "Params.h"

class RepeatableStroke
{
public:
    RepeatableStroke();
    ~RepeatableStroke();
    void addPoint(const ofVec2f& p);
    void update();
    void draw();
    
    static void initTransformations();
    
private:
    vector<ofVec2f*> points;
    static vector<ofVec2f> translates;
    static vector<ofVec2f> scales;
    static vector<float> rotations;
    
    ofVec2f anchor;
};


#endif /* defined(__performance__RepeatableStroke__) */