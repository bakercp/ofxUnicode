#pragma once

#include "ofMain.h"

#include <unicode/brkiter.h>

void printUnicodeString(const UnicodeString &s) {
    char charBuf[1000];
    s.extract(0, s.length(), charBuf, sizeof(charBuf)-1, 0);   
    charBuf[sizeof(charBuf)-1] = 0;          
    printf("%s", charBuf);
}


void printTextRange( BreakIterator& iterator, 
                    int32_t start, int32_t end )
{
    CharacterIterator *strIter = iterator.getText().clone();
    UnicodeString  s;
    strIter->getText(s);
    
    printf(" %ld %ld\t", (long)start, (long)end);
    printUnicodeString(UnicodeString(s, 0, start));
    printf("|");
    printUnicodeString(UnicodeString(s, start, end-start));
    printf("|");
    printUnicodeString(UnicodeString(s, end));
    puts("");
    delete strIter;
}


/* Print each element in order: */
void printEachForward( BreakIterator& boundary)
{
    int32_t start = boundary.first();
    for (int32_t end = boundary.next();
         end != BreakIterator::DONE;
         start = end, end = boundary.next())
    {
        printTextRange( boundary, start, end );
    }
}

/* Print each element in reverse order: */
void printEachBackward( BreakIterator& boundary)
{
    int32_t end = boundary.last();
    for (int32_t start = boundary.previous();
         start != BreakIterator::DONE;
         end = start, start = boundary.previous())
    {
        printTextRange( boundary, start, end );
    }
}

/* Print the first element */
void printFirst(BreakIterator& boundary)
{
    int32_t start = boundary.first();
    int32_t end = boundary.next();
    printTextRange( boundary, start, end );
}

/* Print the last element */
void printLast(BreakIterator& boundary)
{
    int32_t end = boundary.last();
    int32_t start = boundary.previous();
    printTextRange( boundary, start, end );
}

/* Print the element at a specified position */
void printAt(BreakIterator &boundary, int32_t pos )
{
    int32_t end = boundary.following(pos);
    int32_t start = boundary.previous();
    printTextRange( boundary, start, end );
}



class testApp : public ofBaseApp{
public:
    void setup();

    void breakSample();
    
};
