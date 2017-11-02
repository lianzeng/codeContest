// CandyGift.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "FileTestResult.hpp"
#include "ParseTestData.hpp"
#include "CandyDispatch.hpp"


int main()
{
	ParseTestData input("input.txt");
	auto testCases = input.getTestCases();

	std::vector<int> result;

	for (auto& oneCase : testCases)
	{
		CandyDispatch dispatch(oneCase.first, oneCase.second);
		result.push_back(dispatch.getHappyGroupNum());
		std::cout << "\n" << dispatch.getHappyGroupNum() << "\n\n";
	}


	
	FileTestResult saveResultToFile(result, "output.txt");
	std::cout << "Candy ok." << "\n";
    return 0;
}

