//
//  ofxUTF8CPP.h
//  ofxUTFCPPExample
//
//  Created by Christopher Baker on 5/23/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofUnicode.h"
#include "ofUTF16.h"
#include "ofUTF32.h"

#include "unicode/utf8.h" // icu


class ofUTF8 {
public:
    
    ////////////////////////////////////////////////////////////////////
    // UTF8 MANIPULATION TOOLS /////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////

    static ofUTF16String toUTF16(const ofUTF8String& txt);
    static ofUniString   toUTF32(const ofUTF8String& txt);
    
    
    // append unicode char to UTF8 string
    static ofUTF8String   append(ofUTF8String txt, ofUniChar unicode);
    static ofUTF8String   append(ofUTF8String txt, ofUniString unicode);
    static ofUTF8String&  appendInPlace(ofUTF8String& txt, ofUniChar unicode);

    static ofUTF8String   appendUnsafe(ofUTF8String txt, ofUniChar unicode);
    static ofUTF8String   appendUnsafe(ofUTF8String txt, ofUniString unicode);
    static ofUTF8String&  appendInPlaceUnsafe(ofUTF8String& txt, ofUniChar unicode);

    
    // check to see if a UTF8 string is valid
    static bool     isValid(const ofUTF8String& txt);
    static bool     isValid(const ofUTF8String& txt, ofCharPtr fromPtr);
    static bool     isValid(const ofUTF8String& txt, ofCharPtr fromPtr, ofCharPtr toPtr);
    static bool     isValid(const ofUTF8String& txt, ofUTF8Idx fromIdx);
    static bool     isValid(const ofUTF8String& txt, ofUTF8Idx fromIdx, ofUTF8Idx toIdx);
    
    // calculate the number of UTF8 chars (string.length() returns the number of bytes)
    static int      distance(const ofUTF8String& txt);
    static int      distance(const ofUTF8String& txt, ofCharPtr fromPtr);
    static int      distance(const ofUTF8String& txt, ofCharPtr fromPtr, ofCharPtr toPtr);
    static int      distance(const ofUTF8String& txt, ofUTF8Idx fromIdx);
    static int      distance(const ofUTF8String& txt, ofUTF8Idx fromIdx, ofUTF8Idx toIdx);

    // TODO:
    // UTF8 repair method.
    // UTF8 get valid part of string method.
    
    static int      icompare(const ofUTF8String& utf8String0, const ofUTF8String& utf8String1);
    
    // unicode-based case conversion
    // TODO: can do all of these through ICU
	static ofUTF8String   toUpper(const ofUTF8String& str);
	static ofUTF8String&  toUpperInPlace(ofUTF8String& str);
	static ofUTF8String   toLower(const ofUTF8String& str);
	static ofUTF8String&  toLowerInPlace(ofUTF8String& str);
    
    ////////////////////////////////////////////////////////////////////
    // UTF8 ITERATION TOOLS ////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
    
    // FROM ICU

    // custom iterator helper
    static ofCharPtr beginCharPtr(const ofUTF8String& input); // gets the start pointer to a string (input.c_str())
    static ofCharPtr endCharPtr(const ofUTF8String& input);

    static ofUTF8Ptr toUTF8Ptr(const ofCharPtr ptr);
    static ofCharPtr toCharPtr(const ofUTF8Ptr ptr);
    
    
    // custom iterator helper
    static ofUTF8Ptr beginUTF8Ptr(const ofUTF8String& input); // gets the start pointer to a string (input.c_str())
    static ofUTF8Ptr endUTF8Ptr(const ofUTF8String& input);
    
    // Checked Iterators - No need to check input 
    ////////////////////////////////////////////////////////////////////
    static ofUniChar  get(const ofUTF8String& txt, ofCharPtr iter);  // reads the unichar at the current iter position
    static ofCharPtr  next(const ofUTF8String& txt, ofCharPtr iter); // moves the iterator to the next unicode start
    static ofCharPtr  prior(const ofUTF8String& txt, ofCharPtr iter); // moves the iterator to the previous unicode start
    static ofCharPtr  advance(const ofUTF8String& txt, ofCharPtr iter, int numToSkip = 1); // skips N unicode chars
    
    static ofUniChar  getNext(const ofUTF8String& txt, ofCharPtr& iter); // moves the iterator to the next unicode start and returns it
    static ofUniChar  getPrior(const ofUTF8String& txt, ofCharPtr& iter); // moves the iterator to the previous unicode start and returns it
    
    // do it with indicies
    static ofUniChar  get(const ofUTF8String& txt, ofUTF8Idx idx);  // reads the unichar at the current iter position
    static ofUTF8Idx  next(const ofUTF8String& txt, ofUTF8Idx idx); // moves the iterator to the next unicode start
    static ofUTF8Idx  prior(const ofUTF8String& txt, ofUTF8Idx idx); // moves the iterator to the previous unicode start
    static ofUTF8Idx  advance(const ofUTF8String& txt, ofUTF8Idx idx, int numToSkip = 1); // skips N unicode chars
    
    static ofUniChar  getNext(const ofUTF8String& txt, ofUTF8Idx& idx); // moves the iterator to the next unicode start and returns it
    static ofUniChar  getPrior(const ofUTF8String& txt, ofUTF8Idx& idx); // moves the iterator to the previous unicode start and returns it
    
    // Unchecked Iterators - Should check input string for valid UTF8 first 
    ////////////////////////////////////////////////////////////////////
    static ofUniChar  getUnsafe(const ofUTF8String& txt, ofCharPtr iter);  // reads the unichar at the current iter position
    static ofCharPtr  nextUnsafe(const ofUTF8String& txt, ofCharPtr iter); // moves the iterator to the next unicode start
    static ofCharPtr  priorUnsafe(const ofUTF8String& txt, ofCharPtr iter); // moves the iterator to the previous unicode start
    static ofCharPtr  advanceUnsafe(const ofUTF8String& txt, ofCharPtr iter, int numToSkip = 1); // skips N unicode chars
    
    static ofUniChar  getNextUnsafe(const ofUTF8String& txt, ofCharPtr& iter); // moves the iterator to the next unicode start and returns it
    static ofUniChar  getPriorUnsafe(const ofUTF8String& txt, ofCharPtr& iter); // moves the iterator to the previous unicode start and returns it

    // do it with indicies
    static ofUniChar  getUnsafe(const ofUTF8String& txt, ofUTF8Idx idx);  // reads the unichar at the current iter position
    static ofUTF8Idx  nextUnsafe(const ofUTF8String& txt, ofUTF8Idx idx); // moves the iterator to the next unicode start
    static ofUTF8Idx  priorUnsafe(const ofUTF8String& txt, ofUTF8Idx idx); // moves the iterator to the previous unicode start
    static ofUTF8Idx  advanceUnsafe(const ofUTF8String& txt, ofUTF8Idx idx, int numToSkip = 1); // skips N unicode chars
    
    static ofUniChar  getNextUnsafe(const ofUTF8String& txt, ofUTF8Idx& idx); // moves the iterator to the next unicode start and returns it
    static ofUniChar  getPriorUnsafe(const ofUTF8String& txt, ofUTF8Idx& idx); // moves the iterator to the previous unicode start and returns it

    
    
};