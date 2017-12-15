# RaceTheMoon

| Windows Build | Linux / Mac Build |
| ------------- | ------------- |
| [![Build status](https://ci.appveyor.com/api/projects/status/rgyc1jieyqj4a1ph?svg=true)](https://ci.appveyor.com/project/Zoeoeh/racethemoon)| [![Unix Build Status](https://api.travis-ci.org/Zoeoeh/RaceTheMoon.svg?branch=master)](https://api.travis-ci.org/Zoeoeh/RaceTheMoon) |


Hello this is RACE THE MOON!
http://beejpersson.blogspot.co.uk/2017/12/race-moon-title-screen.html

 Keep flying, you can make it home.
 
 To build this from source, ensure you have the minimum Cmake version 3.10 installed.
 
 This repository uses git submodules so ensure to use the command below to clone the dependent repositories.
 
 git submodule update --init
 
 
 OpenAL is also required for sound output. If sound files are missing they can be downloaded from here: https://drive.google.com/open?id=12Atx_ze0FtyPh0-SWJqqNE2YCwWcWGMP
 
 If using the Microsoft Visual studio compiler, you must right click on the project "Race The Moon"'s and click properies. Under Debugging, change the working directory from $(ProjectDir) to $(TargetDir) if the shaders are not found. This will ensure the resource folder in the repository is looked at.

There is an installer with our latest release for both 32-bit and 64-bit versions of Windows.
For a linux build, you will have to compile it using CMake, it has been tested with both GCC and Clang.
