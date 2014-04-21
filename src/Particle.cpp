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
    maxSpeed = 15;
    vel = ofVec2f();
    acc = ofVec2f();
    locked = false;
}

void Particle::applyForce(ofVec2f force)
{
    acc += force/mass;
}

void Particle::update()
{
    if (locked) {
        return;
    }
    
    vel += acc;
    vel.limit(maxSpeed);
    
    x += vel.x;
    y += vel.y;
    
    vel *= 0.99;
    
    acc *= 0;
}

void Particle::draw()
{
    ofPushMatrix();
    ofTranslate(x, y);
    
    ofSetColor(color);
    ofEllipse(0, 0, 15, 15);
    
    ofPopMatrix();
}

void Particle::checkBounds()
{
    if (y > ofGetWindowHeight()) {
        vel.y *= -1;
        y = ofGetWindowHeight();
    }
}

void Particle::setColor(ofColor c)
{
    color = c;
}

