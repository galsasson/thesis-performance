//
//  Stroke.cpp
//  performance
//
//  Created by Gal Sasson on 4/12/14.
//
//

#include "Stroke.h"

Stroke::Stroke()
{
    
}

Stroke::~Stroke()
{
    // delete all allocated points
    for (int i=0; i<points.size(); i++)
    {
        delete points[i];
    }
    
    points.clear();
}

void Stroke::addPoint(const ofVec2f& p)
{
    points.push_back(new ofVec2f(p));
}

vector<ofVec2f*>& Stroke::getPoints()
{
    return points;
}

