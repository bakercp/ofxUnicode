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
    fileReadWriteTests();


}

void testApp::conversionTests() {
    assert(ofTextConverter::toUTF8(0x30A1) == "\u30A1"); // just checking ...
    
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
    ofUniString uStr_0  = ofTextConverter::toUTF32(testStrings[0]); // UTF8 -> UTF32
    ofUniString uStr_1  = ofTextConverter::toUTF32(testStrings[1]); // UTF8 -> UTF32
    ofUniString uStr_01 = uStr_0 + uStr_1;                  // add in UTF32 domain
    
    ofUTF8String utf8_01b = ofTextConverter::toUTF8(uStr_01); // UTF32 -> UTF8
    
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
    // iteration using the checked iterators
    {
        ofUTF8Ptr iter = ofUTF8::beginPtr(testStrings[1]);
        ofUTF8Ptr start = ofUTF8::beginPtr(testStrings[1]);
        ofUTF8Ptr stop = ofUTF8::endPtr(testStrings[1]);
        
        string utf8_1_out;
        while(iter < stop) {
            ofUniChar c = ofUTF8::getNext(iter,stop); // get the next unichar and iterate
            utf8_1_out += ofTextConverter::toUTF8(c);
        }
        
        assert(testStrings[1] == utf8_1_out); // check!
        
    }
    
    // iteration using the unchecked iterators
    {
        // before using unchecked iterators, makes sure the whole thing is valid
        assert(ofUTF8::isValid(testStrings[1]) == true); // check a few for valid UTF8
        ofUTF8Ptr iter = ofUTF8::beginPtr(testStrings[1]);
        ofUTF8Ptr stop = ofUTF8::endPtr(testStrings[1]);
        
        string utf8_1_out;
        while(iter < stop) {
            ofUniChar c = ofUTF8::getNext(iter); // get the next unichar and iterate
            utf8_1_out += ofTextConverter::toUTF8(c);
        }
        
        assert(testStrings[1] == utf8_1_out); // check!
        
    }
    
    // iteration using the unchecked iterators
    {
        string goal = "8675309"; // just something to shoot for
        string dest = "";
        // before using unchecked iterators, makes sure the whole thing is valid
        assert(ofUTF8::isValid(testStrings[0]) == true); // check a few for valid UTF8
        ofUTF8Ptr iter = ofUTF8::beginPtr(testStrings[0]);
        
        iter = ofUTF8::advance(iter,8); // advance to 8
        dest += ofTextConverter::toUTF8(ofUTF8::get(iter));
        iter = ofUTF8::prior(iter);  // back one
        iter = ofUTF8::prior(iter); // back one
        dest += ofTextConverter::toUTF8(ofUTF8::get(iter));
        iter = ofUTF8::next(iter); // foward one
        dest += ofTextConverter::toUTF8(ofUTF8::get(iter));
        iter = ofUTF8::prior(iter); // back one
        iter = ofUTF8::prior(iter);  // back one
        dest += ofTextConverter::toUTF8(ofUTF8::get(iter));
        iter = ofUTF8::prior(iter); // back one
        iter = ofUTF8::prior(iter); // back one
        dest += ofTextConverter::toUTF8(ofUTF8::get(iter));
        iter = ofUTF8::prior(iter); // back one
        iter = ofUTF8::prior(iter); // back one
        iter = ofUTF8::prior(iter); // back one
        dest += ofTextConverter::toUTF8(ofUTF8::get(iter));
        iter = ofUTF8::advance(iter,9); // advance to 8
        dest += ofTextConverter::toUTF8(ofUTF8::get(iter));
        
        assert(goal == dest); // check!
    }
    
    // iteration using the the iterclass iterators
    {
        string goal = "8675309"; // just something to shoot for
        string dest = "";
        
        ofUTF8Iterator it = ofUTF8::iterator(testStrings[0]);
        
        it++;
        it++;
        it++;
        it++;
        it++;
        it++;
        it++;
        it++;
        dest += ofTextConverter::toUTF8(*it);
        it--;
        it--;
        dest += ofTextConverter::toUTF8(*it);
        it++;
        dest += ofTextConverter::toUTF8(*it);
        it--;
        it--;
        dest += ofTextConverter::toUTF8(*it);
        it--;
        it--;
        dest += ofTextConverter::toUTF8(*it);
        it = ofUTF8::begin(testStrings[0]); // cheat back to 0
        dest += ofTextConverter::toUTF8(*it);
        it = ofUTF8::end(testStrings[0]); // cheat to 9
        it--;
        dest += ofTextConverter::toUTF8(*it);
        cout << dest << endl;
        cout << goal << endl;
        assert(goal == dest); // check!
    }
    
    
    // one more way
    {
        string goal = "8675309"; // just something to shoot for
        string dest;
        
        ofUniString uni = ofTextConverter::toUTF32(testStrings[0]);
        
        dest += ofTextConverter::toUTF8(uni[8]); // the index where 8 lives
        dest += ofTextConverter::toUTF8(uni[6]); // etc
        dest += ofTextConverter::toUTF8(uni[7]);
        dest += ofTextConverter::toUTF8(uni[5]);
        dest += ofTextConverter::toUTF8(uni[3]);
        dest += ofTextConverter::toUTF8(uni[0]);
        dest += ofTextConverter::toUTF8(uni[9]);
        
        assert(goal == dest); // check!
    }
    
    
    
     // one more way
     {
     string goal = "8675309"; // just something to shoot for
     string dest;
     
     ofUniString uni = ofTextConverter::toUTF32(testStrings[0]);
     ofUniString uniDest;
     
     uniDest.push_back(uni[8]);
     uniDest.push_back(uni[6]);
     uniDest.push_back(uni[7]);
     uniDest.push_back(uni[5]);
     uniDest.push_back(uni[3]);
     uniDest.push_back(uni[0]);
     uniDest.push_back(uni[9]);
     
     dest = ofTextConverter::toUTF8(uniDest);
     
     assert(goal == dest); // check!
     }
     
     // one more way
     {
         string goal = "8675309"; // just something to shoot for
         string dest;
         
         ofUniString uni = ofTextConverter::toUTF32(testStrings[0]);
         ofUniString uniDest;
         
         uniDest += uni[8];
         uniDest += uni[6];
         uniDest += uni[7];
         uniDest += uni[5];
         uniDest += uni[3];
         uniDest += uni[0];
         uniDest += uni[9];
         
         dest = ofTextConverter::toUTF8(uniDest);
         assert(goal == dest); // check!
     }
     
    // one more way
    {
        string goal = "8675309"; // just something to shoot for
        string dest;
        
        ofUniString uni = ofTextConverter::toUTF32(testStrings[0]);
        ofUniString uniDest;
        
        uniDest += uni[8];
        uniDest += uni[6];
        uniDest += uni[7];
        uniDest += uni[5];
        uniDest += uni[3];
        uniDest += uni[0];
        uniDest += uni[9];
        
        dest = ofTextConverter::toUTF8(uniDest);
        assert(goal == dest); // check!
    }


}

void testApp::fileReadWriteTests() {

//    // read files into strings
//    ofFile test0("test_UTF8.txt");
//    ofBuffer buff0 = test0.readToBuffer();
//    cout << buff0.size() << endl;
//    string t0 = ofTextConverter::convert(buff0,OF_TEXT_ENCODING_UTF8,OF_TEXT_ENCODING_UTF8); // only utf8 encoded
//    ofFile test1("test_UTF16.txt");
//    ofBuffer buff1 = test1.readToBuffer();
//    cout << buff1.size() << endl;
//    string t1 = ofTextConverter::convert(buff1,OF_TEXT_ENCODING_UTF16,OF_TEXT_ENCODING_UTF8); // only utf8 encoded
//    
    
    
    //assert(ofUTF8::isValid(t0) == true); 
    //assert(ofUTF8::isValid(t1) == false); // UTF16
    
    //cout << ofUTF8::distance(t0) << endl;
    //cout << ofUTF8::distance(t1) << endl;
    
   // string t1_utf8 = ofTextConverter::convert(t1, OF_TEXT_ENCODING_UTF16, OF_TEXT_ENCODING_UTF8);
  
//   ofUTF16Char utf16 =  ofTextConverter::toUTF16(<#const ofUTF8String &input#>)
  
  //  ofTextConverter::toUTF8(<#const ofUTF16String &input#>);
    
//    for(int i = 0; i < t1_utf8;
//    ofToHex(<#const T &value#>)
//    cout << " --- " << endl;
//    cout << t0.length() << "|" << ofUTF8::distance(t0) <<  endl;
//    cout << t1.size() << "|" << endl;
//    //cout << t1_utf8.length() << "|" << endl;
//    
//    cout << t0 << endl;
//    cout << t1 << endl;
//    
//    
//    
    
    
    
}
