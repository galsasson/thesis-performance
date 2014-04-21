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
    
}

void SpringStroke::addPoint(float x, float y)
{
    line.addPoint(x, y);
}

void SpringStroke::update()
{
    vector<Particle*> particles = line.getPoints();
    cout << "before: " << particles[0] << endl;
    for (int i=0; i<particles.size(); i++)
    {
//        particles[i].applyForce(ofVec2f(10, 10));
//        cout<<"x: " << particles[i].x<<endl;
        particles[i]->x+=0.1;
//        cout<<"x: " << particles[i].x<<endl;
        particles[i]->update();
    }
    
    cout << "after: "<<particles[0] << endl;

    line.rebuildMesh();
}

void SpringStroke::draw()
{
    line.draw();
}

