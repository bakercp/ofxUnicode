//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//

#pragma once


#include "ofMain.h"
#include "ofxUnicode.h"


class ofApp: public ofBaseApp
{
public:
    void setup() override;

    void validationTests();
    void concatTests();
    void conversionTests();
    void distanceTests();
    void iterationTests();
    void fileReadWriteTests();

};
