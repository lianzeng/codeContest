#ifndef _PARSE_TEST_DATA_HPP
#define _PARSE_TEST_DATA_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <utility>

using std::string;
using BooksList = std::vector< std::vector<int> >;
using std::ifstream;

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

	BooksList getTestCases() const
	{
		return testCases;
	}

private:
	std::vector<int> convertToInt(const string& str)
	{
		auto c2i = [](char c) {return c - '0'; };
		std::vector<int> books(5, 0);//max 5 type books
		for (auto& c : str)
			books[c2i(c) - 1]++;
		return books;
	}

	void storeTestCase(const int num, ifstream& ifs)
	{
		for (int i = 0; i < num; i++)
		{
			string str;
			std::getline(ifs, str);

			auto nums = convertToInt(str);
			
			testCases.push_back(nums);
		}

		assert(testCases.size() == num);
	}

	void showTestCases()
	{
		std::cout << "\n" << "Total " << testCases.size() << " TestCase : \n\n";

		for (auto& nums : testCases)
		{
			std::cout << "\n";
			for (auto& book : nums)
				std::cout << book << " , ";
		}

		std::cout << "\n";
	}

	int getFirstLine(ifstream& ifs)
	{
		string str;
		std::getline(ifs, str);
		return std::stoi(str);
	}
private:
	BooksList testCases;
};

#endif