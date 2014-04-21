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
    
}

void SpringStroke::draw()
{
    line.draw();
}

