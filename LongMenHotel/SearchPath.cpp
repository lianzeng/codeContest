
#include "stdafx.h"
#include "SearchPath.hpp"
#include <iostream>

const Point Solution::InvalidPoint = {-1,-1};

bool Solution::getPath(Point curr)
{
	if (exceedTime() || alreadyFailed(curr))
	{
		cacheHit++;
		return false;
	}

	mPath.push_back(curr);

	if (reachStartPoint(curr)) return true;	

	if (reachFromNeighbor(curr, EDirection_ABOVE)) return true; 	

	if (reachFromNeighbor(curr, EDirection_BELOW)) return true;
	
	if (reachFromNeighbor(curr, EDirection_RIGHT)) return true;	

	if (reachFromNeighbor(curr, EDirection_LEFT))  return true;

	mPath.pop_back();//revert

	failRecords.insert(curr);

	return false;
}

bool Solution::printPath()
{
	if (0 == mPath.size())
	{
		std::cout << std::endl << "Error: No path found ! \n";
		return false;
	}
	else if (mPath.size() > (mParas.maxDays + 1))
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

void Solution::maskPosition(std::vector<Point> path,  GraphMatrix& matrix, char c)
{
	for (auto& p : path)
		matrix[p.first][p.second] = c;

	matrix[mEnd.first][mEnd.second] = 'L';
	matrix[mStart.first][mStart.second] = 'Z';
}