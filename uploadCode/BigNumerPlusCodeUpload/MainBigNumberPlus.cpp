// BigNumberPlus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include "ParseTestData.hpp"
#include "FileTestResult.hpp"
#include "BigNumberPlus.hpp"


int main()
{
	
	//string num1 = "-100000";
	//string num2 = "99990";
	//std::cout <<"\n (" << num1 << ") + (" << num2 <<") = " << ret << "\n";

	ParseTestData parseTestData("input.txt");//remeber to add testCasesNumber in first line before run.
	auto testCases = parseTestData.getTestCases();
	std::vector<std::string> result;

	for (auto& tc : testCases)
	{
		BigNumberPlus bigNumberPlus(tc.first, tc.second);
		result.push_back( bigNumberPlus.output());
	}

	FileTestResult saveResultToFile(result, "output.txt");
	
	std::cout << "remeber to add testCasesNumber in first line before run. \n";
	std::cout << "\n BigNumberPlus ok \n";
    return 0;
}

