#pragma once

#include "ofMain.h"

#include "ofUnicode.h"
#include "ofUTF8.h"
#include "ofUTF16.h"
#include "ofUTF32.h"


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
