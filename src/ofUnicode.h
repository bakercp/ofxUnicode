//
//  ofUnicode.h
//  ofxUTFCPPExample
//
//  Created by Christopher Baker on 5/23/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofConstants.h"
#include "ofLog.h"
#include "ofUtils.h"

#include "utf8.h"

#include "Poco/String.h"
#include "Poco/UTF8String.h"
#include "Poco/Ascii.h"
#include "Poco/Unicode.h"
#include "Poco/UTF8Encoding.h"
#include "Poco/TextIterator.h"
#include "Poco/TextConverter.h"

#include "Poco/UTF16Encoding.h"
#include "Poco/ASCIIEncoding.h"
#include "Poco/Latin1Encoding.h"
#include "Poco/Latin9Encoding.h"
#include "Poco/Windows1252Encoding.h"

typedef unsigned int     ofUTF32Char;
typedef unsigned short   ofUTF16Char;
typedef unsigned char	 ofUTF8Char;
typedef char             ofChar;
typedef const char *     ofUTF8Iter;
typedef utf8::iterator<ofUTF8Iter> ofUTF8Iterator;


typedef ofUTF32Char      ofUniChar;

typedef ofUniChar*       ofUniCharPtr;
typedef unsigned int     ofUniCharCount;
typedef signed   int     ofUniCharGlyphIdx;
typedef ofUniCharCount*  ofUniCharCountPtr;


typedef vector<ofUniChar> ofUniChars;

class ofUnicode {
public:
    
    static bool       isValid(const ofUniChar& unicode);

    static bool       isSpace(const ofUniChar& unichar);
    static bool       isDigit(const ofUniChar& unichar);
    static bool       isPunct(const ofUniChar& unichar);
    static bool 	  isAlpha(const ofUniChar& unichar);
    static bool       isLower(const ofUniChar& unichar);
    static bool       isUpper(const ofUniChar& unichar);
    static ofUniChar  toLower(const ofUniChar& unichar);
    static ofUniChar  toUpper(const ofUniChar& unichar);
    static ofUniChar& toLowerInPlace(ofUniChar& unichar);
    static ofUniChar& toUpperInPlace(ofUniChar& unichar);
    
};
