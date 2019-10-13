# ofxUnicode

## Description

An openFrameworks addon that wraps various Unicode algorithms.

## Features

-   Unicode Line / Word Breaking.
-   Unicode BiDi Formatting.
-   Unicode Case Folding (`toUpper(...)`, `toLower(...)`, etc).
-   Unicode Normalization.
-   Unicode codepoint queries (`isTitle(...)`, `isUpper(...)`).
-   UTF8 ⬌ UTF16 ⬌ UTF32 conversion.
-   Case-insensitive Unicode string comparisons (with case folding and normalization).

This addon employs the following 3rd party libraries:

-   [harfbuzz](https://github.com/harfbuzz/harfbuzz) ([MIT](https://opensource.org/licenses/MIT))
-   [fribidi](https://fribidi.org/) ([LGPL-2.0](https://opensource.org/licenses/LGPL-2.0))
-   [libraqm](https://github.com/HOST-Oman/libraqm) ([MIT](https://opensource.org/licenses/MIT))
-   [libiconv](https://www.gnu.org/software/libiconv/)([LGPL](https://opensource.org/licenses/LGPL))
-   [ucdn](https://github.com/grigorig/ucdn) ([ISC](https://opensource.org/licenses/ISC))
-   [unibreak](https://github.com/adah1972/libunibreak) ([Zlib](https://opensource.org/licenses/Zlib))
-   [utf8proc](https://github.com/JuliaLang/utf8proc) ([MIT](https://opensource.org/licenses/MIT))


## Getting Started

To build and install the 3rd party libraries, run `scripts/build.sh`.

To get started, generate the example project files using the openFrameworks [Project Generator](http://openframeworks.cc/learning/01_basics/how_to_add_addon_to_project/).

## Documentation

API documentation can be found here.

## Build Status

Linux, macOS [![Build Status](https://travis-ci.org/bakercp/ofxUnicode.svg?branch=master)](https://travis-ci.org/bakercp/ofxHTTP)

Visual Studio, MSYS [![Build status](https://ci.appveyor.com/api/projects/status/cvahckay2t65tl2x/branch/master?svg=true)](https://ci.appveyor.com/project/bakercp/ofxunicode/branch/master)

## Compatibility

### Branches

The `stable` branch of this repository is meant to be compatible with the openFrameworks [stable branch](https://github.com/openframeworks/openFrameworks/tree/stable), which corresponds to the latest official openFrameworks release.

The `master` branch of this repository is meant to be compatible with the openFrameworks [master branch](https://github.com/openframeworks/openFrameworks/tree/master).

Some past openFrameworks releases are supported via tagged versions, but only `stable` and `master` branches are actively supported.

### Requirements

-   None

## Versioning

This project uses [Semantic Versioning](http://semver.org/), although strict adherence will only come into effect at version 1.0.0.

## Licensing

See [LICENSE.md](LICENSE.md).

## Contributing

Pull Requests are always welcome, so if you make any improvements please feel free to float them back upstream :)

1.  Fork this repository.
2.  Create your feature branch (`git checkout -b my-new-feature`).
3.  Commit your changes (`git commit -am 'Add some feature'`).
4.  Push to the branch (`git push origin my-new-feature`).
5.  Create new Pull Request.
