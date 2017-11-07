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

#define DIJKSTRA

int main()
{		

#ifdef DFS

	ParseTestData input("input.txt");
	auto testCases = input.getTestCases();

	std::vector<string> result;

	for (auto& oneCase : testCases)
	{
		DFSearch dfs(oneCase.second, oneCase.first);
		if (dfs.searchPath())
		{
			result.push_back("YES");
			dfs.printPath();
		}
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
			dijkstra.printPath();
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
			bfs.printPath();
		}
		else
			result.push_back("NO");

	}

	FileTestResult saveResultToFile(result, "output2.txt");
#endif

    return 0;
}

