#!/bin/sh
#Oniguruma, v6.1.3
#RE2
#
./cpp/__build/test.bin
./golang/main
python3 ./python/main.py
./rust/target/release/rust
java -jar ./java/build/libs/java.jar
./csharp/bin/Release/net5.0/pcretest
./js/pcre.js
