#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <set>
#include <string>
#include <cctype>


using namespace std;
std::string& convToLower(std::string &src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{

set<string> s1;
trimpunct(rawWords);
trim(rawWords);
convToLower(rawWords);
string temp;
stringstream ss1(rawWords);

while(ss1 >> temp){
    trim(temp);
    if(temp.size() > 1){
        s1.insert(temp);
    }
}

return s1;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(),
            std::find_if(s.begin(),
                         s.end(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
            std::find_if(s.rbegin(),
                         s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
            s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

std::string &trimpunct(std::string &s) {
    for (int i = 0; i < s.size(); i++) {
        if (ispunct(s[i])) {
            s[i] = ' ';
        }
    }
    return s;
}


