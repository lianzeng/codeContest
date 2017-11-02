// BowlingGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include "ParseTestData.hpp"
#include "BowlingBall.hpp"
#include "FileTestResult.hpp"


int main()
{
	ParseTestData parseTestData("input.txt");
	auto testCases = parseTestData.getTestCases();

	BowlingBall bowBall;
	std::vector<int> result;

	for (auto& input : testCases)
	{
		auto score = bowBall.getScore(input);
		result.push_back(score);		
	}
	
	assert(result.size() == testCases.size());

	FileTestResult saveResultToFile(result, "BowlingGame_Result.txt");

	std::cout << "\n Bowling Game\n" << std::endl;
    return 0;
}

