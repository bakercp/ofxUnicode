//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "stdio.h"
#include "assert.h"

#include "ofApp.h"


std::size_t nTestStrings = 8;

std::string testStrings[] =
{
    "0123456789",               // length = 10, valid
    "ABCDEFGHIJ",               // length = 10, valid
    "\xe6\x97\xa5\xd1\x88\xfa", // length = 6, not valid
    "والثعلب البني السريع.", // arabic, length = 21
    "бързо кафяво лисица.", // bulgarian
    "דער שנעל ברוין פוקס." , // yiddish
    "สุนัขจิ้งจอกสีน้ำตาลอย่างรวดเร็ว", // thai
    "퀵 브라운 폭스 (빠른 갈색 여우).", // korean
};

std::size_t nEncoderStrings = 9;

std::string encoderStrings[] =
{
    "költészet",
    "poetry",
    "thơ",
    "詩",
    "ポエトリー",
    "поезия",
    "ಕಾವ್ಯ",
    "கவிதை",
    "أشعار"
};



void ofApp::setup()
{
    validationTests();
    concatTests();
    conversionTests();
    distanceTests();
    iterationTests();
//    fileReadWriteTests();
}


void ofApp::conversionTests()
{
    assert(ofx::UTF32::toUTF8(0x30A1) == "\u30A1"); // just checking ...
    
    // do some case conversions
    std::string utf8_1_toLower = ofx::UTF8::toLower(testStrings[1]);
    std::cout << "From: " << testStrings[1] << std::endl;
    std::cout << "  To: " << utf8_1_toLower << std::endl;
    
    std::string utf8_6_toUpper = ofx::UTF8::toUpper(encoderStrings[0]);
    std::cout << "From: " << encoderStrings[0] << std::endl;
    std::cout << "  To: " << utf8_6_toUpper << std::endl;
    
    std::string utf8_8_toUpper = ofx::UTF8::toUpper(encoderStrings[1]);
    std::cout << "From: " << encoderStrings[1] << std::endl;
    std::cout << "  To: " << utf8_8_toUpper << std::endl;

    std::cout << "------------- of native -----------" << std::endl;
    {
    // do some case conversions
    std::string utf8_1_toLower = ofToLower(testStrings[1]);
    std::cout << "From: " << testStrings[1] << std::endl;
    std::cout << "  To: " << utf8_1_toLower << std::endl;

    std::string utf8_6_toUpper = ofToUpper(encoderStrings[0]);
    std::cout << "From: " << encoderStrings[0] << std::endl;
    std::cout << "  To: " << utf8_6_toUpper << " (incorrect w/o correct locale)" << std::endl;

    std::string utf8_6_toUpper_hu = ofToUpper(encoderStrings[0], "hu_HU");
    std::cout << "From: " << encoderStrings[0] << std::endl;
    std::cout << "  To: " << utf8_6_toUpper_hu << " (correct w/ hu_HU locale)" << std::endl;

    std::string utf8_8_toUpper = ofToUpper(encoderStrings[1]);
    std::cout << "From: " << encoderStrings[1] << std::endl;
    std::cout << "  To: " << utf8_8_toUpper << std::endl;
    }

}



void ofApp::validationTests()
{
    assert(ofx::UTF8::isValid(testStrings[0]) == true); // check a few for valid UTF8
    assert(ofx::UTF8::isValid(testStrings[1]) == true); // check a few for valid UTF8
    assert(ofx::UTF8::isValid(testStrings[2]) == false); // check a few for valid UTF8
}

void ofApp::concatTests()
{
    // combine unicode strings in the UTF8 string domain
    std::string utf8_01a = testStrings[0] + testStrings[1];  // add two std::strings (simply an alias for std::string)
    
    // convert strings to UTF32 and combine in the UTF32 domain
    std::u32string uStr_0  = ofx::UTF8::toUTF32(testStrings[0]); // UTF8 -> UTF32
    std::u32string uStr_1  = ofx::UTF8::toUTF32(testStrings[1]); // UTF8 -> UTF32
    std::u32string uStr_01 = uStr_0 + uStr_1;                  // add in UTF32 domain
    
    std::string utf8_01b = ofx::UTF32::toUTF8(uStr_01); // UTF32 -> UTF8
    
    assert(uStr_0.length()  == ofx::UTF8::distance(testStrings[0])); // are lengths in UTF32 the same as distance in UTF8?  
    assert(uStr_1.length()  == ofx::UTF8::distance(testStrings[1])); // are lengths in UTF32 the same as distance in UTF8?
    assert(uStr_01.length() == ofx::UTF8::distance(utf8_01b)); // are the sums the same?
}


void ofApp::distanceTests()
{
    assert(ofx::UTF8::distance(testStrings[0]) == 10);
    assert(ofx::UTF8::distance(testStrings[1]) == 10);
    assert(ofx::UTF8::distance(testStrings[3]) == 21);
}


void ofApp::iterationTests()
{
    // iteration using the the iterclass iterators
    {
        std::string goal = "8675309"; // just something to shoot for
        std::string dest = "";


        ofUTF8Iterator iterator(testStrings[0]);

        auto it = iterator.begin();
        
        it++;
        it++;
        it++;
        it++;
        it++;
        it++;
        it++;
        it++;
        dest += ofx::UTF32::toUTF8(*it);
        it--;
        it--;
        dest += ofx::UTF32::toUTF8(*it);
        it++;
        dest += ofx::UTF32::toUTF8(*it);
        it--;
        it--;
        dest += ofx::UTF32::toUTF8(*it);
        it--;
        it--;
        dest += ofx::UTF32::toUTF8(*it);
        it = iterator.begin();
        dest += ofx::UTF32::toUTF8(*it);
        it = iterator.end();
        it--;
        dest += ofx::UTF32::toUTF8(*it);
        std::cout << dest << std::endl;
        std::cout << goal << std::endl;
        assert(goal == dest); // check!
    }

    // one more way
    {
        std::string goal = "8675309"; // just something to shoot for
        std::string dest;
        
        std::u32string uni = ofx::UTF8::toUTF32(testStrings[0]);
        
        dest += ofx::UTF32::toUTF8(uni[8]); // the index where 8 lives
        dest += ofx::UTF32::toUTF8(uni[6]); // etc
        dest += ofx::UTF32::toUTF8(uni[7]);
        dest += ofx::UTF32::toUTF8(uni[5]);
        dest += ofx::UTF32::toUTF8(uni[3]);
        dest += ofx::UTF32::toUTF8(uni[0]);
        dest += ofx::UTF32::toUTF8(uni[9]);
        
        assert(goal == dest); // check!
    }

     // one more way
     {
     std::string goal = "8675309"; // just something to shoot for
     std::string dest;
     
     std::u32string uni = ofx::UTF8::toUTF32(testStrings[0]);
     std::u32string uniDest;
     
     uniDest.push_back(uni[8]);
     uniDest.push_back(uni[6]);
     uniDest.push_back(uni[7]);
     uniDest.push_back(uni[5]);
     uniDest.push_back(uni[3]);
     uniDest.push_back(uni[0]);
     uniDest.push_back(uni[9]);
     
     dest = ofx::UTF32::toUTF8(uniDest);
     
     assert(goal == dest); // check!
     }

     // one more way
     {
         std::string goal = "8675309"; // just something to shoot for
         std::string dest;
         
         std::u32string uni = ofx::UTF8::toUTF32(testStrings[0]);
         std::u32string uniDest;
         
         uniDest += uni[8];
         uniDest += uni[6];
         uniDest += uni[7];
         uniDest += uni[5];
         uniDest += uni[3];
         uniDest += uni[0];
         uniDest += uni[9];
         
         dest = ofx::UTF32::toUTF8(uniDest);
         assert(goal == dest); // check!
     }
     
    // one more way
    {
        std::string goal = "8675309"; // just something to shoot for
        std::string dest;
        
        std::u32string uni = ofx::UTF8::toUTF32(testStrings[0]);
        std::u32string uniDest;
        
        uniDest += uni[8];
        uniDest += uni[6];
        uniDest += uni[7];
        uniDest += uni[5];
        uniDest += uni[3];
        uniDest += uni[0];
        uniDest += uni[9];
        
        dest = ofx::UTF32::toUTF8(uniDest);
        assert(goal == dest); // check!
    }


}

void ofApp::fileReadWriteTests() {

//    // read files into strings
//    ofFile test0("test_UTF8.txt");
//    ofBuffer buff0 = test0.readToBuffer();
//    cout << buff0.size() << endl;
//    string t0 = ofx::TextConverter::convert(buff0,OF_TEXT_ENCODING_UTF8,OF_TEXT_ENCODING_UTF8); // only utf8 encoded
//    ofFile test1("test_UTF16.txt");
//    ofBuffer buff1 = test1.readToBuffer();
//    cout << buff1.size() << endl;
//    string t1 = ofx::TextConverter::convert(buff1,OF_TEXT_ENCODING_UTF16,OF_TEXT_ENCODING_UTF8); // only utf8 encoded
//    
    
    
    //assert(ofx::UTF8::isValid(t0) == true); 
    //assert(ofx::UTF8::isValid(t1) == false); // UTF16
    
    //cout << ofx::UTF8::distance(t0) << endl;
    //cout << ofx::UTF8::distance(t1) << endl;
    
   // string t1_utf8 = ofx::TextConverter::convert(t1, OF_TEXT_ENCODING_UTF16, OF_TEXT_ENCODING_UTF8);
  
//   ofUTF16Char utf16 =  ofx::TextConverter::toUTF16(<#const std::string &input#>)
  
  //  ofx::TextConverter::toUTF8(<#const std::u16string &input#>);
    
//    for(int i = 0; i < t1_utf8;
//    ofToHex(<#const T &value#>)
//    cout << " --- " << endl;
//    cout << t0.length() << "|" << ofx::UTF8::distance(t0) <<  endl;
//    cout << t1.size() << "|" << endl;
//    //cout << t1_utf8.length() << "|" << endl;
//    
//    cout << t0 << endl;
//    cout << t1 << endl;
//    
//    
//    
    
    
    
}
