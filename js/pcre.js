#!/usr/bin/env node
'use strict';
var trueString = `http://test.com?user=mohsen&server=test&param1=1&param2=2&param3=3&param4=4&param5=5&param6=6&param7=7&param8=8&param9=9&param10=10&param11=11&param12=12&param13=13&param14=14&param15=15,last=1`
var falseString = `http://test.com?user=mohsen&server=test&param1=1&param2=2&param3=3&param4=4&param5=5&param6=6&param7=7&param8=8&param9=9&param10=10&param11=11&param12=12&param13=13&param14=14&param15=15,last=2`
var totalCount = 100000

function match(test_str){
  let count=0
  for(let i=0;i<totalCount;i++){
    let regexObj =/http:\/\/.*?((param\d+=\d+&){1,10}).*?param15=15.*?(last=1)/m;
    if(regexObj.test(test_str)){
      count++;
    }
  }
  return count;
}

function run(match_func,param,info){
  let start = new Date();
    let matchCount=match_func(param);
  let end=new Date();
  console.log("T : %d M : %d D : %d %s",totalCount,matchCount,end.getTime()-start.getTime(),info)
}

run(match,trueString,"NODEJS:MATCH")
run(match,falseString,"NODEJS:UNMATCH")
