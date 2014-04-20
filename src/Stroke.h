//
//  Stroke.h
//  performance
//
//  Created by Gal Sasson on 4/12/14.
//
//

#ifndef __performance__Stroke__
#define __performance__Stroke__

#include <iostream>
#include "ofMain.h"

class Stroke
{
public:
    Stroke();
    ~Stroke();
    void addPoint(const ofVec2f& p);
    
    vector<ofVec2f*>& getPoints();
    
private:
    vector<ofVec2f*> points;
};

#endif /* defined(__performance__Stroke__) */
