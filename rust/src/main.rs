use std::u32;

static  TOTAL_:u32 = 100000;
static  TRUE_STRING_:&str ="http://test.com?user=mohsen&server=test&param1=1&param2=2&param3=3&param4=4&param5=5&param6=6&param7=7&param8=8&param9=9&param10=10&param11=11&param12=12&param13=13&param14=14&param15=15,last=1";
static  FALSE_STRING_:&str ="http://test.com?user=mohsen&server=test&param1=1&param2=2&param3=3&param4=4&param5=5&param6=6&param7=7&param8=8&param9=9&param10=10&param11=11&param12=12&param13=13&param14=14&param15=15,last=2";

fn test_regx(test_string : &str) -> u32 {
    let mut match_count : u32 =0;
    let pattern = regex::Regex::new(r"(?m)http://.*?((param\d+=\d+&){1,10}).*?param15=15.*?(last=1)").unwrap();
    for _x in 0..TOTAL_ { 
        if pattern.is_match(test_string)==true {
            match_count+=1;
        }
    }
    return match_count;
}

fn run_test(f : fn(&str) -> u32,param : &str,info :  &str){
    let start = std::time::Instant::now();
    let match_count=f(param);
    let end = std::time::Instant::now();
    let result = end-start;
    println!("T : {} M : {} D : {} {}",TOTAL_,match_count,result.as_millis(),info);
}

fn main() {
    run_test(test_regx,TRUE_STRING_,"RUST:MATCH");
    run_test(test_regx,FALSE_STRING_,"RUST:UNMATCH");
}
