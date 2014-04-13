//
//  Canvas.h
//  performance
//
//  Created by Gal Sasson on 4/12/14.
//
//

#ifndef __performance__Canvas__
#define __performance__Canvas__

#include <iostream>
#include "ofMain.h"

#include "Stroke.h"
#include "TurtleStroke.h"

class Canvas
{
public:
    Canvas();
    ~Canvas();
    void setup(float width, float height);
    
    void update();
    void draw();
    
    void clear();
    
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    
    // parameters
    int nStrokes;
    int strokeControlIndex;
    
    float noiseLevel;
    float noiseRate;
    float noiseSpatialRate;
    float randomLevel;
    float xFrequency;
    float xAmplitude;
    
private:
    ofVec2f size;
    vector<Stroke*> strokes;
    vector<TurtleStroke*> turtleStrokes;
    Stroke* currentStroke;
    TurtleStroke* currentTurtleStroke;
    ofVec3f noiseTime;

    int strokeType;
    

    void drawShape(Stroke *s);
    void drawStroke(Stroke *s);
    
    ofVec3f getPointWithNoise(ofVec3f *p, int index = 0);
};

#endif /* defined(__performance__Canvas__) */
