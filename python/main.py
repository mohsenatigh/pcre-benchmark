import re
import time
import math

trueString = "http://test.com?user=mohsen&server=test&param1=1&param2=2&param3=3&param4=4&param5=5&param6=6&param7=7&param8=8&param9=9&param10=10&param11=11&param12=12&param13=13&param14=14&param15=15,last=1"
falseString = "http://test.com?user=mohsen&server=test&param1=1&param2=2&param3=3&param4=4&param5=5&param6=6&param7=7&param8=8&param9=9&param10=10&param11=11&param12=12&param13=13&param14=14&param15=15,last=2" 
totalCount = 100000

def match(test_str):
  count=0
  regex = r"http:\/\/.*?((param\d+=\d+&){1,10}).*?param15=15.*?(last=1)"
  pcre_out=re.compile(regex,re.MULTILINE)
  for _ in range(totalCount):
    if pcre_out.match(test_str):
        count+=1
  return count
  
def test(fn,param,info):
  start=time.time_ns()
  count =fn(param)
  end=time.time_ns()
  elapsed=math.trunc((end-start)/1000000)
  print("T : {} M : {} D : {} {}".format(totalCount,count,elapsed,info))


def main():
  test(match,trueString,"PYTHON:MATCH")
  test(match,falseString,"PYTHON:UNMATCH")


if __name__ == "__main__":
    main()
