
#ifndef SEARCH_PATH_INCLUDED
#define SEARCH_PATH_INCLUDED

#include <utility>
#include <vector>
#include <unordered_set>
#include "Definition.hpp"
#include <cassert>

using Point = std::pair<int, int>; //{row, col}
using PVector = std::vector<Point>;

#define HASH_BUCKET_SIZE 400


enum EDirection
{
	EDirection_ABOVE = 0,
	EDirection_BELOW,
	EDirection_LEFT,
	EDirection_RIGHT
};

class Solution
{
public:


	Solution(const GraphMatrix& imatrix, const Paramerters& iParas) :
		mPath(),failRecords(HASH_BUCKET_SIZE, hash), mStart(InvalidPoint),mEnd(InvalidPoint), mMatrix(imatrix), mParas(iParas)
	{

		for (int i = 0; i < mParas.rowNum; i++)
		{
			assert(mMatrix[i].size() == mParas.colNum);

			for (int j = 0; j < mParas.colNum; j++ )
			{
				if (mMatrix[i][j] == 'L') { setEndPoint({i, j}); }
				else if (mMatrix[i][j] == 'Z') { setStartPoint({i, j}); }				
			}
		}


		cacheHit = 0;
		assert(mMatrix.size() == mParas.rowNum);
		assert(mStart != InvalidPoint);
		assert(mEnd != InvalidPoint);
		assert(mStart != mEnd);
	}

	bool searchPath() //API
	{		
		getPath(mEnd);

		return checkResult();
	}	

	bool printPath();

private:

	bool checkResult()
	{
		if (0 == mPath.size())
		{
			//std::cout << std::endl << "Error: No path found ! \n";
			return false;
		}
		else if (mPath.size() > (mParas.maxDays + 1))
		{
			//std::cout << std::endl << "Error: path found, but exceed neededDays !" << " costDays: " << mPath.size() - 1 << std::endl;
			return false;
		}
		else
		{
			//std::cout << std::endl << "Success !  " << " costDays: " << mPath.size() - 1 << std::endl;//path.size() = cost + 1;
			return true;
		}
	}

	bool getPath(Point curr);

	void setStartPoint(Point p)
	{
		mStart = p;
	}

	void setEndPoint(Point p)
	{ 
		mEnd = p;  
	}

	bool reachStartPoint(Point p) const
	{
		return p == mStart;
	}

	bool reachFromNeighbor(Point p, EDirection from)
	{
		Point adjacent;
		switch (from)
		{
			case EDirection_ABOVE: adjacent = { p.first - 1, p.second }; break;
			case EDirection_BELOW: adjacent = {p.first + 1, p.second }; break;
			case EDirection_LEFT:  adjacent = { p.first, p.second - 1 }; break;
			case EDirection_RIGHT: adjacent = { p.first, p.second + 1 }; break;
			default:assert(0); break;
		}

		if(isValid(adjacent))
			return getPath(adjacent);
		else
			return false;

	}

	bool isValid(Point p) const
	{
		return inRange(p) && !isObstacle(p) && !inHistoryPath(p); //shoud not go back to it's history path !
	}

	bool inRange(Point p) const
	{
		return (0 <= p.first && p.first < mParas.rowNum) &&
			   (0 <= p.second && p.second < mParas.colNum);
	}

	bool isObstacle(Point p) const
	{		
		return (mMatrix[p.first][p.second] == '*');
			   
	}

	bool inHistoryPath(Point p) const
	{
		for (auto& h : mPath)
			if (h == p) return true;
		return false;
	}
	

	static size_t hash(Point key)
	{		
		return key.first * key.second;
	}

	bool alreadyFailed(Point p)
	{
		return failRecords.find(p) != failRecords.end();
	}

	bool exceedTime()
	{
		return  mPath.size() >= (mParas.maxDays + 1);// use > or >=		
	}

	using HashSet = std::unordered_set<Point, decltype(hash)* >;

	void maskPosition(PVector path, std::vector<std::vector<char> >& matrix, char c);//debug method,to remove

private:
	PVector mPath;
	HashSet failRecords;
	size_t cacheHit;


	Point mStart;
	Point mEnd;
	const GraphMatrix mMatrix;
	const Paramerters mParas;
	static const Point InvalidPoint;
};

#endif
