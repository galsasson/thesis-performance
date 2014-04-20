//
//  Params.h
//  performance
//
//  Created by Gal Sasson on 4/13/14.
//
//

#ifndef __performance__Params__
#define __performance__Params__

#include <iostream>

class Params
{
public:
    static float angleOffset;
    static float angleOffsetPerIndex;
    
    static float lengthScale;
    static float lengthIndexScale;
    
    static float repeatTimes;
    static float repeatRotateCoeff;
    static float repeatScaleXCoeff;
    static float repeatScaleYCoeff;
    static float repeatTransXCoeff;
    static float repeatTransYCoeff;
};

#endif /* defined(__performance__Params__) */
