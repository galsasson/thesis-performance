//
//  Particle.cpp
//  performance
//
//  Created by Gal Sasson on 4/18/14.
//
//

#include "Particle.h"

Particle::Particle() : ofVec2f(), mass(1)
{
    setup();
}

Particle::Particle(float x, float y, float m) : ofVec2f(x, y), mass(m)
{
    setup();
}

Particle::Particle(const ofVec2f& p, float m) : ofVec2f(p), mass(m)
{
    setup();
}

void Particle::setup()
{
    vel = ofVec2f();
    acc = ofVec2f();
    locked = false;
    materialColor = ofColor(50);
    tempColor = ofColor(50);
    tempColorIntensity = 0;
    t = ofRandom(1000);
}

void Particle::applyForce(const ofVec2f& force)
{
    acc += force/mass;
}

void Particle::applyGravity(const ofVec2f& gravity)
{
    acc += gravity;
}

void Particle::update()
{
    t += 0.1;
    
    // color
    if (tempColorIntensity>0) {
        tempColorIntensity -= ofNoise(t)*0.1;
    }
    
    // movement
    if (locked) {
        return;
    }
    
    // apply temporal velocity
    vel += Params::particleTemporalVelocity;
    
    
    vel += acc;
    vel.limit(Params::particleMaxSpeed);
    
    x += vel.x;
    y += vel.y;
    
    vel *= Params::particleFrictionCoeff;
    
    acc *= 0;
}

void Particle::draw()
{
    ofPushMatrix();
    ofTranslate(x, y);
    
    ofSetColor(getColor());
    ofEllipse(0, 0, mass+10 + ofNoise(t)*10, mass+10 + ofNoise(t)*10);
    
    ofPopMatrix();
}

void Particle::checkBounds()
{
    if (y > ofGetWindowHeight()) {
        vel.y *= -0.8;
        y = ofGetWindowHeight();
    }
}

