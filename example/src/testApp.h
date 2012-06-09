#pragma once

#include "stdio.h"
#include "assert.h"

#include "ofMain.h"

#include "ofUTF8.h"
//#include "ofUTF16.h"
#include "ofUnicode.h"
#include "ofTextConverter.h"

class testApp : public ofBaseApp{
public:
    void setup();


    void validationTests();
    void concatTests();
    void conversionTests();
    void distanceTests();
    void iterationTests();
    void fileReadWriteTests();



};
