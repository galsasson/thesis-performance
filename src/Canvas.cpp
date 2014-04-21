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
    currentRepeatableStroke = NULL;
    currentSpringStroke = NULL;
    
    nStrokes = 0;
    strokeControlIndex = 0;
    
    noiseTime.x = ofRandom(10000);
    noiseTime.y = ofRandom(10000);
    noiseRate = 0;
    randomLevel = 0;
    strokeType = 0;
    bShowFlowfield = false;
    
    RepeatableStroke::initTransformations();    
}

Canvas::~Canvas()
{
    clear();
}

void Canvas::setup(float width, float height)
{
    size = ofVec2f(width, height);
    
    flowField.setup(width, height, 300, 300);
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
    
    if (currentParticleStroke) {
        currentParticleStroke->applyFlowField(flowField);
        currentParticleStroke->update();
    }
    
//    flowField.update();
}

void Canvas::draw()
{
    ofSetColor(220, 220, 220, 20);
    ofFill();
    ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

    // draw filled surfaces
    ofSetColor(200, 0, 0);
    ofFill();
    for (int i=0; i<turtleStrokes.size(); i++)
    {
        turtleStrokes[i]->draw();
    }
    if (currentTurtleStroke) {
        currentTurtleStroke->draw();
    }

    ofSetColor(50);
    ofNoFill();
    ResourceManager::getInstance().circleImg.getTextureReference().bind();
    for (int i=0; i<strokes.size(); i++)
    {
        strokes[i]->draw();
    }
    if (currentStroke) {
        currentStroke->draw();
    }
    for (int i=0; i<repeatableStrokes.size(); i++)
    {
        repeatableStrokes[i]->draw();
    }
    if (currentRepeatableStroke) {
        currentRepeatableStroke->draw();
    }
    for (int i=0; i<springStrokes.size(); i++)
    {
        springStrokes[i]->draw();
    }
    if (currentSpringStroke) {
        currentSpringStroke->draw();
    }
    ResourceManager::getInstance().circleImg.getTextureReference().unbind();

    for (int i=0; i<particleStrokes.size(); i++)
    {
        particleStrokes[i]->draw();
    }
    

    ofSetColor(50);
    ofNoFill();

    if (currentParticleStroke) {
        currentParticleStroke->draw();
    }
    
    if (bShowFlowfield) {
        flowField.draw();
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
    
    for (int i=0; i<repeatableStrokes.size(); i++)
    {
        delete repeatableStrokes[i];
    }
    repeatableStrokes.clear();
    for (int i=0; i<springStrokes.size(); i++)
    {
        delete springStrokes[i];
    }
    springStrokes.clear();
    
    if (currentTurtleStroke) {
        delete currentTurtleStroke;
        currentTurtleStroke = NULL;
    }
    if (currentParticleStroke) {
        delete currentParticleStroke;
        currentParticleStroke = NULL;
    }
    if (currentRepeatableStroke) {
        delete currentRepeatableStroke;
        currentRepeatableStroke = NULL;
    }
    if (currentSpringStroke) {
        delete currentSpringStroke;
        currentSpringStroke = NULL;
    }
    
    flowField.reset();
}

void Canvas::mousePressed(int x, int y, int button)
{
    if (strokeType == 0)
    {
        currentStroke = new Stroke();
        currentStroke->addPoint(x, y);
        flowField.addAttractor(ofVec2f(x, y), 40, 1);
    }
    else if (strokeType == 1) {
        currentTurtleStroke = new TurtleStroke();
        currentTurtleStroke->setup(ofVec3f(x, y, 0));
    }
    else if (strokeType == 2) {
        currentParticleStroke = new ParticleStroke();
        currentParticleStroke->addPoint(ofVec2f(x, y));
    }
    else if (strokeType == 3) {
        if (repeatableStrokes.size() == 0) {
            repeatableAnchor = ofVec2f(x, y);
        }
        
        currentRepeatableStroke = new RepeatableStroke();
        currentRepeatableStroke->setAnchor(repeatableAnchor.x, repeatableAnchor.y);
        currentRepeatableStroke->addPoint(x, y);
    }
    else if (strokeType == 4) {
        currentSpringStroke = new SpringStroke();
        currentSpringStroke->addPoint(x, y);
    }
}

void Canvas::mouseDragged(int x, int y, int button)
{
    if (strokeType == 0)
    {
        if (currentStroke) {
            flowField.addForce(ofVec2f(x, y), 40, (ofVec2f)(ofVec3f(x, y, 0) - currentStroke->getPoints()[currentStroke->getPoints().size()-1])/5);
            currentStroke->addPoint(x, y);
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
    else if (strokeType == 3) {
        if (currentRepeatableStroke) {
            currentRepeatableStroke->addPoint(x, y);
        }
    }
    else if (strokeType == 4) {
        if (currentSpringStroke) {
            currentSpringStroke->addPoint(x, y);
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
    else if (strokeType == 3) {
        if (currentRepeatableStroke) {
            repeatableStrokes.push_back(currentRepeatableStroke);
            currentRepeatableStroke = NULL;
        }
    }
    else if (strokeType == 4) {
        if (currentSpringStroke) {
            springStrokes.push_back(currentSpringStroke);
            currentSpringStroke = NULL;
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
    else if (key == '4') {
        strokeType = 3;
    }
    else if (key == '5') {
        strokeType = 4;
    }
    else if (key == 'f') {
        bShowFlowfield = !bShowFlowfield;
    }
    else if (key == 'c') {
//        ofClear(220);
        clear();
    }
}

void Canvas::drawStroke(Stroke *s)
{
//    if (s == NULL) {
//        return;
//    }
//    
//    ofSetColor(50, 50, 50);
//    ofSetLineWidth(1);
//    ofNoFill();
//    vector<ofVec2f*> points = s->getPoints();
//    ofBeginShape();
//    for (int i=0; i<points.size(); i++)
//    {
//        ofVec2f p = getPointWithNoise(points[i], i);
//        ofVertex(p.x, p.y);
//    }
//    ofEndShape();
}

void Canvas::drawShape(Stroke *s)
{
//    if (s == NULL) {
//        return;
//    }
//    
//    ofSetColor(50, 50, 50);
//    ofSetLineWidth(1);
//    ofFill();
//    vector<ofVec2f*> points = s->getPoints();
//    ofBeginShape();
//    for (int i=0; i<points.size(); i++)
//    {
//        ofVec2f p = getPointWithNoise(points[i]);
//        ofVertex(p.x, p.y);
//    }
//    ofEndShape();
}

ofVec2f Canvas::getPointWithNoise(ofVec2f *p, int index)
{
    float time = noiseTime.x + index*noiseSpatialRate;

    return ofVec2f(p->x + (ofNoise(time)-0.5f)*noiseLevel + ofRandom(-0.5, 0.5)*randomLevel + sin(xFrequency*index)*xAmplitude,
                   p->y + (ofNoise(time + 1000)-0.5f)*noiseLevel + ofRandom(-0.5, 0.5)*randomLevel);
}
