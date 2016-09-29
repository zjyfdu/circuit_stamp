///
/// @file   util.h
/// @author Yinghai
/// @date   Fri Sep 12 13:55:42 2008
/// 
/// @brief  Header of the utility funtions
/// 
/// 
///

#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <cctype>
#include <cstdlib>

using std::string;


/// \brief This function breaks the string into tokens with the given delimiters.
/// 
/// \param str the long string to be break
/// \param de delimiters
/// @return first token extracted
///
/// This function is a convenient C++ verion of \e strtok. Given the delimiters,
/// it will extract the first token from the string. 
/// For example, \e tokenizer("Hello+$World","+$") will return the string \e Hello.
/// You have run it several times in order to extract more tokens. If no more token
/// can be extracted, it will return an empty string. Using this, you can decide whether
/// a line is finished. 
/// In boost library, there is a more powerful tokening tool. If you'rer interested,
/// please see to the doc of boost.
string tokenizer(string& str, const string& de);


/// \brief this function converts string to upper case
///
/// @param token string to be converted
///
void capitalize(string &token);

/// \brief This function converts string to a double considering the units
///
/// In SPICE, units are used. So \e 9ns should equal to \e 1e-9. This function
/// just help you take care of such things. 
double to_double(string &); 


#endif
