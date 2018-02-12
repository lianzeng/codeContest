#ifndef _PARSE_TEST_DATA_HPP
#define _PARSE_TEST_DATA_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <utility>
#include <sstream>
#include "Definition.hpp"

class ParseTestData
{
public:
	ParseTestData(string filePath)
	{
		ifstream inputFile(filePath);

		int numOfTestCases = getFirstLine(inputFile);		

		storeTestCase(numOfTestCases, inputFile);

		inputFile.close();

		//showTestCases();
	}

	CaseList getTestCases() const
	{
		return testCases;
	}

private:

	void storeTestCase(const int num, ifstream& ifs)
	{
		for (int i = 0; i < num; i++)
		{
			auto tcase = parseOneCase(ifs);

			testCases.push_back(tcase);
		}

		assert(testCases.size() == num);
	}
	CaseInfo parseOneCase(ifstream& ifs)
	{		
		auto params = parseParams(ifs);
		
	        string str;
		std::getline(ifs, str);
		auto headCountList = parseOneRow(str, params.groupNum);

		assert(headCountList.size() == params.groupNum);							
		return {params, headCountList };//oneCase
	}

	HeadCountList parseOneRow(const string& str, const int groupNum)
	{
		HeadCountList headCountList;
		std::stringstream strstream(str);
		for (int i = 0; i < groupNum; i++)
		{
			int headCount;
			strstream >> headCount;
			headCountList.push_back(headCount);
		}
		return headCountList;
	}

	Paramerters parseParams(ifstream& ifs)
	{	
		Paramerters ret;
		string str;
		std::getline(ifs, str);
		std::stringstream strstream(str);
		strstream >> ret.groupNum >> ret.candyNumPerBox;//split with space
		assert(1 <= ret.groupNum && ret.groupNum <= 100);
		assert(2 <= ret.candyNumPerBox && ret.candyNumPerBox <= 4);
		return ret;
	}



	void showTestCases()
	{
		std::cout << "\n"<< testCases.size() <<"\n";

		for (auto& oneCase : testCases)
		{
			std::cout << oneCase.first.groupNum << " " << oneCase.first.candyNumPerBox <<"\n";
			for (auto& num : oneCase.second)
			{				
				std::cout << num <<" ";
			}

			std::cout << "\n";
		}

		std::cout << "\n\n";
	}

	int getFirstLine(ifstream& ifs)
	{
		string str;
		std::getline(ifs, str);
		return std::stoi(str);
	}
private:
	CaseList testCases;
};

#endif
