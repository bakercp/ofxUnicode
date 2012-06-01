//
//  ofUTF32.h
//  ofxUnicodeExample
//
//  Created by Christopher Baker on 6/1/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofUnicode.h"
#include "ofUTF8.h"
#include "ofUTF16.h"

class ofUTF32 {
public:
    static ofUTF8String   toUTF8(const ofUniChar&   input); // 32->8
    static ofUTF8String   toUTF8(const ofUniString& input); // 32->8
    static ofUTF16String toUTF16(const ofUniString& input); // 16->8
};


