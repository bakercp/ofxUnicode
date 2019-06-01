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
    void setup();

    void dumpLineBreaks(const std::string& text, const std::string& language);
    void dumpWordBreaks(const std::string& text, const std::string& language);

};
