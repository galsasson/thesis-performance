//
//  Spring.cpp
//  performance
//
//  Created by Gal Sasson on 4/21/14.
//
//

#include "Spring.h"

Spring::Spring()
{
    k = 0.3;
}

Spring::~Spring()
{
    
}

void Spring::setup(Particle *source, Particle *target)
{
    p1 = source;
    p2 = target;
    
    restLength = (*p2-*p1).length();
}

void Spring::update()
{
    ofVec2f force = (*p2-*p1);
    float currentLength = force.length();
    float x = currentLength - restLength;
    
    force.normalize();
    
    force *= k * x;
    
    p1->applyForce(force*2);
    p2->applyForce(force*-2);
}
