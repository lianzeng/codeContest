// LongMenHotel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "SearchPath.hpp"
#include <cassert>
#include "ParseTestData.hpp"
#include "FileTestResult.hpp"

int main()
{	
	


	ParseTestData input("input.txt");
	auto testCases = input.getTestCases();

	std::vector<string> result;

	for (auto& oneCase : testCases)
	{
		Solution so(oneCase.second, oneCase.first);
		if (so.searchPath())
			result.push_back("YES");
		else
			result.push_back("NO");
		//so.printPath();	
	}

	FileTestResult saveResultToFile(result, "output.txt");

	//std::cout << "\n LongMenHotel ok \n";
    return 0;
}

