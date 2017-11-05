#include "stdafx.h"
#include "Dijkstra.hpp"

const Point Dijkstra::InvalidPoint = { -1,-1 }; 


bool Dijkstra::printPath()
{
	mPath = getPath();

	if (0 == mPath.size())
	{
		std::cout << std::endl << "Error: No path found ! \n";
		return false;
	}
	else if (mPath.size() > (requiredDays + 1))
	{
		std::cout << std::endl << "Error: path found, but exceed neededDays !" << " costDays: " << mPath.size() - 1 << std::endl;
		return false;
	}
	else
	{
		std::cout << std::endl << "Success !  " << " costDays: " << mPath.size() - 1 << std::endl;//path.size() = cost + 1;
	}

	GraphMatrix matrix = mMatrix;
	maskPosition(mPath, matrix, '$');


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

PVector Dijkstra::getPath()
{
	PVector path;
	if (canReachWithRequiredDays())
	{
		path.push_back(mEnd);
		auto v = mEnd;
		while ((v = preMap[v]) != mStart)
		{
			path.push_back(v);
		}
		path.push_back(mStart);
		assert(0 < path.size() && path.size() <= (requiredDays + 1));
	}

	return path;
}

void Dijkstra::maskPosition(std::vector<Point> path, GraphMatrix& matrix, char c)
{
	for (auto& p : path)
		matrix[p.first][p.second] = c;

	matrix[mEnd.first][mEnd.second] = 'L';
	matrix[mStart.first][mStart.second] = 'Z';
}