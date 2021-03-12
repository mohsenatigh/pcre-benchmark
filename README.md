# pcre-benchmark
simple program for comparing the performance of REGEX implementations in different programming languages

## Test criteria 
Refrence pattern is `http:\/\/.*?((param\d+=\d+&){1,10}).*?param15=15.*?(last=1)`

Loop count is 100000

## Performance comparison when the input text matched with the reference pattern
![alt text](https://github.com/mohsenatigh/pcre-benchmark/blob/main/matched.png)

## Performance comparison when the input text not matched with the reference pattern
![alt text](https://github.com/mohsenatigh/pcre-benchmark/blob/main/not_matched.png)

## PCRE-jit vs Intel Hyperscan
![alt text](https://github.com/mohsenatigh/pcre-benchmark/blob/main/pcrejitvshscan.png)
