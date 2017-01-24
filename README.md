# cimplog

Simple logging library for rdklogger

[![Build Status](https://travis-ci.org/Comcast/cimplog.svg?branch=master)](https://travis-ci.org/Comcast/cimplog)
[![codecov.io](http://codecov.io/github/Comcast/cimplog/coverage.svg?branch=master)](http://codecov.io/github/Comcast/cimplog?branch=master)
[![Coverity](https://img.shields.io/coverity/scan/xxx.svg)]("https://scan.coverity.com/projects/comcast-cimplog)
[![Apache V2 License](http://img.shields.io/badge/license-Apache%20V2-blue.svg)](https://github.com/Comcast/cimplog/blob/master/LICENSE.txt)

# Building and Testing Instructions

```
mkdir build
cd build
cmake ..
make
make test
make coverage
firefox index.html
```

# Coding Formatter Settings

Please format pull requests using the following command to keep the style consistent.

```
astyle -A10 -S -f -U -p -D -c -xC90 -xL
```
