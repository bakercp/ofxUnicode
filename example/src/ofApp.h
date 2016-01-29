#pragma once


#include "ofMain.h"
#include "ofUTF8.h"
#include "ofUnicode.h"
#include "ofTextConverter.h"


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
