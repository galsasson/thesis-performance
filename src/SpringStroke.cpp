//
//  SpringStroke.cpp
//  performance
//
//  Created by Gal Sasson on 4/21/14.
//
//

#include "SpringStroke.h"

SpringStroke::SpringStroke()
{
    
}

SpringStroke::~SpringStroke()
{
    for (int i=0; i<springs.size(); i++)
    {
        delete springs[i];
    }
    springs.clear();
}

void SpringStroke::addPoint(float x, float y)
{
    line.addPoint(x, y);
    
    vector<Particle*> particles = line.getPoints();
    int lastIndex = particles.size()-1;
    if (lastIndex > 0) {
        Spring *s = new Spring();
        s->setup(particles[lastIndex-1], particles[lastIndex]);
        s->restLength*=0.5;
        springs.push_back(s);
    }
    else {
        particles[lastIndex]->locked = true;
    }
    
    // check if another point overlaps with this point, add another spring
    if (lastIndex > 2) {
        for (int i=0; i<particles.size()-2; i++)
        {
            if ((*particles[i] - *particles[lastIndex]).length() < 3) {
                Spring *s = new Spring();
                s->setup(particles[i], particles[lastIndex]);
//                s->restLength*=0.8;
                springs.push_back(s);
                break;
            }
        }
    }
}

void SpringStroke::update()
{
    for (int i=0; i<springs.size(); i++)
    {
        springs[i]->update();
    }
    
    vector<Particle*> particles = line.getPoints();
    for (int i=0; i<particles.size(); i++)
    {
        particles[i]->applyForce(ofVec2f(0, 0.4));
        particles[i]->update();
        particles[i]->checkBounds();
    }
    
    line.rebuildMesh();
}

void SpringStroke::draw()
{
    line.draw();
}

