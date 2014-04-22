//
//  Particle.h
//  performance
//
//  Created by Gal Sasson on 4/18/14.
//
//

#ifndef __performance__Particle__
#define __performance__Particle__

#include <iostream>
#include "ofMain.h"
#include "Params.h"

class Particle : public ofVec2f
{
public:
    Particle();
    Particle(float x, float y, float mass=1);
    Particle(const ofVec2f& p, float mass=1);
    
    void setup();
    
    void applyForce(ofVec2f force);
    void update();
    void draw();
    
    void checkBounds();
    
    void setColor(ofColor c);

    float mass;
    bool locked;

private:
    float maxSpeed;
    ofVec2f vel;
    ofVec2f acc;
    
    ofColor color;
};

#endif /* defined(__performance__Particle__) */
