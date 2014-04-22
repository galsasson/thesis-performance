//
//  Params.cpp
//  performance
//
//  Created by Gal Sasson on 4/13/14.
//
//

#include "Params.h"

float Params::angleOffset = 0;
float Params::angleOffsetPerIndex = 0;

float Params::lengthScale = 1;
float Params::lengthIndexScale = 1;

float Params::repeatTimes = 50;
float Params::repeatRotateCoeff = 1;
float Params::repeatScaleXCoeff = 1;
float Params::repeatScaleYCoeff = 1;
float Params::repeatTransXCoeff = 1;
float Params::repeatTransYCoeff = 1;

ofVec2f Params::springGravity(0, 1);
float Params::springForceFactor = 1;
float Params::springRestLengthFactor = 0.005;
ofVec2f Params::springTemporalForce(0, 0);
float Params::springCoeff = 0.61;

float Params::particleMaxSpeed = 45;
float Params::particleFrictionCoeff = 0.96f;
ofVec2f Params::particleTemporalVelocity(0, 0);

ofColor Params::springStrokeColor(50);//, 20, 38);