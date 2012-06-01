//
//  ofUTF32.cpp
//  ofxUnicodeExample
//
//  Created by Christopher Baker on 6/1/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#include "ofUTF32.h"

//------------------------------------------------------------------
ofUTF8String ofUTF32::toUTF8(const ofUniChar& input) {
    ofUTF8String utf8result;
    return ofUTF8::append(utf8result, input);
}

//------------------------------------------------------------------
ofUTF8String ofUTF32::toUTF8(const ofUniString& input) {
    ofUTF8String utf8result;
    return ofUTF8::append(utf8result, input);
}

//------------------------------------------------------------------
ofUTF16String ofUTF32::toUTF16(const ofUniString& input) {
    return UnicodeString::fromUTF32(input.c_str(),input.length());
}
