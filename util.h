#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */

 // The set intersection function takes advantage of the alphabetical nature
 // of the > operator as it pertains to the relevant T type being used. In this
 // case (since T is a string), we can modify the iterator based on which set has 
 // the current "highest" value. This way, we do not have to operater in O(n^2) time.

template <typename T>
std::set<T> setIntersection(const std::set<T>& s1, const std::set<T>& s2)
{

std::set<T> result;
typename std::set<T>::iterator it1 = s1.begin();
typename std::set<T>::iterator it2 = s2.begin();

while(it1!=s1.end() && it2!=s2.end()){
    if(*it1 > *it2){
        it2++;
    }
    else if(*it2 > *it1){
        it1++;
    }
    else{
        result.insert(*it1);
        it1++;
        it2++;
    }
}

return result;

}

//The union is simply appending the two sets together. 
//Since sets will not allow duplicates, this is done trivially.
template <typename T>
std::set<T> setUnion(const std::set<T>& s1, const std::set<T>& s2)
{
    std::set<T> result;

    for(typename std::set<T>::iterator it = s1.begin(); it!=s1.end(); it++ ) {
        result.insert(*it);
    }

    for(typename std::set<T>::iterator it = s2.begin(); it!=s2.end(); it++ ) {
        result.insert(*it);
    }

    return result;


}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string& convToLower(std::string &src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;

std::string &trimpunct(std::string &s) ;
#endif
