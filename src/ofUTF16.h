//
//  ofUTF16.h
//  ofxUnicodeExample
//
//  Created by Christopher Baker on 6/1/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofUnicode.h"
#include "ofUTF8.h"
#include "ofUTF32.h"

class ofUTF16 {
public:
    static ofUTF8String toUTF8(const ofUTF16String& input); // 16->8
    static ofUniString toUTF32(const ofUTF16String& input); // 16->32
};
