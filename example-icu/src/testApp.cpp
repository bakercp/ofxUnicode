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

}

void testApp::breakSample() {
    
    
}

