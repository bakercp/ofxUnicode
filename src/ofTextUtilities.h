//
//  ofTextUtilities.h
//  ofxUnicodeExample
//
//  Created by Christopher Baker on 6/1/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofUnicode.h"
#include "ofUTF8.h"
#include "ofUTF16.h"
#include "ofUTF32.h"

#include "unicode/ucsdet.h" // charset detection
#include "unicode/ucnv.h"   // character set conversion

class ofTextUtilities {
public:
    ofTextUtilities();
    virtual ~ofTextUtilities();
    
    static vector<string> listAvailableCharsets();
    static bool detectCharset(const string& buffer, string& name, string& lang, int& confidence);
    static bool convertCharset(string& buffer, const string& originCharset, const string& destCharset); 
    static bool convertCharsetToUTF8(string& buffer, const string& originCharset); 
    
    
};
