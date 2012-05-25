#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    // some test strings
    string utf8_0  = "0123456789";       // length = 10, valid
    string utf8_1  = "ÁÂÃÄÅÆΑΩ€x";       // length = 10, valid
    string utf8_2  = "\u30A0\u30FF";     // length = 2, valid
    string utf8_3  = "\u03FF\u03E8";     // length = 2, valid
    string utf8_4  = "アァアィイゥウェエォ"; // length = 13, valid
    string utf8_5  = "\xe6\x97\xa5\xd1\x88\xfa"; // length = 6, not valid
    string utf8_6  = "éá´v´fúüü˚˚k"; // length = 6, not valid
    string utf8_7  = "والثعلب البني السريع."; // arabic, length = 21
    string utf8_8  = "бързо кафяво лисица."; // bulgarian
    string utf8_12 = "דער שנעל ברוין פוקס."; // yiddish
    string utf8_13 = "สุนัขจิ้งจอกสีน้ำตาลอย่างรวดเร็ว"; // thai
    string utf8_14 = "퀵 브라운 폭스 (빠른 갈색 여우)."; // korean

    assert(ofUTF8::isValid(utf8_0) == true); // check a few for valid UTF8
    assert(ofUTF8::isValid(utf8_1) == true); // check a few for valid UTF8
    
    // combine unicode strings in the UTF8 string domain
    ofUTF8String utf8_01a = utf8_0 + utf8_1;  // add two ofUTF8Strings (simply an alias for std::string)
    
    // convert strings to UTF32 and combine in the UTF32 domain
    ofUniString uStr_0  = ofTextConverter::toUTF32(utf8_0); // UTF8 -> UTF32
    ofUniString uStr_1  = ofTextConverter::toUTF32(utf8_1); // UTF8 -> UTF32
    ofUniString uStr_01 = uStr_0 + uStr_1;                  // add in UTF32 domain
    
    ofUTF8String utf8_01b = ofTextConverter::toUTF8(uStr_01); // UTF32 -> UTF8
   
    assert(uStr_0.length()  == ofUTF8::distance(utf8_0)); // are lengths in UTF32 the same as distance in UTF8?  
    assert(uStr_1.length()  == ofUTF8::distance(utf8_1)); // are lengths in UTF32 the same as distance in UTF8?
    assert(uStr_01.length() == ofUTF8::distance(utf8_01b)); // are the sums the same?
    
    // convert to a string ofUnichar

    assert(ofTextConverter::toUTF8(0x30A1) == "\u30A1"); // just checking ...
    
    // do some case conversions
    string utf8_1_toLower = ofUTF8::toLower(utf8_1);
    cout << "From: " << utf8_1 << endl;
    cout << "  To: " << utf8_1_toLower << endl; 
    
    string utf8_6_toUpper = ofUTF8::toUpper(utf8_6);
    cout << "From: " << utf8_6 << endl;
    cout << "  To: " << utf8_6_toUpper << endl; 
    
    string utf8_8_toUpper = ofUTF8::toUpper(utf8_8);
    cout << "From: " << utf8_8 << endl;
    cout << "  To: " << utf8_8_toUpper << endl; 
    
    
    // iteration using the checked iterators
    {
        ofUTF8Ptr iter = ofUTF8::beginPtr(utf8_1);
        ofUTF8Ptr start = ofUTF8::beginPtr(utf8_1);
        ofUTF8Ptr stop = ofUTF8::endPtr(utf8_1);
        
        string utf8_1_out;
        while(iter < stop) {
            ofUniChar c = ofUTF8::getNext(iter,stop); // get the next unichar and iterate
            utf8_1_out += ofTextConverter::toUTF8(c);
        }
        
        assert(utf8_1 == utf8_1_out); // check!
        
    }
    
    // iteration using the unchecked iterators
    {
        // before using unchecked iterators, makes sure the whole thing is valid
        assert(ofUTF8::isValid(utf8_1) == true); // check a few for valid UTF8
        ofUTF8Ptr iter = ofUTF8::beginPtr(utf8_1);
        ofUTF8Ptr stop = ofUTF8::endPtr(utf8_1);
        
        string utf8_1_out;
        while(iter < stop) {
            ofUniChar c = ofUTF8::getNext(iter); // get the next unichar and iterate
            utf8_1_out += ofTextConverter::toUTF8(c);
        }
        
        assert(utf8_1 == utf8_1_out); // check!
        
    }
    
    // iteration using the unchecked iterators
    {
        string goal = "8675309"; // just something to shoot for
        string dest = "";
        // before using unchecked iterators, makes sure the whole thing is valid
        assert(ofUTF8::isValid(utf8_0) == true); // check a few for valid UTF8
        ofUTF8Ptr iter = ofUTF8::beginPtr(utf8_0);
        
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

        ofUTF8Iterator it = ofUTF8::iterator(utf8_0);
        
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
        it = ofUTF8::begin(utf8_0); // cheat back to 0
        dest += ofTextConverter::toUTF8(*it);
        it = ofUTF8::end(utf8_0); // cheat to 9
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
        
        ofUniString uni = ofTextConverter::toUTF32(utf8_0);
    
        dest += ofTextConverter::toUTF8(uni[8]);
        dest += ofTextConverter::toUTF8(uni[6]);
        dest += ofTextConverter::toUTF8(uni[7]);
        dest += ofTextConverter::toUTF8(uni[5]);
        dest += ofTextConverter::toUTF8(uni[3]);
        dest += ofTextConverter::toUTF8(uni[0]);
        dest += ofTextConverter::toUTF8(uni[9]);
        
        assert(goal == dest); // check!
    }

        
}

