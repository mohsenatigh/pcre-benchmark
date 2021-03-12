#include <boost/regex.hpp>
#include <iostream>
#include <mutex>
#include <pcre.h>
#include <regex>
#include <string>
#include <hs/hs.h>
//---------------------------------------------------------------------------------------
const std::string trueString_ =
    "http://"
    "test.com?user=mohsen&server=test&param1=1&param2=2&param3=3&param4=4&"
    "param5=5&param6=6&param7=7&param8=8&param9=9&param10=10&param11=11&"
    "param12=12&param13=13&param14=14&param15=15,last=1";

const std::string falseString_ =
    "http://"
    "test.com?user=mohsen&server=test&param1=1&param2=2&param3=3&param4=4&"
    "param5=5&param6=6&param7=7&param8=8&param9=9&param10=10&param11=11&"
    "param12=12&param13=13&param14=14&param15=15,last=2";

const std::string testPattern_ =
    "http:\\/\\/.*?((param\\d+=\\d+&){1,10}).*?param15=15.*?(last=1)";


const char* testPatternMulti_[] ={
    "http:\\/\\/.*?((param\\d+=\\d+&){1,10}).*?param15=15.*?(last=1)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,2}).*?param15=15.*?(last=3)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,3}).*?param15=15.*?(last=4)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,4}).*?param15=15.*?(last=5)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,5}).*?param15=15.*?(last=6)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,6}).*?param15=15.*?(last=7)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,7}).*?param15=15.*?(last=8)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,8}).*?param15=15.*?(last=9)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,9}).*?param15=15.*?(last=10)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,10}).*?param15=15.*?(last=11)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,11}).*?param15=15.*?(last=12)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,12}).*?param15=15.*?(last=13)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,13}).*?param15=15.*?(last=14)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,14}).*?param15=15.*?(last=15)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,15}).*?param15=15.*?(last=16)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,16}).*?param15=15.*?(last=17)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,17}).*?param15=15.*?(last=18)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,18}).*?param15=15.*?(last=19)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,19}).*?param15=15.*?(last=20)",
    "http:\\/\\/.*?((param\\d+=\\d+&){1,20}).*?param15=15.*?(last=21)"};


uint32_t testCount_ = 100000;
uint32_t mPatternCount_=20;
//---------------------------------------------------------------------------------------
uint32_t testSTDRegx(const std::string &str) {
  uint32_t matchCount = 0;
  const std::regex txt_regex(testPattern_, std::regex_constants::optimize);
  for (int i = 0; i < testCount_; i++) {
    if (std::regex_match(str, txt_regex)) {
      matchCount++;
    }
  }
  return matchCount;
}
//---------------------------------------------------------------------------------------
uint32_t testPCRE(const std::string &str, bool jit, uint32_t matchLimit) {
  uint32_t matchCount = 0;
  const char *pcreErrorStr;
  int pcreErrorOffset;
  int subStrVec[24];
  matchCount = 0;

  auto reCompiled = pcre_compile(testPattern_.c_str(), 0, &pcreErrorStr,
                                 &pcreErrorOffset, NULL);

  pcre_extra *studyInfo = nullptr;

  if (jit) {
    studyInfo = pcre_study(reCompiled, PCRE_STUDY_JIT_COMPILE, &pcreErrorStr);

    if (matchLimit > 0) {
      studyInfo->flags |= PCRE_EXTRA_MATCH_LIMIT;
      studyInfo->match_limit = matchLimit;
    }
  }

  for (int i = 0; i < testCount_; i++) {
    if (pcre_exec(reCompiled, studyInfo, str.c_str(), str.length(), 0, 0,
                  subStrVec, 24) > 0) {
      matchCount++;
    }
  }
  return matchCount;
}
//---------------------------------------------------------------------------------------
uint32_t testPCRENormal(const std::string &str) {
  return testPCRE(str, false, 0);
}
//---------------------------------------------------------------------------------------
uint32_t testPCREJit(const std::string &str) { return testPCRE(str, true, 0); }

//---------------------------------------------------------------------------------------
uint32_t testPCREJitMatchLimit(const std::string &str) {
  return testPCRE(str, true, 110);
}
//---------------------------------------------------------------------------------------
uint32_t testBoostRegx(const std::string &str) {
  uint32_t matchCount=0;
  const boost::regex re(testPattern_);

  for (int i = 0; i < testCount_; i++) {
    if (boost::regex_match(str,re)==true){
      matchCount++;
    }
  }
  return matchCount;
}
//---------------------------------------------------------------------------------------
static int hscanOnMatch(uint32_t id, unsigned long long from,  unsigned long long to, uint32_t flags, void* ctx) {
  uint32_t* val=static_cast<uint32_t*>(ctx);
  (*val)=(*val)+1;
  return 1;
}
//---------------------------------------------------------------------------------------
uint32_t testHScanCount(const std::string &str,uint32_t patternCount) {
  hs_database_t* db=nullptr;
  hs_scratch_t* scratch=nullptr;
  hs_compile_error_t* compileErr;
  uint32_t *flags=new uint32_t[patternCount];
  uint32_t *idList=new uint32_t[patternCount];
  uint32_t matchCount=0;

  for(int i=0;i<patternCount;i++){
    flags[i]=0;
    idList[i]=0;
  }
  
  if(hs_compile_multi(testPatternMulti_,flags,idList,patternCount, HS_MODE_BLOCK, nullptr, &db, &compileErr)!=HS_SUCCESS){
    std::cout << "compile failed  " <<  compileErr->message << "\n";
    return 0;
  }

  if(hs_alloc_scratch(db, &scratch)!=HS_SUCCESS){
    std::cout << "scratch failed \n";
    return 0;
  }


  for (int i = 0; i < testCount_; i++) {
    auto res = hs_scan(db, str.c_str(), str.size(), 0, scratch, hscanOnMatch, &matchCount);
    if (res != HS_SUCCESS && res != HS_SCAN_TERMINATED) {
      std::cout << res << "\n";
    }
  }
  return matchCount;
}
//---------------------------------------------------------------------------------------
uint32_t testHScan(const std::string &str){
  return testHScanCount(str,1);
}
//---------------------------------------------------------------------------------------
uint32_t testHScanMulti(const std::string &str){
  return testHScanCount(str,mPatternCount_);
}
//---------------------------------------------------------------------------------------
void runTest(std::function<uint32_t(const std::string &)> func,
             const std::string &info, const std::string &param) {
  auto start = std::chrono::high_resolution_clock::now();
  auto matchCount = func(param);
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "T : " << testCount_ << " M : " << matchCount
            << " D : " << (end - start).count() / 1000000 << " " << info
            << "\n";
}
//---------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  runTest(testSTDRegx, "CPP:MATCH", trueString_);
  runTest(testPCRENormal, "CPP:PCRE:MATCH", trueString_);
  runTest(testPCREJit, "CPP:PCREJIT:MATCH", trueString_);
  runTest(testPCREJitMatchLimit, "CPP:PCREJIT_MATCHLIMIT:MATCH", trueString_);
  runTest(testBoostRegx, "CPP:BOOST:MATCH", trueString_);
  runTest(testHScan, "CPP:HSCAN:MATCH", trueString_);
  runTest(testHScanMulti, "CPP:HSCAN-20:MATCH", trueString_);

  runTest(testSTDRegx, "CPP:UNMATCH", falseString_);
  runTest(testPCRENormal, "CPP:PCRE:UNMATCH", falseString_);
  runTest(testPCREJit, "CPP:PCREJIT:UNMATCH", falseString_);
  runTest(testPCREJitMatchLimit, "CPP:PCREJIT_MATCHLIMIT:UNMATCH",
          falseString_);
  runTest(testBoostRegx, "CPP:BOOST:UNMATCH", falseString_);
  runTest(testHScan, "CPP:HSCAN:UNMATCH", falseString_);
  runTest(testHScanMulti, "CPP:HSCAN-20:MATCH", falseString_);
}
