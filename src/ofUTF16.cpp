//
//  ofUTF16.cpp
//  ofxUnicodeExample
//
//  Created by Christopher Baker on 6/1/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#include "ofUTF16.h"

//------------------------------------------------------------------
ofUTF8String ofUTF16::toUTF8(const ofUTF16String& input) {
    ofUTF8String utf8result;
    input.toUTF8String(utf8result);
    return utf8result;
}

//------------------------------------------------------------------
ofUniString ofUTF16::toUTF32(const ofUTF16String& input) {
    ofUniString out;
    ofUniChar buffer[input.length()]; // we'll not need more than this;
    UErrorCode errorCode = U_ZERO_ERROR;
    int32_t len = input.toUTF32(buffer, input.length(), errorCode);    
    if(U_SUCCESS(errorCode)) {
        out.append(buffer,len);
    } else {
        ofLog(OF_LOG_ERROR,"ofUTF8::append - error converting unicode to UTF8.  Returning original.");
    }
    return out;
}
