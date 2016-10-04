# Unit tests

This uses the [https://github.com/philsquared/Catch](Catch) single header C++
test suite. This test suite is licensed under
[http://www.boost.org/LICENSE_1_0.txt](Boost Software License, Version 1.0),
see file `LICENSE` in this directory or follow link.

## Code coverage
 * cmdline
 * data
    * Grid : 100%
    * Histogram : 100%
    * LinearNormalizer : 100%
    * LogarithmicPlusOneNormalizer : 100%
    * StandardSingleByteTransitionCounter
        * AsciiTransitionCounter: 100%
        * ByteTransitionCounter: 100%
 * except
 * io
    * FileReader : 100%
 * vis
    * Image : 100%
    * ImageBuilder : 100%
    * StandardColormap : 100%
    * TextHistogram : 100%

## Missing tests
Tests for the following classes are missing:  
 * options
 * BmpWriter
