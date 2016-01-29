//
//  ofxUTF8CPP.h
//  ofxUTFCPPExample
//
//  Created by Christopher Baker on 5/23/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofUnicode.h"
#include "utf8.h"

class ofUTF8 {
public:
     
    ////////////////////////////////////////////////////////////////////
    // UTF8 MANIPULATION TOOLS /////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////

    // append unicode char to UTF8 string
    //static std::string   append(std::string txt, char32_t unicode);
    //static std::string   append(std::string txt, std::u32string unicode);
    //static std::string&  appendInPlace(std::string& txt, char32_t unicode);

    // check to see if a UTF8 string is valid
    static bool isValid(const std::string& txt);
    static bool isValid(const char* iter, const char* end);
    
    // check to see if a string starts with a UTF8 BOM (byte order mark)
    static bool startsWithBOM(const std::string& txt);
    static bool startsWithBOM(const char* iter, const char* end);
    
    // attempt to repair a broken UTF8 string
    static std::string repair(const std::string& txt, char32_t replacement = -1);
    static std::string& repairInPlace(std::string& txt, char32_t replacement = -1);
    
    // calculate the number of UTF8 chars (string.length() returns the number of bytes)
    static std::size_t distance(const std::string& txt);
    static std::size_t distance(const char* iter, const char* end);
    
    // case insensitive comparison of UTF8 strings
    static int      icompare(const std::string& utf8String0, const std::string& utf8String1);
    
    // unicode-based case conversion
	static std::string toUpper(const std::string& str);
	static std::string& toUpperInPlace(std::string& str);
	static std::string toLower(const std::string& str);
	static std::string& toLowerInPlace(std::string& str);
    
    ////////////////////////////////////////////////////////////////////
    // UTF8 ITERATION TOOLS ////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
    
    // custom iterator helper
    static const char* beginPtr(const std::string& input); // gets the start pointer to a string (input.c_str())
    static const char* endPtr(const std::string& input);
    
    // custom bi-directional iterator
    static utf8::iterator<const char*> iterator(const std::string& input);
    static utf8::iterator<const char*> begin(const std::string& input);
    static utf8::iterator<const char*> end(const std::string& input);
    
    // Checked Iterators - No need to check input 
    ////////////////////////////////////////////////////////////////////
    static char32_t   getNext(const char* iter, const char* end);  // will increment iter and return value
    static char32_t   getPrior(const char* iter, const char* end); // will increment iter and return value
    static const char*   advance(const char* iter, const char* end, std::size_t numToSkip = 1); // skips N unicode chars
    //------------------------------------------------------------------
    //------------------------------------------------------------------
    static char32_t  get(const char* iter, const char* end);  // reads the unichar at the current iter position
    static const char*  next(const char* iter, const char* end); // moves the iterator to the next unicode start
    static const char*  prior(const char* iter, const char* start); // moves the iterator to the previous unicode start
    //------------------------------------------------------------------
    //------------------------------------------------------------------
    static char32_t get(const std::string& input, const char* iter = nullptr);  // reads the unichar at the current iter position
    static const char*  next(const std::string& input, const char* iter = nullptr); // moves the iterator to the next unicode start
    static const char*  prior(const std::string& input, const char* iter = nullptr); // moves the iterator to the previous unicode start
    static const char*  advance(const std::string& input, const char* iter = nullptr, std::size_t numToSkip = 1); // skips N unicode chars
    
    // Unchecked Iterators - Should check input string for valid UTF8 first 
    ////////////////////////////////////////////////////////////////////
    static char32_t  get(const char* iter);  // reads the unichar at the current iter position
    static const char*  next(const char* iter); // moves the iterator to the next unicode start
    static const char*  prior(const char* iter); // moves the iterator to the previous unicode start
    static const char*  advance(const char* iter, std::size_t numToSkip = 1); // skips N unicode chars
    
    static char32_t  getNext(const char* iter); // moves the iterator to the next unicode start and returns it
    static char32_t  getPrior(const char* iter); // moves the iterator to the previous unicode start and returns it

    
};