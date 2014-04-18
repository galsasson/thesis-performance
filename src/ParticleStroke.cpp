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
    points.push_back(new Particle(p));
}

void ParticleStroke::update()
{
    for (int i=0; i<points.size(); i++)
    {
        points[i]->update();
    }
}

void ParticleStroke::draw()
{
    ofBeginShape();
    for (int i=0; i<points.size(); i++)
    {
        points[i]->draw();
        ofVertex(points[i]->x, points[i]->y);
    }
    ofEndShape();
}

void ParticleStroke::applyFlowField(const FlowField &flowField)
{
    for (int i=0; i<points.size(); i++)
    {
        points[i]->applyForce(flowField.getForce(*points[i]));
    }
}
