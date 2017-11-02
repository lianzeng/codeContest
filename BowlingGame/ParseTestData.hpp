#ifndef _PARSE_TEST_DATA_HPP
#define _PARSE_TEST_DATA_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

using std::string;
using SVector = std::vector<string>;
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

		showTestCases();
	}

	SVector getTestCases() const
	{
		return testCases;
	}

private:
	void storeTestCase(const int num, ifstream& ifs)
	{
		for (int i = 0; i < num; i++)
		{
			string str;
			std::getline(ifs, str);
			testCases.push_back(str);
		}

		assert(testCases.size() == num);
	}

	void showTestCases()
	{
		std::cout << "\n" << "Total " << testCases.size() << " TestCase : \n\n";

		for (auto& str : testCases)
			std::cout << str << "\n";

		std::cout << "\n";
	}

	int getFirstLine(ifstream& ifs)
	{
		string str;
		std::getline(ifs, str);
		return std::stoi(str);
	}
private:
	SVector testCases;
};

#endif