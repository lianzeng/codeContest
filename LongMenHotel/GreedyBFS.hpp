#ifndef _GREEDY_BFS_HPP
#define _GREEDY_BFS_HPP

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_set>
#include "Definition.hpp"
#include <cassert>
#include <climits>
#include <map>


using Point = std::pair<int, int>; //{row, col}
using PVector = std::vector<Point>;

using Distance = int;
using WeightVetex = std::pair<Point, Distance>;//Distance = currentVetex to startPoint.
using VetexSet = std::vector<WeightVetex>;
using FatherMap = std::map<Point,Point>;



class PriorityQueue //here can't use STL::Priority_queue, as here need uniquepush.
{
	using ElementType = WeightVetex;
public:
	PriorityQueue(FatherMap& imap):fatherMap(imap){}

	void push(const ElementType& element, Point father)
	{
		for (size_t i = 0; i < queue.size(); i++)
		{
			if (queue[i].first == element.first)//update to the shortest distance if already exist in queue.
			{
				if (queue[i].second > element.second)
				{
					queue[i].second = element.second;
					updateFatherMap(element.first, father);
				}
				return;
			}
		}

		queue.push_back(element);//it's a new element.
		updateFatherMap(element.first, father);
	}

	ElementType pop()//pop the shortest candidate from queue.
	{
		assert(!queue.empty());		
		
		auto min = queue.begin();
		
		for (auto iter = queue.begin();iter != queue.end(); iter++)
		{
			if ((*iter).second < (*min).second)
			{
				min = iter;				
			}
		}

		auto minElement = *min;
		queue.erase(min);
		return minElement;
	}

	bool empty() const { return queue.empty(); }

	void updateFatherMap(const Point curr, Point father)
	{
		fatherMap[curr] = father;
	}

private:
	VetexSet queue;
	FatherMap& fatherMap;
};

class GreedyBFS
{
public:

	GreedyBFS(const GraphMatrix& imatrix, const Paramerters& iParas):
		mMatrix(imatrix),requiredDays(iParas.maxDays), mStart(InvalidPoint), mEnd(InvalidPoint), fatherMap()
	{
		setStartEndPoint(mMatrix);
	}

	bool canReachWithRequiredDays()
	{
		auto minDistance = calculateShortestPath(mStart, mEnd);

		if (minDistance == INFINITE) std::cout << "\n start can't reach End , they are disconnected. \n";
		else std::cout << "\n minDistance is " << minDistance << " ,requiredDays is " << requiredDays << "  \n";

		return minDistance <= requiredDays;
	}

	bool printPath();

private:
	int calculateShortestPath(const Point from, const Point target)//BFS classical.
	{
		PVector visited;
		PriorityQueue queue(fatherMap); //use priority_queue instead of FIFO_queue.
		queue.push({ from , 0}, InvalidPoint);//from has no father, so set it's father as InvalidPoint.

		while (!queue.empty())
		{
			auto ele = queue.pop();

			if (ele.first == target) return ele.second;

			visited.push_back(ele.first);

			auto adjacents = getNeighborVetex(ele.first);
			for (auto& vetex : adjacents)
			{
				if (!inSet(visited, vetex))
				{
					auto dist = ele.second + distance(ele.first, vetex);
					queue.push({vetex, dist}, ele.first);
				}
			}
		}

		return INFINITE;
	}

	void setStartEndPoint(const GraphMatrix& matrix)
	{		
		for (size_t r = 0; r < matrix.size(); r++)
		{
			for (size_t c = 0; c < matrix[r].size(); c++)
			{
				if (matrix[r][c] == START)    { setStartPoint({r,c}); }
				else if (matrix[r][c] == END) { setEndPoint({r, c} ); }
			}
		}
		
	}
	void setStartPoint(Point p)
	{
		mStart = p;
	}

	void setEndPoint(Point p)
	{
		mEnd = p;
	}

	PVector getNeighborVetex(const Point p)
	{
		Point above = { p.first - 1, p.second };
		Point below = { p.first + 1, p.second };
		Point left = { p.first, p.second - 1 };
		Point right = { p.first, p.second + 1 };

		PVector adjacent;
		if (isValid(above)) { adjacent.push_back(above); }
		if (isValid(below)) { adjacent.push_back(below); }
		if (isValid(left)) { adjacent.push_back(left); }
		if (isValid(right)) { adjacent.push_back(right); }

		return adjacent;
	}

	bool isValid(Point p) const
	{
		return inRange(p) && !isObstacle(p);
	}

	bool inRange(Point p) const
	{
		auto row = mMatrix.size();
		auto col = mMatrix[0].size();
		return (0 <= p.first && p.first < row) && (0 <= p.second && p.second < col);
	}

	bool isObstacle(Point p) const
	{
		return (mMatrix[p.first][p.second] == OBSTACLE);

	}
	bool inSet(const PVector& vec, Point p) const
	{
		for (auto& s : vec)
		{
			if (s == p) return true;
		}
		return false;
	}

	int distance(Point p1, Point p2)
	{
		return 1;  //as the p1,p2 is adjacent in current case. Extend: the distance not 1.
	}

	void maskPosition(PVector path, std::vector<std::vector<char> >& matrix, char c);//debug method
	PVector getPath();
private:
	const GraphMatrix mMatrix;
	const int requiredDays;

	Point mStart;
	Point mEnd;

	FatherMap fatherMap;

	static const char OBSTACLE = '*';
	static const char START = 'Z';
	static const char END = 'L';
	static const Distance INFINITE = INT_MAX;
	static const Point InvalidPoint;

};


#endif
