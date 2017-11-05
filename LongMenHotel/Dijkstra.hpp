#ifndef _DIJKSTRA_HPP
#define _DIJKSTRA_HPP

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_set>
#include "Definition.hpp"
#include <cassert>
#include <climits>
#include <unordered_map>

using Point = std::pair<int, int>; //{row, col}
using PVector = std::vector<Point>;

using Distance = int;
using WeightVetex = std::pair<Point,Distance>;//Distance = currentVetex to startPoint.
using VetexSet = std::vector<WeightVetex>;

//Thinking: Dijkstra is a greedy algorithm,  it is also valid in disconnected graph.

#define HASH_MAP_BUCKET_SIZE 200

class Dijkstra 
{
public:
	Dijkstra(const GraphMatrix& imatrix, const Paramerters& iParas):
		preMap(HASH_MAP_BUCKET_SIZE,hash),mPath(), mSvetex(),  
		mStart(InvalidPoint), mEnd(InvalidPoint), minDistance(INFINITE), 
		mMatrix(imatrix), requiredDays(iParas.maxDays)
	{
		auto vertexSet = buildVertexSet(mMatrix);
		minDistance = calculateShortestPath(vertexSet, mEnd); 
	}

	bool canReachWithRequiredDays() const
	{
		if (minDistance == INFINITE) std::cout << "\n start can't reach End , they are disconnected. \n";
		else std::cout << "\n minDistance is " << minDistance <<" ,requiredDays is " <<requiredDays << "  \n";
		return minDistance <= requiredDays;
	}

	bool printPath();

	
	
private:
	PVector getPath();

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
					Distance d = INFINITE; //initial all the distance to Infinite except the start point.
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
		mSvetex = { };
		VetexSet Qset = Vset;
		bool connectOver = false;

		while (!Qset.empty())
		{
			auto u = extractMinVetex(Qset);

			if (u.first == target || u.first == InvalidPoint) return u.second;

			joinToS(u, mSvetex); //S = S U {u}

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

	void relaxNeighborVetexDistance(const WeightVetex u, VetexSet&  Qset)
	{
		
		auto adjacents = getNeighborVetex(u.first);		

		for (auto& p : adjacents)
		{
			updateDistance(u, p, Qset);
		}

		
	}

	void updateDistance(const WeightVetex u, const Point toUpdate, VetexSet&  Qset)
	{
		
		for (auto& v : Qset)
		{
			if (v.first == toUpdate)
			{
				auto newD = distance(v.first, u.first) + u.second;

				if (v.second > newD)
				{
					v.second = newD;//TODO: set newD as the pre-vetex, will be used to form path.
					recordPreShip(v.first, u.first);
				}

				return ;
			}
		}
				
	}

	void recordPreShip(const Point curr, const Point pre)
	{
		assert(preMap.find(curr) == preMap.end());
		preMap[curr] = pre;
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
		return inRange(p) && !isObstacle(p) && !joined(p); 
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
	bool joined(Point p) const
	{
		for (auto& s: mSvetex)
		{
			if (s.first == p) return true;
		}
		return false;
	}

	static size_t hash(Point p)
	{
		return p.first*p.second;
	}

	
	void maskPosition(PVector path, std::vector<std::vector<char> >& matrix, char c);//debug method
private:
	using HashMap = std::unordered_map<Point,Point,decltype(hash)*>;
	HashMap preMap;//[key,value] --- [currVetex, preVetex]
	PVector mPath;

	VetexSet mSvetex;//temp.
		
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
