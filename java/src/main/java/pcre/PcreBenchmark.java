package pcre;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

class PcreBenchmark {

  final String trueString_ = "http://test.com?user=mohsen&server=test&param1=1&param2=2&param3=3&param4=4&param5=5&param6=6&param7=7&param8=8&param9=9&param10=10&param11=11&param12=12&param13=13&param14=14&param15=15,last=1";
  final String falseString_ = "http://test.com?user=mohsen&server=test&param1=1&param2=2&param3=3&param4=4&param5=5&param6=6&param7=7&param8=8&param9=9&param10=10&param11=11&param12=12&param13=13&param14=14&param15=15,last=2";
  final String regex = "http:\\/\\/.*?((param\\d+=\\d+&){1,10}).*?param15=15.*?(last=1)";
  final int testCount_=100000;


  private void RunTest(final String str,final String comment){
    int matchCount=0;
    long start = System.currentTimeMillis();
    final Pattern pattern = Pattern.compile(regex, Pattern.MULTILINE);
    for(int i=0;i<testCount_;i++){
      final Matcher matcher = pattern.matcher(str);  
      if(matcher.find()){
          matchCount++;
      }
    }
    long end = System.currentTimeMillis();
    System.out.printf("T : %d M : %d D : %d %s %n", testCount_,matchCount,end-start,comment);
  }


  public void Run(){
    RunTest(trueString_,"JAVA:MATCH");
    RunTest(falseString_,"JAVA:UNMATCH");
  }
}
