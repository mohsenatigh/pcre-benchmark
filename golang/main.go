package main

import (
	"fmt"
	"regexp"
	"time"
)

const totalCount = 100000
const trueString = `http://test.com?user=mohsen&server=test&param1=1&param2=2&param3=3&param4=4&param5=5&param6=6&param7=7&param8=8&param9=9&param10=10&param11=11&param12=12&param13=13&param14=14&param15=15,last=1`
const falseString = `http://test.com?user=mohsen&server=test&param1=1&param2=2&param3=3&param4=4&param5=5&param6=6&param7=7&param8=8&param9=9&param10=10&param11=11&param12=12&param13=13&param14=14&param15=15,last=2`

func matchPattern(str string) uint32 {
	matchCount := uint32(0)
	var re = regexp.MustCompile(`(?m)http:\/\/.*?((param\d+=\d+&){1,10}).*?param15=15.*?(last=1)`)
	for i := 0; i < totalCount; i++ {
		if re.Match([]byte(str)) {
			matchCount++
		}
	}
	return matchCount
}

func main() {

	runFunc := func(fn func(string) uint32, param string, info string) {
		start := time.Now()
		matchCount := fn(param)
		end := time.Now()
		elapsed := end.Sub(start)
		fmt.Printf("T : %v M : %v D : %d %s\n", totalCount, matchCount, elapsed.Milliseconds(), info)
	}

	runFunc(matchPattern, trueString, "GOLANG:MATCH")
	runFunc(matchPattern, falseString, "GOLANG:UNMATCH")

}
