//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    {
        // Multi-lingual panagrams for testing.
        std::string en = "The quick brown fox jumps over the lazy dog.";
        std::string de = "Victor jagt zwölf Boxkämpfer quer über den großen Sylter Deich";
        std::string es = "El veloz murciélago hindú comía feliz cardillo y kiwi. La cigüeña tocaba el saxofón detrás del palenque de paja.";
        std::string fr = "Buvez de ce whisky que le patron juge fameux.";
        std::string ru = "Эх, чужак! Общий съём цен шляп (юфть) – вдрызг!";
        std::string zh = "視野無限廣，窗外有藍天";  // Logographc scripts don't really have pangrams ...
        
        // break some lines in various languages

        dumpLineBreaks(en, "en");
        dumpLineBreaks(de, "de");
        dumpLineBreaks(es, "es");
        dumpLineBreaks(fr, "fr");
        dumpLineBreaks(ru, "ru");
        dumpLineBreaks(zh, "zh");
    }

    {
        // Multi-lingual panagrams for testing.
        std::string en = "Quickly";
        std::string de = "Boxkämpfer";
        std::string es = "Cardillo";
        std::string fr = "Patron";
        std::string ru = "Общий";
        std::string zh = "視";

        // break some lines in various languages

        dumpWordBreaks(en, "en");
        dumpWordBreaks(de, "de");
        dumpWordBreaks(es, "es");
        dumpWordBreaks(fr, "fr");
        dumpWordBreaks(ru, "ru");
        dumpWordBreaks(zh, "zh");
    }

}


void ofApp::dumpLineBreaks(const std::string& text, const std::string& language)
{
    std::cout << "--- " << language << " ---" << std::endl;

    // Convert it to utf32 text for easier output.
    auto text32 = ofx::UTF8::toUTF32(text);

    auto breaks = ofx::Linebreaker::findBreaks(text32, language);

    for (std::size_t i = 0; i < breaks.size(); ++i)
    {
        std::cout << ofx::UTF32::toUTF8(text32[i]) << "\t->\t";

        switch (breaks[i])
        {
            case ofx::Linebreaker::BreakType::MUST_BREAK:
                std::cout << "MUST_BREAK";
                break;
            case ofx::Linebreaker::BreakType::ALLOW_BREAK:
                std::cout << "ALLOW_BREAK";
                break;
            case ofx::Linebreaker::BreakType::NO_BREAK:
                std::cout << "NO_BREAK";
                break;
            case ofx::Linebreaker::BreakType::INSIDE_CHAR:
                std::cout << "INSIDE_CHAR";
                break;
        }

        std::cout << std::endl;
    }
}


void ofApp::dumpWordBreaks(const std::string& text, const std::string& language)
{
    std::cout << "--- " << language << " ---" << std::endl;

    // Convert it to utf32 text for easier output.
    auto text32 = ofx::UTF8::toUTF32(text);

    auto breaks = ofx::Wordbreaker::findBreaks(text32, language);

    for (std::size_t i = 0; i < breaks.size(); ++i)
    {
        std::cout << ofx::UTF32::toUTF8(text32[i]) << "\t->\t";

        switch (breaks[i])
        {
            case ofx::Wordbreaker::BreakType::ALLOW_BREAK:
                std::cout << "ALLOW_BREAK";
                break;
            case ofx::Wordbreaker::BreakType::NO_BREAK:
                std::cout << "NO_BREAK";
                break;
            case ofx::Wordbreaker::BreakType::INSIDE_CHAR:
                std::cout << "INSIDE_CHAR";
                break;
        }

        std::cout << std::endl;
    }
}
