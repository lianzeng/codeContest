#ifndef _DEFINITION_HPP
#define _DEFINITION_HPP


#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <utility>
#include <sstream>


struct Paramerters
{
	int groupNum;
	int candyNumPerBox;	
};


using std::string;

using HeadCountList = std::vector<int>;//each element is a group headCount

using CaseInfo = std::pair<Paramerters, HeadCountList>;

using CaseList = std::vector< CaseInfo >;

using std::ifstream;


#endif
