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
    noiseTime.x += noiseRate/10;
    noiseTime.y += noiseRate/10;
    
//    handleControlMessages();

    // update spring strokes and flow field
    flowField.reset();
    for (int i=0; i<springStrokes.size(); i++)
    {
        springStrokes[i]->update();
        flowField.applyStrokeForces(springStrokes[i]->getPoints());
    }
    if (currentSpringStroke) {
        flowField.applyStrokeForces(currentSpringStroke->getPoints());
    }
    
    // update surfaces
    for (int i=0; i<surfaceStrokes.size(); i++)
    {
        surfaceStrokes[i]->update();
    }
    
    // update PARTICLE stroke
    for (int i=0; i<particleStrokes.size(); i++)
    {
        particleStrokes[i]->applyFlowField(flowField);
        particleStrokes[i]->update();
    }
//    if (currentParticleStroke) {
//        currentParticleStroke->applyFlowField(flowField);
//        currentParticleStroke->update();
//    }
    
//    flowField.update();
}

void Canvas::draw()
{
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(ResourceManager::getInstance().getBackgroundColor());
    ofFill();
    ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
//    ofDisableBlendMode();
    
    ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
    // draw filled surfaces
    ofSetColor(150, 20, 20, 50);
    ofFill();
    for (int i=0; i<surfaceStrokes.size(); i++)
    {
        surfaceStrokes[i]->drawSurface();
    }
    if (currentSurfaceStroke) {
        currentSurfaceStroke->drawSurface();
    }
//    ofDisableBlendMode();

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(255);
    ofNoFill();
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
//    ofDisableBlendMode();

//    ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
    // draw PARTICLE strokes
    for (int i=0; i<particleStrokes.size(); i++)
    {
        particleStrokes[i]->draw();
    }
    if (currentParticleStroke) {
        currentParticleStroke->draw();
    }
//    ofDisableBlendMode();
    
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
    if (bShowFlowfield) {
        flowField.draw();
    }
    
    // draw cursor
    ofSetColor(ResourceManager::getInstance().getStrokeColor());
    ofNoFill();
    if (strokeType < 5) {
        ofEllipse(ofGetMouseX(), ofGetMouseY(), 15, 15);
    }
    else {
        ofLine(ofGetMouseX()-7, ofGetMouseY()-7, ofGetMouseX()+7, ofGetMouseY()+7);
        ofLine(ofGetMouseX()+7, ofGetMouseY()-7, ofGetMouseX()-7, ofGetMouseY()+7);
        ofLine(bladePrev, blade);
    }
//    ofDisableBlendMode();

}

void Canvas::doCut(const ofVec2f &p, const ofVec2f &q)
{
    for (int i=0; i<springStrokes.size(); i++)
    {
        int index = springStrokes[i]->getIntersection(p, q);
        if (index < 0) {
            continue;
        }
        
        // do the cut
        SpringStroke *newStroke = springStrokes[i]->cutStroke(index);
        springStrokes.push_back(newStroke);
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
    
    for (int i=0; i<surfaceStrokes.size(); i++)
    {
        delete surfaceStrokes[i];
    }
    surfaceStrokes.clear();
    
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
    
    if (currentSurfaceStroke) {
        delete currentSurfaceStroke;
        currentSurfaceStroke = NULL;
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
        currentSpringStroke = new SpringStroke();
        currentSpringStroke->setLockDistance(50);
        currentSpringStroke->addPoint(x, y);
    }
    else if (strokeType == 1) {
        currentSurfaceStroke = new SpringStroke();
        currentSurfaceStroke->setLockDistance(50);
        currentSurfaceStroke->addPoint(x, y);
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
    else if (strokeType == 5) {
        // this is the blade that cuts
        blade = bladePrev = ofVec2f(x, y);
    }
}

void Canvas::mouseDragged(int x, int y, int button)
{
    if (strokeType == 0)
    {
        if (currentSpringStroke) {
            currentSpringStroke->addPoint(x, y);
        }
    }
    else if (strokeType == 1) {
        if (currentSurfaceStroke) {
            currentSurfaceStroke->addPoint(x, y);
        }
    }
    else if (strokeType == 2) {
        if (currentParticleStroke) {
            for (int i=0; i<3; i++) {
                currentParticleStroke->addPoint(ofVec2f(x+ofRandom(20)-10, y+ofRandom(20)-10));
            }
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
    else if (strokeType == 5) {
        // blade
        bladePrev = blade;
        blade = ofVec2f(x, y);
        doCut(bladePrev, blade);
    }
}

void Canvas::mouseReleased(int x, int y, int button)
{
    if (strokeType == 0)
    {
        if (currentSpringStroke) {
            springStrokes.push_back(currentSpringStroke);
            currentSpringStroke = NULL;
        }
    }
    else if (strokeType == 1) {
        if (currentSurfaceStroke) {
            surfaceStrokes.push_back(currentSurfaceStroke);
            currentSurfaceStroke = NULL;
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

void Canvas::mouseMoved(int x, int y)
{
    if (strokeType == 5) {
        // blade
        bladePrev = blade;
    }
}

void Canvas::keyPressed(int key)
{
    if (key >= '1' &&
        key <= '6') {
        setStroke(key);
    }
    else if (key == 'r') {
        releaseAllParticles(1);
    }
    else if (key == 'f') {
        bShowFlowfield = !bShowFlowfield;
    }
    else if (key == 'c') {
//        ofClear(220);
        clear();
    }
    else if (key == 'd') {
        for (int i=0; i<springStrokes.size(); i++)
        {
            springStrokes[i]->releaseAnchors();
        }
        for (int i=0; i<surfaceStrokes.size(); i++)
        {
            surfaceStrokes[i]->releaseAnchors();
        }
        for (int i=0; i<particleStrokes.size(); i++)
        {
            particleStrokes[i]->releaseAllParticles();
        }
    }
    else if (key == 'z') {
        for (int i=0; i<springStrokes.size(); i++)
        {
            springStrokes[i]->dropColor(ofColor(180, 0, ofRandom(50)));
        }
    }
    else if (key == 'a') {
        Params::colorMode = (Params::colorMode)?0:1;
    }
}

void Canvas::releaseAllParticles(float val)
{
    if (val == 0) {
        return;
    }
    
    for (int i=0; i<particleStrokes.size(); i++)
    {
        particleStrokes[i]->releaseAllParticles();
    }
}

ofVec2f Canvas::getPointWithNoise(ofVec2f *p, int index)
{
    float time = noiseTime.x + index*noiseSpatialRate;

    return ofVec2f(p->x + (ofNoise(time)-0.5f)*noiseLevel + ofRandom(-0.5, 0.5)*randomLevel + sin(xFrequency*index)*xAmplitude,
                   p->y + (ofNoise(time + 1000)-0.5f)*noiseLevel + ofRandom(-0.5, 0.5)*randomLevel);
}
