//
//  ParticleStroke.h
//  performance
//
//  Created by Gal Sasson on 4/18/14.
//
//

#ifndef __performance__ParticleStroke__
#define __performance__ParticleStroke__

#include <iostream>
#include "ofMain.h"
#include "FlowField.h"
#include "Particle.h"

class ParticleStroke
{
public:
    ParticleStroke();
    ~ParticleStroke();
    void addPoint(const ofVec2f& p);
    
    void update();
    void draw();
    
    void applyFlowField(const FlowField& flowField);
    
private:
    vector<Particle*> points;
    
};

#endif /* defined(__performance__ParticleStroke__) */
