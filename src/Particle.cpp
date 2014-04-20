//
//  Particle.cpp
//  performance
//
//  Created by Gal Sasson on 4/18/14.
//
//

#include "Particle.h"

Particle::Particle() : ofVec2f()
{
    setup();
}

Particle::Particle(float x, float y) : ofVec2f(x, y)
{
    setup();
}

Particle::Particle(const ofVec2f& p) : ofVec2f(p)
{
    setup();
}

void Particle::setup()
{
    maxSpeed = 5;
    mass = ofRandom(1)+1;
    vel = ofVec2f();
    acc = ofVec2f();
}

void Particle::applyForce(ofVec2f force)
{
    acc += force/mass;
}

void Particle::update()
{
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

void Particle::setColor(ofColor c)
{
    color = c;
}

