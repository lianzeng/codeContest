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
		GraphMatrix oneCase;
		auto params = parseParams(ifs);
		
		for (int i = 0; i < params.rowNum; i++)
		{
			string str;
			std::getline(ifs, str);
			auto oneRow = parseOneRow(str);
			assert(oneRow.size() == params.colNum);
			oneCase.push_back(oneRow);
		}
		assert(oneCase.size() == params.rowNum);
		return {params, oneCase};
	}

	std::vector<char> parseOneRow(const string& str)
	{
		std::vector<char> row;
		for (auto& c : str)
			if (c != ' ')
				row.push_back(c);
		return row;
	}

	Paramerters parseParams(ifstream& ifs)
	{	
		Paramerters ret;
		string str;
		std::getline(ifs, str);
		std::stringstream strstream(str);
		strstream >> ret.colNum >> ret.rowNum >> ret.maxDays;
		assert(ret.colNum > 0 && ret.rowNum > 0 && ret.maxDays > 0);
		return ret;
	}



	void showTestCases()
	{
		std::cout << "\n"<< testCases.size() <<"\n";

		for (auto& oneCase : testCases)
		{
			std::cout << oneCase.first.colNum << " " << oneCase.first.rowNum << " "<<oneCase.first.maxDays <<"\n";
			for (auto& row : oneCase.second)
			{
				for (auto&col: row)
				{
					std::cout << col<<" ";
				}
				std::cout << "\n";
			}

			//std::cout << "\n\n";
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