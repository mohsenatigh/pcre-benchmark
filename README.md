# pcre-benchmark
simple program for comparing the performance of REGEX implementations in different programming languages

Please note that this test compares the REGX implementation in different programming languages and is not an indication of any programming languages' performance. For example, node-js excellent performance is related to the performance of the Google V8 engine, which has been implemented using c++, but the c++ std::regx is the worst implementation among this list. Furthermore, Other implementations are also available for each of these programming languages, but I only used the default implementation. For example, for GOLANG, you can use PCRE instead of it,s default REGX matcher.

## Test criteria

Refrence pattern is `http:\/\/.*?((param\d+=\d+&){1,10}).*?param15=15.*?(last=1)`

Loop count is 100000

## Performance comparison when the input text matched with the reference pattern
![alt text](https://github.com/mohsenatigh/pcre-benchmark/blob/main/matched.png)

## Performance comparison when the input text not matched with the reference pattern
![alt text](https://github.com/mohsenatigh/pcre-benchmark/blob/main/not_matched.png)

## PCRE-jit vs Intel Hyperscan
![alt text](https://github.com/mohsenatigh/pcre-benchmark/blob/main/pcrejitvshscan.png)
