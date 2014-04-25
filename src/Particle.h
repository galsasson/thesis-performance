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
#include "ResourceManager.h"
#include "Params.h"

class Particle : public ofVec2f
{
public:
    Particle();
    Particle(float x, float y, float mass=1);
    Particle(const ofVec2f& p, float mass=1);
    
    void setup();
    
    void applyForce(const ofVec2f& force);
    void applyGravity(const ofVec2f& gravity);
    void update();
    void draw();
    
    void checkBounds();
    
    void setColor(const ofColor& c) { materialColor = c; }
    ofColor& getColor() { return materialColor.lerp(tempColor, tempColorIntensity); }
    ofColor& getMaterialColor() { return materialColor; }
    
    void setTempColor(const ofColor& c) { tempColor = c; tempColorIntensity = 1; }
    
    float getSize() { return mSize; }
    float getRadius() { return mRadius; }
    
    static inline float getMassFromRadius(float rad) { return (rad/15)+1; }
    
    float mass;
    float stickiness;

private:
    float t;
    float maxSpeed;
    float mRadius;
    float mSize;
    
    ofVec2f vel;
    ofVec2f acc;
    
    ofColor materialColor;
    
    // temporal color
    ofColor tempColor;
    float tempColorIntensity;
};

#endif /* defined(__performance__Particle__) */
