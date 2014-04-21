//
//  SmoothLine.cpp
//  performance
//
//  Created by Gal Sasson on 4/21/14.
//
//

#include "SmoothLine.h"

SmoothLine::SmoothLine()
{
}

SmoothLine::~SmoothLine()
{
    for (int i=0; i<points.size(); i++)
    {
        delete points[i];
    }
    points.clear();
}

void SmoothLine::addPoint(float x, float y)
{
    float w = 1;
    if (points.size() > 0) {
        ofVec2f lp = *points.back();
        w = 0.2f+(ofVec2f(x, y) - lp).length() / 5;
    }
    
    points.push_back(new Particle(x, y, w));
    rebuildMesh();
}

void SmoothLine::draw()
{
//    ResourceManager::getInstance().circleImg.getTextureReference().bind();
    mesh.draw();
//    ResourceManager::getInstance().circleImg.getTextureReference().unbind();
}


// based on https://github.com/apitaru/ofxSmoothLines/blob/master/src/ofxSmoothLines.mm
void SmoothLine::rebuildMesh()
{
    if (points.size() < 2) {
        return;
    }
    
    mesh.clear();
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    float w = points[0]->mass;
    float w2;
    
    for (int i=0; i<points.size()-1; i++)
    {
        ofVec2f a = ofVec2f(points[i]->x, points[i]->y);
		ofVec2f b = ofVec2f(points[i+1]->x, points[i+1]->y);
        
        w2 = w + (points[i+1]->mass - w)*0.2f;
		ofVec2f ea = (ofVec2f)(b - a).normalize() * w;
        ofVec2f eb = (ofVec2f)(b - a).normalize() * w2;
        
		ofVec2f NA = ofVec2f(-ea.y, ea.x);
		ofVec2f NB = ofVec2f(-eb.y, eb.x);
		ofVec2f SA = -NA;
		ofVec2f SB = -NB;
		ofVec2f NE = NB + eb;
		ofVec2f NW = NA - ea;
        ofVec2f SW = -NA - ea;
        ofVec2f SE = -NB + eb;
        
		mesh.addVertex(a + SW);
		mesh.addVertex(a + NW);
		mesh.addVertex(a + SA);
		mesh.addVertex(a + NA);
		mesh.addVertex(b + SB);
		mesh.addVertex(b + NB);
		mesh.addVertex(b + SE);
		mesh.addVertex(b + NE);
        
		int vertOffest = i * 8;
		mesh.addIndex(vertOffest + 0); 	mesh.addIndex(vertOffest +1); 	mesh.addIndex(vertOffest +2);
		mesh.addIndex(vertOffest +2); 	mesh.addIndex(vertOffest +1); 	mesh.addIndex(vertOffest +3);
		mesh.addIndex(vertOffest +2); 	mesh.addIndex(vertOffest +3); 	mesh.addIndex(vertOffest +4);
		mesh.addIndex(vertOffest +4); 	mesh.addIndex(vertOffest +3); 	mesh.addIndex(vertOffest +5);
		mesh.addIndex(vertOffest +4); 	mesh.addIndex(vertOffest +5); 	mesh.addIndex(vertOffest +6);
		mesh.addIndex(vertOffest +6); 	mesh.addIndex(vertOffest +5); 	mesh.addIndex(vertOffest +7);
        
		mesh.addTexCoord(ofVec2f(0,0));
		mesh.addTexCoord(ofVec2f(0,16));
		mesh.addTexCoord(ofVec2f(8,0));
		mesh.addTexCoord(ofVec2f(8,16));
		mesh.addTexCoord(ofVec2f(8,0));
		mesh.addTexCoord(ofVec2f(8,16));
		mesh.addTexCoord(ofVec2f(16,0));
		mesh.addTexCoord(ofVec2f(16,16));
        
        w = w2;
    }
}

