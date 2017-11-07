// LongMenHotel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "SearchPath.hpp"
#include <cassert>
#include "ParseTestData.hpp"
#include "FileTestResult.hpp"
#include "Dijkstra.hpp"
#include "GreedyBFS.hpp"

//#define DFS

int main()
{		
#ifdef DFS
	ParseTestData input("input.txt");
	auto testCases = input.getTestCases();

	std::vector<string> result;

	for (auto& oneCase : testCases)
	{
		Solution so(oneCase.second, oneCase.first);
		if (so.searchPath())
			result.push_back("YES");
		    so.printPath();
		else
			result.push_back("NO");
		 
	}

	FileTestResult saveResultToFile(result, "output1.txt");

	
#elif defined(DIJKSTRA)

	ParseTestData input("input.txt");
	auto testCases = input.getTestCases();

	std::vector<string> result;

	for (auto& oneCase : testCases)
	{
		Dijkstra dijkstra(oneCase.second, oneCase.first);
		if (dijkstra.canReachWithRequiredDays())
		{
			result.push_back("YES");
			//dijkstra.printPath();
		}
		else
			result.push_back("NO");
		
	}

	FileTestResult saveResultToFile(result, "output2.txt");

#else

	ParseTestData input("input.txt");
	auto testCases = input.getTestCases();

	std::vector<string> result;

	for (auto& oneCase : testCases)
	{
		GreedyBFS bfs(oneCase.second, oneCase.first);
		if (bfs.canReachWithRequiredDays())
		{
			result.push_back("YES");
			//bfs.printPath();
		}
		else
			result.push_back("NO");

	}

#endif

    return 0;
}

