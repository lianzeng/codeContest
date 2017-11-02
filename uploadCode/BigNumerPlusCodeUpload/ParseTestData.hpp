#ifndef _PARSE_TEST_DATA_HPP
#define _PARSE_TEST_DATA_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <utility>

using std::string;
using SPair = std::pair<string, string>;
using SPVector = std::vector<SPair>;
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

	SPVector getTestCases() const
	{
		return testCases;
	}

private:
	SPair splitNumber(const string& str)
	{
		auto pos = str.find(',');
		auto num1 = str.substr(0, pos);
		auto num2 = str.substr(pos +1 , str.size() - pos -1);
		//std::cout << str << " " << num1 << " " << num2 << "\n";
		return {num1, num2};
	}
	void storeTestCase(const int num, ifstream& ifs)
	{
		for (int i = 0; i < num; i++)
		{
			string str;
			std::getline(ifs, str);

			auto nums = splitNumber(str);
			
			testCases.push_back(nums);
		}

		assert(testCases.size() == num);
	}

	void showTestCases()
	{
		std::cout << "\n" << "Total " << testCases.size() << " TestCase : \n\n";

		for (auto& nums : testCases)
			std::cout << nums.first <<","<< nums.second<< "\n";

		std::cout << "\n";
	}

	int getFirstLine(ifstream& ifs)
	{
		string str;
		std::getline(ifs, str);
		return std::stoi(str);
	}
private:
	SPVector testCases;
};

#endif