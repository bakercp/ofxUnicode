// =============================================================================
//
// Copyright (c) 2009-2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


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
    auto text32 = ofx::TextConverter::toUTF32(text);

    auto breaks = ofx::Linebreaker::findBreaks(text32, language);

    for (std::size_t i = 0; i < breaks.size(); ++i)
    {
        std::cout << ofx::TextConverter::toUTF8(text32[i]) << "\t->\t";

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
    auto text32 = ofx::TextConverter::toUTF32(text);

    auto breaks = ofx::Wordbreaker::findBreaks(text32, language);

    for (std::size_t i = 0; i < breaks.size(); ++i)
    {
        std::cout << ofx::TextConverter::toUTF8(text32[i]) << "\t->\t";

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
