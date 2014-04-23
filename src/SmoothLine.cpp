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
    float w;
    if (points.empty()) {
        w = 1;
    }
    else {
        Particle *lp = points.back();
        float prevMass = lp->mass;
        w = prevMass + ((0.5f+(ofVec2f(x, y) - *lp).length() / 5) - prevMass)*0.2;
    }
    
    Particle* newPar = new Particle(x, y, w);
    newPar->setColor(ofColor(50));
    points.push_back(newPar);
    rebuildMesh();
}

void SmoothLine::update()
{
}

void SmoothLine::draw()
{
    ResourceManager::getInstance().circleImg.getTextureReference().bind();
    mesh.draw();
    ResourceManager::getInstance().circleImg.getTextureReference().unbind();
}

SmoothLine* SmoothLine::cutLine(int index)
{
    if (index >= points.size()) {
        cout<<"error: index out of bounds in cutLine"<<endl;
        return NULL;
    }
    
    SmoothLine* newLine = new SmoothLine();
    for (int i=index; i<points.size(); i++)
    {
        newLine->points.push_back(points[i]);
    }
    points.erase(points.begin()+index, points.end());
    
    newLine->rebuildMesh();
    rebuildMesh();
    return newLine;
}

// based on https://github.com/apitaru/ofxSmoothLines/blob/master/src/ofxSmoothLines.mm
void SmoothLine::rebuildMesh()
{
    if (points.size() < 2) {
        return;
    }
    
    mesh.clear();
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    for (int i=0; i<points.size()-1; i++)
    {
        Particle a = *points[i];
        Particle b = *points[i+1];
//        ofVec2f a = ofVec2f(points[i]->x, points[i]->y);
//		ofVec2f b = ofVec2f(points[i+1]->x, points[i+1]->y);
        
		ofVec2f ea = (ofVec2f)(b - a).normalize() * a.mass;
        ofVec2f eb = (ofVec2f)(b - a).normalize() * b.mass;
        
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
        
        mesh.addColor(a.getColor());
        mesh.addColor(a.getColor());
        mesh.addColor(a.getColor());
        mesh.addColor(a.getColor());
        mesh.addColor(b.getColor());
        mesh.addColor(b.getColor());
        mesh.addColor(b.getColor());
        mesh.addColor(b.getColor());
        
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
    }
}

