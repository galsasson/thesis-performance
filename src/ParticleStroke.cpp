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
    Particle *newP = new Particle(p);
    newP->setColor(ofColor::fromHsb(ofNoise(t)*100, 150, 255));
    points.push_back(newP);
}

void ParticleStroke::update()
{
    for (int i=0; i<points.size(); i++)
    {
        points[i]->update();
    }
    
    t+=0.1;
}

void ParticleStroke::draw()
{
    ofFill();
//    ofBeginShape();
    for (int i=0; i<points.size(); i++)
    {
        points[i]->draw();
//        ofVertex(points[i]->x, points[i]->y);
    }
//    ofEndShape();
}

void ParticleStroke::applyFlowField(const FlowField &flowField)
{
    for (int i=0; i<points.size(); i++)
    {
        points[i]->applyForce(flowField.getForce(*points[i]));
    }
}
