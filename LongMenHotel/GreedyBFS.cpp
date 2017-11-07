
#include "stdafx.h"
#include "GreedyBFS.hpp"

const Point GreedyBFS::InvalidPoint = { -1,-1 };


bool GreedyBFS::printPath()
{
	auto path = getPath();

	if (0 == path.size())
	{
		std::cout << std::endl << "Error: No path found ! \n";
		return false;
	}
	else if (path.size() > (requiredDays + 1))
	{
		std::cout << std::endl << "Error: path found, but exceed neededDays !" << " costDays: " << path.size() - 1 << std::endl;
		return false;
	}
	else
	{
		std::cout << std::endl << "Success !  " << " costDays: " << path.size() - 1 << std::endl;//path.size() = cost + 1;
	}

	GraphMatrix matrix = mMatrix;
	maskPosition(path, matrix, '$');


	for (auto& row : matrix)
	{
		std::cout << std::endl;
		for (auto& c : row)
		{
			std::cout << c << ' ';
		}
	}
	std::cout << std::endl << std::endl;

	return true;
}

PVector GreedyBFS::getPath()
{
	PVector path;
	if (canReachWithRequiredDays())
	{		
		auto v = mEnd;
		for (; fatherMap.find(v) != fatherMap.end() && v != mStart; v = fatherMap[v])
		{
			path.push_back(v);
		}
		path.push_back(mStart);
		assert(0 < path.size() && path.size() <= (requiredDays + 1));
	}

	return path;
}

void GreedyBFS::maskPosition(std::vector<Point> path, GraphMatrix& matrix, char c)
{
	for (auto& p : path)
		matrix[p.first][p.second] = c;

	matrix[mEnd.first][mEnd.second] = 'L';
	matrix[mStart.first][mStart.second] = 'Z';
}