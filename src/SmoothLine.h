//
//  SmoothLine.h
//  performance
//
//  Created by Gal Sasson on 4/21/14.
//
//

#ifndef __performance__SmoothLine__
#define __performance__SmoothLine__

#include <iostream>
#include "ofMain.h"
#include "ResourceManager.h"

class SmoothLine
{
public:
    SmoothLine();
    ~SmoothLine();
    
    void addPoint(float x, float y);
    
    void draw();
    
    vector<ofVec3f>& getPoints() { return points; }
    
private:
    void makeMesh();
    
    vector<ofVec3f> points;
    
    ofMesh mesh;
};

#endif /* defined(__performance__SmoothLine__) */
