# cimplog

Simple logging library for rdklogger

[![Build Status](https://travis-ci.com/xmidt-org/cimplog.svg?branch=master)](https://travis-ci.com/xmidt-org/cimplog)
[![codecov.io](http://codecov.io/github/xmidt-org/cimplog/coverage.svg?branch=master)](http://codecov.io/github/xmidt-org/cimplog?branch=master)
[![Coverity](https://img.shields.io/coverity/scan/11572.svg)]("https://scan.coverity.com/projects/comcast-cimplog)
[![Apache V2 License](http://img.shields.io/badge/license-Apache%20V2-blue.svg)](https://github.com/xmidt-org/cimplog/blob/master/LICENSE.txt)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=xmidt-org_cimplog&metric=alert_status)](https://sonarcloud.io/dashboard?id=xmidt-org_cimplog)

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
