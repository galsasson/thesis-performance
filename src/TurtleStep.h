//
//  TurtleStep.h
//  performance
//
//  Created by Gal Sasson on 4/13/14.
//
//

#ifndef __performance__TurtleStep__
#define __performance__TurtleStep__

#include <iostream>
#include "ofMain.h"

class TurtleStep
{
public:
    TurtleStep(float ang, float dist);
    
    float getAngleDeg() { return (angle + angleOffset)*180/PI; }
    
    float angle;
    float distance;
    
    float angleOffset;
};
#endif /* defined(__performance__TurtleStep__) */
