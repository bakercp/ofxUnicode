#include "testApp.h"

int nTestStrings = 8;
string testStrings[] = {
    "0123456789",       // length = 10, valid
    "ABCDEFGHIJ",       // length = 10, valid
    "\xe6\x97\xa5\xd1\x88\xfa", // length = 6, not valid
    "والثعلب البني السريع.", // arabic, length = 21
    "бързо кафяво лисица.", // bulgarian
    "דער שנעל ברוין פוקס.", // yiddish
    "สุนัขจิ้งจอกสีน้ำตาลอย่างรวดเร็ว", // thai
    "퀵 브라운 폭스 (빠른 갈색 여우).", // korean
};

int nEncoderStrings = 9;
string encoderStrings[] = {
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

//--------------------------------------------------------------
void testApp::setup(){

    validationTests();
    concatTests();
    conversionTests();
    distanceTests();
    iterationTests();
    charsetDetection();


}

void testApp::conversionTests() {
    assert(ofUTF32::toUTF8(0x30A1) == "\u30A1"); // just checking ...
    
    // do some case conversions
    string utf8_1_toLower = ofUTF8::toLower(testStrings[1]);
    cout << "From: " << testStrings[1] << endl;
    cout << "  To: " << utf8_1_toLower << endl; 
    
    string utf8_6_toUpper = ofUTF8::toUpper(encoderStrings[0]);
    cout << "From: " << encoderStrings[0] << endl;
    cout << "  To: " << utf8_6_toUpper << endl; 
    
    string utf8_8_toUpper = ofUTF8::toUpper(encoderStrings[1]);
    cout << "From: " << encoderStrings[1] << endl;
    cout << "  To: " << utf8_8_toUpper << endl; 

}


void testApp::validationTests() {
    assert(ofUTF8::isValid(testStrings[0]) == true); // check a few for valid UTF8
    assert(ofUTF8::isValid(testStrings[1]) == true); // check a few for valid UTF8
    assert(ofUTF8::isValid(testStrings[2]) == false); // check a few for valid UTF8

}

void testApp::concatTests() {
    // combine unicode strings in the UTF8 string domain
    ofUTF8String utf8_01a = testStrings[0] + testStrings[1];  // add two ofUTF8Strings (simply an alias for std::string)
    
    // convert strings to UTF32 and combine in the UTF32 domain
    ofUniString uStr_0  = ofUTF8::toUTF32(testStrings[0]); // UTF8 -> UTF32
    ofUniString uStr_1  = ofUTF8::toUTF32(testStrings[1]); // UTF8 -> UTF32
    ofUniString uStr_01 = uStr_0 + uStr_1;                  // add in UTF32 domain
    
    ofUTF8String utf8_01b = ofUTF32::toUTF8(uStr_01); // UTF32 -> UTF8
    
    assert(uStr_0.length()  == ofUTF8::distance(testStrings[0])); // are lengths in UTF32 the same as distance in UTF8?  
    assert(uStr_1.length()  == ofUTF8::distance(testStrings[1])); // are lengths in UTF32 the same as distance in UTF8?
    assert(uStr_01.length() == ofUTF8::distance(utf8_01b)); // are the sums the same?
}


void testApp::distanceTests() {
    assert(ofUTF8::distance(testStrings[0]) == 10);
    assert(ofUTF8::distance(testStrings[1]) == 10);
    assert(ofUTF8::distance(testStrings[3]) == 21);
 }

void testApp::iterationTests() {
 //iteration using the checked iterators
    {
        ofCharPtr iter = ofUTF8::beginCharPtr(testStrings[1]);
        ofCharPtr stop = ofUTF8::endCharPtr(testStrings[1]);
        
        string utf8_1_out;
        while(iter < stop) {
            ofUniChar c = ofUTF8::getNext(testStrings[1],iter); // get the next unichar and iterate
            utf8_1_out += ofUTF32::toUTF8(c);
        }
        
        assert(testStrings[1] == utf8_1_out); // check!
        
    }
    
    // iteration using the unchecked iterators
    {
        // before using unchecked iterators, makes sure the whole thing is valid
        assert(ofUTF8::isValid(testStrings[1]) == true); // check a few for valid UTF8
        ofCharPtr iter = ofUTF8::beginCharPtr(testStrings[1]);
        ofCharPtr stop = ofUTF8::endCharPtr(testStrings[1]);
        
        string utf8_1_out;
        
        int i = 0;
        while(iter < stop) {
            ofUniChar c = ofUTF8::getNextUnsafe(testStrings[1],iter); // get the next unichar and iterate
            utf8_1_out += ofUTF32::toUTF8(c);
        }
        
        assert(testStrings[1] == utf8_1_out); // check!
        
    }
    
    // iteration using the unchecked iterators
    {
        string goal = "8675309"; // just something to shoot for
        string dest = "";
        // before using unchecked iterators, makes sure the whole thing is valid
        assert(ofUTF8::isValid(testStrings[0]) == true); // check a few for valid UTF8
        ofCharPtr iter = ofUTF8::beginCharPtr(testStrings[0]);
        
        iter = ofUTF8::advance(testStrings[0],iter,8); // advance to 8
        dest += ofUTF32::toUTF8(ofUTF8::get(testStrings[0],iter));
        iter = ofUTF8::prior(testStrings[0],iter);  // back one
        iter = ofUTF8::prior(testStrings[0],iter); // back one
        dest += ofUTF32::toUTF8(ofUTF8::get(testStrings[0],iter));
        iter = ofUTF8::next(testStrings[0],iter); // foward one
        dest += ofUTF32::toUTF8(ofUTF8::get(testStrings[0],iter));
        iter = ofUTF8::prior(testStrings[0],iter); // back one
        iter = ofUTF8::prior(testStrings[0],iter);  // back one
        dest += ofUTF32::toUTF8(ofUTF8::get(testStrings[0],iter));
        iter = ofUTF8::prior(testStrings[0],iter); // back one
        iter = ofUTF8::prior(testStrings[0],iter); // back one
        dest += ofUTF32::toUTF8(ofUTF8::get(testStrings[0],iter));
        iter = ofUTF8::prior(testStrings[0],iter); // back one
        iter = ofUTF8::prior(testStrings[0],iter); // back one
        iter = ofUTF8::prior(testStrings[0],iter); // back one
        dest += ofUTF32::toUTF8(ofUTF8::get(testStrings[0],iter));
        iter = ofUTF8::advance(testStrings[0],iter,9); // advance to 8
        
        
        
        dest += ofUTF32::toUTF8(ofUTF8::get(testStrings[0],iter));
                
        assert(goal == dest); // check!
    }

    {
        
        string goal = "8675309"; // just something to shoot for
        string dest = "";
        // before using unchecked iterators, makes sure the whole thing is valid
        assert(ofUTF8::isValid(testStrings[0]) == true); // check a few for valid UTF8
        ofCharPtr iter = ofUTF8::beginCharPtr(testStrings[0]);
        
        for(int i = 0; i < 7; i++) {
            dest += ofUTF32::toUTF8(ofUTF8::get(testStrings[0],iter));
            iter = ofUTF8::advance(testStrings[0],iter,1); // advance to 8
        }
        
        cout << "dest=" << dest << endl;
    }
    
    
    // one more way
    {
        string goal = "8675309"; // just something to shoot for
        string dest;
        
        ofUniString uni = ofUTF8::toUTF32(testStrings[0]);
        
        dest += ofUTF32::toUTF8(uni[8]); // the index where 8 lives
        dest += ofUTF32::toUTF8(uni[6]); // etc
        dest += ofUTF32::toUTF8(uni[7]);
        dest += ofUTF32::toUTF8(uni[5]);
        dest += ofUTF32::toUTF8(uni[3]);
        dest += ofUTF32::toUTF8(uni[0]);
        dest += ofUTF32::toUTF8(uni[9]);
        
        assert(goal == dest); // check!
    }
    
    
    
     // one more way
     {
     string goal = "8675309"; // just something to shoot for
     string dest;
     
     ofUniString uni = ofUTF8::toUTF32(testStrings[0]);
     ofUniString uniDest;
     
     uniDest.push_back(uni[8]);
     uniDest.push_back(uni[6]);
     uniDest.push_back(uni[7]);
     uniDest.push_back(uni[5]);
     uniDest.push_back(uni[3]);
     uniDest.push_back(uni[0]);
     uniDest.push_back(uni[9]);
     
     dest = ofUTF32::toUTF8(uniDest);
     
     assert(goal == dest); // check!
     }
     
     // one more way
     {
         string goal = "8675309"; // just something to shoot for
         string dest;
         
         ofUniString uni = ofUTF8::toUTF32(testStrings[0]);
         ofUniString uniDest;
         
         uniDest += uni[8];
         uniDest += uni[6];
         uniDest += uni[7];
         uniDest += uni[5];
         uniDest += uni[3];
         uniDest += uni[0];
         uniDest += uni[9];
         
         dest = ofUTF32::toUTF8(uniDest);
         assert(goal == dest); // check!
     }
     
    // one more way
    {
        string goal = "8675309"; // just something to shoot for
        string dest;
        
        ofUniString uni = ofUTF8::toUTF32(testStrings[0]);
        ofUniString uniDest;
        
        uniDest += uni[8];
        uniDest += uni[6];
        uniDest += uni[7];
        uniDest += uni[5];
        uniDest += uni[3];
        uniDest += uni[0];
        uniDest += uni[9];
        
        dest = ofUTF32::toUTF8(uniDest);
        assert(goal == dest); // check!
    }


}

void testApp::charsetDetection() {

    vector<string> charsets = ofTextUtilities::listAvailableCharsets();
    for(int i = 0; i < charsets.size(); i++) {
        cout << charsets[i] << endl;
        }
        
        ofBuffer b0 = ofBufferFromFile("test_UTF8.txt");
        ofBuffer b1 = ofBufferFromFile("test_UTF16_NO_BOM.txt");
        ofBuffer b2 = ofBufferFromFile("test_UTF16.txt");
        ofBuffer b3 = ofBufferFromFile("test_UTF8_BIG5.txt");
        ofBuffer b4 = ofBufferFromFile("test_UTF8_W_BOM.txt");
        
        bool success;
        string lang;
        string name;
        int confidence;
        
        success = ofTextUtilities::detectCharset(b0.getText(), name, lang, confidence);
        cout << "success=" << success << " name=" << name << " lang=" << lang << " conf=" << confidence << endl;
        success = ofTextUtilities::detectCharset(b1.getText(), name, lang, confidence);
        cout << "success=" << success << " name=" << name << " lang=" << lang << " conf=" << confidence << endl;
        success = ofTextUtilities::detectCharset(b2.getText(), name, lang, confidence);
        cout << "success=" << success << " name=" << name << " lang=" << lang << " conf=" << confidence << endl;
        success = ofTextUtilities::detectCharset(b3.getText(), name, lang, confidence);
        cout << "success=" << success << " name=" << name << " lang=" << lang << " conf=" << confidence << endl;
        
        string big5 = b3.getText();
        success = ofTextUtilities::convertCharsetToUTF8(big5,name);
        
        cout << b3.getText() << endl;
        cout << big5 << endl;
        
        
        success = ofTextUtilities::detectCharset(b4.getText(), name, lang, confidence);
        cout << "success=" << success << " name=" << name << " lang=" << lang << " conf=" << confidence << endl;
    
}

