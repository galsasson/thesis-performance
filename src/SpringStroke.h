//
//  SpringStroke.h
//  performance
//
//  Created by Gal Sasson on 4/21/14.
//
//

#ifndef __performance__SpringStroke__
#define __performance__SpringStroke__

#include <iostream>
#include "ofMain.h"
#include "SmoothLine.h"

class SpringStroke
{
    
public:
    
    SpringStroke();
    ~SpringStroke();
    void addPoint(float x, float y);
    
    void update();
    void draw();
    
private:
    SmoothLine line;
};


#endif /* defined(__performance__SpringStroke__) */
