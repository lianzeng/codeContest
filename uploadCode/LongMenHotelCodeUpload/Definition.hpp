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
	int colNum;
	int rowNum;
	int maxDays;
};


using std::string;

using GraphMatrix = std::vector<std::vector<char>>;

using CaseInfo = std::pair<Paramerters, GraphMatrix>;

using CaseList = std::vector< CaseInfo >;

using std::ifstream;



#endif
