//
//  Canvas.cpp
//  performance
//
//  Created by Gal Sasson on 4/12/14.
//
//

#include "Canvas.h"

Canvas::Canvas()
{
    size = ofVec2f(0, 0);
    currentStroke = NULL;
    currentTurtleStroke = NULL;
    currentParticleStroke = NULL;
    
    nStrokes = 0;
    strokeControlIndex = 0;
    
    noiseTime.x = ofRandom(10000);
    noiseTime.y = ofRandom(10000);
    noiseRate = 0;
    randomLevel = 0;
    strokeType = 0;
}

Canvas::~Canvas()
{
    clear();
}

void Canvas::setup(float width, float height)
{
    size = ofVec2f(width, height);
    
    flowField.setup(width, height, 500, 500);
}

void Canvas::update()
{
    nStrokes = strokes.size();
    noiseTime.x += noiseRate/10;
    noiseTime.y += noiseRate/10;
    
    for (int i=0; i<turtleStrokes.size(); i++)
    {
        turtleStrokes[i]->update();
    }
    
    for (int i=0; i<particleStrokes.size(); i++)
    {
        particleStrokes[i]->applyFlowField(flowField);
        particleStrokes[i]->update();
    }
    
//    flowField.update();
}

void Canvas::draw()
{
    ofClear(200);

    ofSetColor(50);
    ofNoFill();
    for (int i=0; i<strokes.size(); i++)
    {
        drawStroke(strokes[i]);
    }
    
    for (int i=0; i<turtleStrokes.size(); i++)
    {
        turtleStrokes[i]->draw();
    }
    
    for (int i=0; i<particleStrokes.size(); i++)
    {
        particleStrokes[i]->draw();
    }
    
    drawStroke(currentStroke);
    if (currentTurtleStroke) {
        currentTurtleStroke->draw();
    }
    if (currentParticleStroke) {
        currentParticleStroke->draw();
    }
}

void Canvas::clear()
{
    for (int i=0; i<strokes.size(); i++)
    {
        delete strokes[i];
    }
    strokes.clear();
    if (currentStroke) {
        delete currentStroke;
        currentStroke = NULL;
    }
    
    for (int i=0; i<turtleStrokes.size(); i++)
    {
        delete turtleStrokes[i];
    }
    turtleStrokes.clear();
    
    for (int i=0; i<particleStrokes.size(); i++)
    {
        delete particleStrokes[i];
    }
    particleStrokes.clear();
    
    if (currentTurtleStroke) {
        delete currentTurtleStroke;
        currentTurtleStroke = NULL;
    }
    if (currentParticleStroke) {
        delete currentParticleStroke;
        currentParticleStroke = NULL;
    }
}

void Canvas::mousePressed(int x, int y, int button)
{
    if (strokeType == 0)
    {
        currentStroke = new Stroke();
        currentStroke->addPoint(ofVec3f(x, y, 0));
        flowField.addAttractor(ofVec2f(x, y), 40, 15);
    }
    else if (strokeType == 1) {
        currentTurtleStroke = new TurtleStroke();
        currentTurtleStroke->setup(ofVec3f(x, y, 0));
    }
    else if (strokeType == 2) {
        currentParticleStroke = new ParticleStroke();
        currentParticleStroke->addPoint(ofVec2f(x, y));
    }
}

void Canvas::mouseDragged(int x, int y, int button)
{
    if (strokeType == 0)
    {
        if (currentStroke) {
            currentStroke->addPoint(ofVec3f(x, y, 0));
            flowField.addAttractor(ofVec2f(x, y), 40, 15);
        }
    }
    else if (strokeType == 1) {
        if (currentTurtleStroke) {
            currentTurtleStroke->addPoint(ofVec3f(x, y, 0));
        }
    }
    else if (strokeType == 2) {
        if (currentParticleStroke) {
            currentParticleStroke->addPoint(ofVec2f(x, y));
        }
    }
}

void Canvas::mouseReleased(int x, int y, int button)
{
    if (strokeType == 0)
    {
        if (currentStroke) {
            strokes.push_back(currentStroke);
            currentStroke = NULL;
        }
    }
    else if (strokeType == 1) {
        if (currentTurtleStroke) {
            turtleStrokes.push_back(currentTurtleStroke);
            currentTurtleStroke = NULL;
        }
    }
    else if (strokeType == 2) {
        if (currentParticleStroke) {
            particleStrokes.push_back(currentParticleStroke);
            currentParticleStroke = NULL;
        }
    }
    
}

void Canvas::keyPressed(int key)
{
    if (key == '1') {
        strokeType = 0;
    }
    else if (key == '2') {
        strokeType = 1;
    }
    else if (key == '3') {
        strokeType = 2;
    }
}

void Canvas::drawStroke(Stroke *s)
{
    if (s == NULL) {
        return;
    }
    
    ofSetColor(50, 50, 50);
    ofSetLineWidth(1);
    ofNoFill();
    vector<ofVec3f*> points = s->getPoints();
    ofBeginShape();
    for (int i=0; i<points.size(); i++)
    {
        ofVec3f p = getPointWithNoise(points[i], i);
        ofVertex(p);
    }
    ofEndShape();
}

void Canvas::drawShape(Stroke *s)
{
    if (s == NULL) {
        return;
    }
    
    ofSetColor(50, 50, 50);
    ofSetLineWidth(1);
    ofFill();
    vector<ofVec3f*> points = s->getPoints();
    ofBeginShape();
    for (int i=0; i<points.size(); i++)
    {
        ofVec3f p = getPointWithNoise(points[i]);
        ofVertex(p);
    }
    ofEndShape();
}

ofVec3f Canvas::getPointWithNoise(ofVec3f *p, int index)
{
    float time = noiseTime.x + index*noiseSpatialRate;

    return ofVec3f(p->x + (ofNoise(time)-0.5f)*noiseLevel + ofRandom(-0.5, 0.5)*randomLevel + sin(xFrequency*index)*xAmplitude,
                   p->y + (ofNoise(time + 1000)-0.5f)*noiseLevel + ofRandom(-0.5, 0.5)*randomLevel,
                   p->z + (ofNoise(time + 10000)-0.5f)*noiseLevel + ofRandom(-0.5, 0.5)*randomLevel);
}
