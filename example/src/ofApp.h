#pragma once


#include "ofMain.h"
#include "ofxUnicode.h"


class ofApp : public ofBaseApp{
public:
    void setup();

    void validationTests();
    void concatTests();
    void conversionTests();
    void distanceTests();
    void iterationTests();
    void fileReadWriteTests();

};
