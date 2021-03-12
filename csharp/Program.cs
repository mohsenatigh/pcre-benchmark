using System;
using System.Text.RegularExpressions;
using System.Diagnostics;
namespace pcretest
{
  class PcreTest
    {
        private const String trueString_ = "http://test.com?user=mohsen&server=test&param1=1&param2=2&param3=3&param4=4&param5=5&param6=6&param7=7&param8=8&param9=9&param10=10&param11=11&param12=12&param13=13&param14=14&param15=15,last=1";
        private const String falseString_ = "http://test.com?user=mohsen&server=test&param1=1&param2=2&param3=3&param4=4&param5=5&param6=6&param7=7&param8=8&param9=9&param10=10&param11=11&param12=12&param13=13&param14=14&param15=15,last=2";
        private const String regex = "http:\\/\\/.*?((param\\d+=\\d+&){1,10}).*?param15=15.*?(last=1)";
        private const int testCount_ = 100000;

        private void RunTest(in String str,in String comment){
            RegexOptions options = RegexOptions.Multiline | RegexOptions.Compiled;
            int matchCount=0;
            Stopwatch watch = Stopwatch.StartNew();
            for(int i=0;i<testCount_;i++){
                Match match=Regex.Match(str,regex,options);
                if(match.Success){
                  matchCount++;
                }
            }
            watch.Stop();
            Console.WriteLine("T : {0} M : {1} D : {2} {3}",testCount_,matchCount,watch.ElapsedMilliseconds,comment);
        }
        public void Run(){
            RunTest(trueString_,"C#:MATCH");
            RunTest(falseString_,"C#:UNMATCH");
        } 
    }

  class Program
  {
    static void Main(string[] args)
    {
        PcreTest test=new PcreTest();
        test.Run();
    }
  }
}
