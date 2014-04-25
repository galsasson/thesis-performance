//
//  ParticleStroke.cpp
//  performance
//
//  Created by Gal Sasson on 4/18/14.
//
//

#include "ParticleStroke.h"

ParticleStroke::ParticleStroke()
{
    t = ofRandom(1000);
}

ParticleStroke::~ParticleStroke()
{
    for (int i=0; i<points.size(); i++)
    {
        delete points[i];
    }
    points.clear();
}

void ParticleStroke::addPoint(const ofVec2f &p)
{
    float mass = 1;
    if (!points.empty()) {
        float radFromLast = getDistanceToClosestParticle(p) * 0.8;
        mass = Particle::getMassFromRadius(radFromLast);
        if (mass > 2) {
            mass = 2;
        }
    }
    else {
        mass = ofRandom(1)+1;
    }
    
    Particle *newP = new Particle(p, mass);
    newP->setColor(Params::springStrokeColor);
    points.push_back(newP);
}

void ParticleStroke::update()
{
    for (int i=0; i<points.size(); i++)
    {
        points[i]->applyGravity(Params::particleGravity);
        points[i]->update();
        points[i]->checkBounds();
    }
    
    t+=0.1;
}

void ParticleStroke::draw()
{
    ofFill();
    for (int i=0; i<points.size(); i++)
    {
        points[i]->draw();
    }
}

void ParticleStroke::applyFlowField(FlowField &flowField)
{
    for (int i=0; i<points.size(); i++)
    {
        points[i]->applyForce(flowField.getForce(*points[i]));
        flowField.addRepulsion(*points[i], 8, Params::particleFlowfieldForce);
    }
}

float ParticleStroke::getDistanceToClosestParticle(const ofVec2f &p)
{
    float minLength = 10000;
    
    for (int i=0; i<points.size(); i++)
    {
        float l = (p-*points[i]).length() - points[i]->getRadius();
        if (l < minLength) {
            minLength = l;
        }
    }
    
    return minLength;
}
