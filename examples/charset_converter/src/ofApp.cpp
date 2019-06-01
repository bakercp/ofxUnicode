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

std::size_t nEncoderStrings = 10;

std::string encoderStrings[] =
{
    "költészet",
    "poetry",
    "FÜßBALL",
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
    std::vector<std::string> encoderStrings =
    {
        "0123456789",               // length = 10, valid
        "ABCDEFGHIJ",               // length = 10, valid
        "والثعلب البني السريع.", // arabic, length = 21
        "бързо кафяво лисица.", // bulgarian
        "דער שנעל ברוין פוקס." , // yiddish
        "สุนัขจิ้งจอกสีน้ำตาลอย่างรวดเร็ว", // thai
        "퀵 브라운 폭스 (빠른 갈색 여우).", // korean
        "költészet",
        "poetry",
        "FÜßBALL",
        "thơ",
        "詩",
        "ポエトリー",
        "поезия",
        "ಕಾವ್ಯ",
        "கவிதை",
        "أشعار"
    };

    auto a = ofx::Unicode::AEGEAN_NUMBERS;
    for (auto aa: a.charset())
    {
        std::cout << ofUTF8ToString(aa) << ", ";
    }
    std::cout << std::endl;

    std::string inputEncoding = "UTF-8";
    std::string outputEncoding = "UTF-32";

    ofx::TextConverter converter(inputEncoding, outputEncoding);

//    std::string input = "abcčde";
//    std::string input = "கவிதை";
    std::string input = "бързо кафяво лисица";
    std::string output;
    std::string reverseInput;

    converter.convert(input, output);

    ofx::TextConverter converterReverse(outputEncoding, inputEncoding);

    converterReverse.convert(output, reverseInput);

    std::cout << "Input >" << input << "<" << input.size()<< std::endl;
    std::cout << "output >" << output << "<" << output.size() << std::endl;
    std::cout << "reverseInput >" << reverseInput << "<" << reverseInput.size() << std::endl;

    auto encodings = ofx::TextConverter::encodings();

    std::cout << ofToString(encodings) << std::endl;



    std::vector<std::string> availableCodePages =
    {
//        0–5, 11–21, 26, 30–53, 255
//
//
//        0 [PC437: USA, Standard Europe]
//        1 [Katakana]
//        2 [PC850: Multilingual]
//        3 [PC860: Portuguese]
//        4 [PC863: Canadian-French]
//        5 [PC865: Nordic]
//
//        11 [PC851: Greek]
//        12 [PC853: Turkish]
//        13 [PC857: Turkish]
//        14 [PC737: Greek]
//        15 [ISO8859-7: Greek]
//        16 [WPC1252]
//        17 [PC866: Cyrillic #2]
//        18 [PC852: Latin 2]
//        19 [PC858: Euro]
//        20 [Thai Character Code 42]
//        21 [Thai Character Code 11]
//        26 [Thai Character Code 18]
//        30 [TCVN-3: Vietnamese]
//        31 [TCVN-3: Vietnamese]
//        32 [PC720: Arabic]
//        33 [WPC775: Baltic Rim]
//        34 [PC855: Cyrillic]
//        35 [PC861: Icelandic]
//        36 [PC862: Hebrew]
//        37 [PC864: Arabic]
//        38 [PC869: Greek]
//        39 [ISO8859-2: Latin 2]
//        40 [ISO8859-15: Latin 9]
//        41 [PC1098: Farsi]
//        42 [PC1118: Lithuanian]
//        43 [PC1119: Lithuanian]
//        44 [PC1125: Ukrainian]
//        45 [WPC1250: Latin 2]
//        46 [WPC1251: Cyrillic]
//        47 [WPC1253: Greek]
//        48 [WPC1254: Turkish]
//        49 [WPC1255: Hebrew]
//        50 [WPC1256: Arabic]
//        51 [WPC1257: Baltic Rim]
//        52 [WPC1258: Vietnamese]
//        53 [KZ-1048: Kazakhstan]
    };



}
