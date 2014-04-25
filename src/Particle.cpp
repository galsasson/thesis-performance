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
    
    mSize = (mass-1)*30;
    mRadius = mSize/2;
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
    
//    ofSetColor(getColor());
    ofSetColor(ResourceManager::getInstance().getStrokeColor());
    ofEllipse(0, 0, getSize(), getSize());
    
    ofPopMatrix();
}

void Particle::checkBounds()
{
    if (y > ofGetWindowHeight()) {
        vel.y *= -0.8 + ofRandom(0.2);
        y = ofGetWindowHeight();
    }
    else if (y < 0) {
        vel.y *= -0.8 + ofRandom(0.2);
        y = 0;
    }
    
    if (x > ofGetWindowWidth()) {
        vel.x *= -0.8 + ofRandom(0.2);
        x = ofGetWindowWidth();
    }
    else if (x < 0) {
        vel.x *= -0.8 + ofRandom(0.2);
        x = 0;
    }
}

