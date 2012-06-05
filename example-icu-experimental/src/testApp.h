#pragma once

#include "ofMain.h"

#include <unicode/brkiter.h>
#include "unicode/uchriter.h"
#include "unicode/schriter.h"
#include "unicode/ustring.h"
#include <unicode/brkiter.h>
#include <unicode/ustdio.h>
#include "unicode/utypes.h"
#include "unicode/ucsdet.h"
#include "unicode/utypes.h"
#include "unicode/uchar.h"
#include "unicode/uclean.h"


#include "ofTextUtilities.h"

class testApp : public ofBaseApp{
public:
    void setup();

    void breakSample();
    void caseConversion();
    
    void charIter();
    void strIter();
    
    void ucodeData();
    void unicodeDemo();
    
};
