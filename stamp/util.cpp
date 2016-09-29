///
/// @file   util.cpp
/// @author Yinghai
/// @date   Fri Sep 12 14:05:16 2008
/// 
/// @brief  Implementation of the utility functions
/// 
/// 
///

#include "util.h"

string tokenizer(string& line, const string& delims)
{
	string toke;

	// find the beginning position of first token
	string::size_type idx_begin = line.find_first_not_of(delims);

	if (idx_begin != string::npos) {
		string::size_type idx_end = line.find_first_of(delims, idx_begin);

		// last word
		if (idx_end == string::npos) {
			idx_end = line.length();
		}

		// extract the first token and erase it from the input string
		toke = line.substr(idx_begin, idx_end - idx_begin);
		capitalize(toke);
		line.erase(0, idx_end - 0);
	} // end if

	return toke;
}

void capitalize(string &token) {
  for (size_t i = 0; i< token.length(); ++i) {
    token[i] = toupper(token[i]);
  }
}


double to_double(string &str) {
	string delims = "0123456789+-E.";
	string::size_type fig_end = str.find_first_not_of(delims);
	if (fig_end == string::npos) {
		return atof(str.c_str());	
	}
	else {
		double fig = atof(str.substr(0, fig_end).c_str());
		double scale = 1.0;
		string unit = str.substr(fig_end, str.length() - fig_end);
		if (unit == "P") {
			scale = 1e-12;	
		}
		else if (unit == "N" || unit == "NS") {
			scale = 1e-9;	
		}
		else if (unit == "U") {
			scale = 1e-6;	
		}
		else if (unit == "M") {
			scale = 1e-3;	
		}
		else if (unit == "K") {
			scale = 1e3;
		}
		else if (unit == "MEG"){
			scale = 1e6;     
		} 
		// TODO 
		else {}
		return fig*scale;
	}	

}
