#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    // some test strings
    string utf8_0 = "0123456789"; // length = 10, valid
    string utf8_1 = "ÁÂÃÄÅÆΑΩ€x"; // length = 10, valid
    string utf8_2 = "\u30A0\u30FF"; // length = 2, valid
    string utf8_3 = "\u03FF\u03E8"; // length = 2, valid
    string utf8_4 = "アァアィイゥウェエォ"; // length = 13, valid
    string utf8_5 = "\xe6\x97\xa5\xd1\x88\xfa"; // length = 6, not valid
    string utf8_6 = "éá´v´fúüü˚˚k"; // length = 6, not valid

    string utf8_7 = "والثعلب البني السريع."; // arabic, length = 21
    string utf8_8 = "бързо кафяво лисица."; // bulgarian
    string utf8_12 = "דער שנעל ברוין פוקס."; // yiddish
    string utf8_13 = "สุนัขจิ้งจอกสีน้ำตาลอย่างรวดเร็ว"; // thai
    string utf8_14 = "퀵 브라운 폭스 (빠른 갈색 여우)."; // korean
    
    // check for valid UTF8 sequences
    assert(ofUTF8::isValid(utf8_0) == true);
    assert(ofUTF8::isValid(utf8_1) == true);
    assert(ofUTF8::isValid(utf8_2) == true);
    assert(ofUTF8::isValid(utf8_3) == true);
    assert(ofUTF8::isValid(utf8_4) == true);
    assert(ofUTF8::isValid(utf8_5) == false); // will throw error
    assert(ofUTF8::isValid(utf8_6) == true); 
    assert(ofUTF8::isValid(utf8_7) == true); 
    assert(ofUTF8::isValid(utf8_8) == true); 
    assert(ofUTF8::isValid(utf8_12) == true); 
    assert(ofUTF8::isValid(utf8_13) == true); 
    assert(ofUTF8::isValid(utf8_14) == true); 


    // check for the length of the sequences
    assert(ofUTF8::distance(utf8_0) == 10);
    assert(ofUTF8::distance(utf8_1) == 10);
    assert(ofUTF8::distance(utf8_2) == 2);
    assert(ofUTF8::distance(utf8_3) == 2);
    assert(ofUTF8::distance(utf8_4) == 10);
    assert(ofUTF8::distance(utf8_7) == 21);
    
    // play with the bidirectional ofUTF8Iterator
    string utf8_9 = "\xf0\x90\x8d\x86\xe6\x97\xa5\xd1\x88";
    ofUTF8Iterator it = ofUTF8::iterator(utf8_9);
    ofUTF8Iterator it2 = it;
    assert (it2 == it);
    assert (*it == 0x10346);
    assert (*(++it) == 0x65e5);
    assert ((*it++) == 0x65e5);
    assert (*it == 0x0448);
    assert (it != it2);
    ofUTF8Iterator endit (utf8_9.c_str() + 9, utf8_9.c_str(), utf8_9.c_str() + 9);  
    assert (++it == endit);
    assert (*(--it) == 0x0448);
    assert ((*it--) == 0x0448);
    assert (*it == 0x65e5);
    assert (--it == ofUTF8Iterator(utf8_9.c_str(), utf8_9.c_str(), utf8_9.c_str() + 9));
    assert (*it == 0x10346);
    
    // append a ofUnichar
    string input;
    ofUniChar c = 0x30A0; 
    string end = ofUTF8::append(input,c); // should be ゠

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
    
    
        
}

