#ifndef _DIJKSTRA_HPP
#define _DIJKSTRA_HPP

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_set>
#include "Definition.hpp"
#include <cassert>
#include <climits>

using Point = std::pair<int, int>; //{row, col}
using PVector = std::vector<Point>;

using Distance = int;
using WeightVetex = std::pair<Point,Distance>;//Distance = currentVetex to startPoint.
using VetexSet = std::vector<WeightVetex>;

//Thinking: Dijkstra is a greedy algorithm, Is it valid in disconnected graph ??

class Dijkstra 
{
public:
	Dijkstra(const GraphMatrix& imatrix, const Paramerters& iParas):
		mPath(),  mStart(InvalidPoint), mEnd(InvalidPoint), minDistance(INFINITE), mMatrix(imatrix), requiredDays(iParas.maxDays)
	{
		auto vertexSet = buildVertexSet(mMatrix);
		minDistance = calculateShortestPath(vertexSet, mEnd); 
	}

	bool canReachWithRequiredDays()
	{
		std::cout << "\n minDistance is " << minDistance <<" ,requiredDays is " <<requiredDays << "  \n";
		return minDistance <= requiredDays;
	}

private:
	VetexSet buildVertexSet(const GraphMatrix& matrix)
	{
		VetexSet vset;
		for (size_t r = 0; r < matrix.size(); r++)
		{
			for (size_t c = 0; c < matrix[r].size(); c++)
			{
				if (matrix[r][c] != OBSTACLE)
				{
					Point p = { r, c };
					Distance d = INFINITE;
					if (matrix[r][c] == START)    { setStartPoint(p); d = 0; }
					else if (matrix[r][c] == END) { setEndPoint(p); }
					
					vset.push_back({p, d});
				}
			}
		}

		return vset;
	}

	void setStartPoint(Point p)
	{
		mStart = p;
	}

	void setEndPoint(Point p)
	{
		mEnd = p;
	}

	int calculateShortestPath(const VetexSet& Vset, const Point target) //refer to <Introduction To Algorithm>
	{
		VetexSet Svetex = { };
		VetexSet Qset = Vset;
		bool connectOver = false;

		while (!Qset.empty())
		{
			auto u = extractMinVetex(Qset);

			if (u.first == target || u.first == InvalidPoint) return u.second;

			joinToS(u, Svetex); //S = S U {u}

		    relaxNeighborVetexDistance(u, Qset); 
		}
		
		return INFINITE; 
	}

	WeightVetex extractMinVetex(VetexSet&  Qset)
	{
		Distance min = INFINITE;
		auto minIndex = Qset.end();
		
		for (auto iter = Qset.begin(); iter != Qset.end(); iter++)
		{
			if ((*iter).second < min)
			{
				min = (*iter).second;
				minIndex = iter;
			}
		}

		if (minIndex == Qset.end()) //indicates it's disconnected graph, mStart can't reach mEnd.
		{
			return { InvalidPoint, INFINITE };
		}

		auto minVetex = *minIndex;

		Qset.erase(minIndex);//remove min from Qset
		
		return minVetex;
	}

	void joinToS(const WeightVetex u, VetexSet& s)
	{
		s.push_back(u);
	}

	void relaxNeighborVetexDistance(const WeightVetex u, VetexSet&  Qset)//Note: the start may not reach to end if they are in two disconneted area.
	{
		
		auto adjacents = getNeighborVetex(u.first);		

		for (auto& p : adjacents)
		{
			updateShortestDistInQset(u, p, Qset);
		}

		
	}

	void updateShortestDistInQset(const WeightVetex u, const Point adjacent, VetexSet&  Qset)
	{
		
		for (auto& v : Qset)
		{
			if (v.first == adjacent)
			{
				auto newD = distance(v.first, u.first) + u.second;

				if (v.second > newD) 
				  v.second = newD;

				return ; //found Adacent In Qset.
			}
		}

		
		//for disconnected graph, may reach here.
	}

	int distance(Point p1, Point p2) 
	{ 
		return 1;  //as the p1,p2 is adjacent in current case. Extend: the distance not 1.
	}

	PVector getNeighborVetex(const Point p)
	{
		Point above = { p.first - 1, p.second }; 
		Point below = { p.first + 1, p.second };
		Point left  = { p.first, p.second - 1 };
		Point right = { p.first, p.second + 1 };

		PVector adjacent;
		if (isValid(above)) { adjacent.push_back(above); }
		if (isValid(below)) { adjacent.push_back(below); }
		if (isValid(left))  { adjacent.push_back(left); }
		if (isValid(right)) { adjacent.push_back(right); }

		return adjacent;
	}

	bool isValid(Point p) const
	{
		return inRange(p) && !isObstacle(p); //TODO check: p must in Qset ?
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

private:
	PVector mPath;
		
	Point mStart;
	Point mEnd;
	int minDistance;

	const GraphMatrix mMatrix;
	const int requiredDays;
	

	static const char OBSTACLE = '*';
	static const char START = 'Z';
	static const char END = 'L';
	static const Distance INFINITE = INT_MAX;
	static const Point InvalidPoint;
};



#endif
