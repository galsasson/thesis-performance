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

class Particle : public ofVec2f
{
public:
    Particle();
    Particle(float x, float y);
    Particle(const ofVec2f& p);
    
    void setup();
    
    void applyForce(ofVec2f force);
    void update();
    void draw();
    
    void setColor(ofColor c);
    
private:
    float maxSpeed;
    float mass;
    ofVec2f vel;
    ofVec2f acc;
    
    ofColor color;
};

#endif /* defined(__performance__Particle__) */
