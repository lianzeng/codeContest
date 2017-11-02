#ifndef  _CANDY_DISPATCH_HPP
#define  _CANDY_DISPATCH_HPP

#include "Definition.hpp"

class CandyDispatch
{
public:

	CandyDispatch(const Paramerters& ipara, const HeadCountList& groups):
		mGroupNum(ipara.groupNum), mBoxSize(ipara.candyNumPerBox),mheadCountList(groups), mHappyGroupNum(0)
	{
		assert(mheadCountList.size() == mGroupNum);
		assert(2 <= mBoxSize && mBoxSize <= 4);

		smartDispatch(mheadCountList);
	}

	int getHappyGroupNum()
	{
		//assert(mHappyGroupNum > 0);
		return mHappyGroupNum;
	}

private:
	void smartDispatch(const HeadCountList& headCounts)
	{		
		auto classifiedHeadCounts = classifyGroupsByBoxSize(headCounts);
		
		auto leftHeadCounts = findIndependHappyGroups(classifiedHeadCounts);//1.pick group whose size % BoxSize == 0.
		assert(leftHeadCounts.size() == mBoxSize - 1);
		if (isOver(leftHeadCounts)) return;

		//2. search pair group: (group1 + group2) %  BoxSize == 0.
		leftHeadCounts = findPairHappyGroups(leftHeadCounts);		
		if (isOver(leftHeadCounts)) return;
		assert(1 <= leftHeadCounts.size() && leftHeadCounts.size() <= 2);
		
		//3.
		findLeftHappyGroups(leftHeadCounts);
				
	}

	bool isOver(const HeadCountList& vec)
	{
		int sum = 0;
		for (auto& num : vec)
			sum += num;
		return sum == 0;
	}

	HeadCountList classifyGroupsByBoxSize(const HeadCountList& headCounts)
	{//0.classify input to groups % boxSize

		HeadCountList vec(mBoxSize, 0);
		for (auto& num : headCounts)
		{
			vec[num % mBoxSize] ++;
		}
		return vec;
	}

	HeadCountList findIndependHappyGroups(const HeadCountList& headCounts)
	{//pick group whose size % BoxSize == 0.

		mHappyGroupNum += headCounts[0];

		HeadCountList leftHeadCounts(headCounts.begin() + 1, headCounts.end());
		assert(leftHeadCounts.size() > 0);

		return leftHeadCounts;
	}

	HeadCountList findPairHappyGroups(const HeadCountList& ivec)
	{//search pair group : (group1 + group2) % BoxSize == 0.
		
		auto vec = ivec;
		int indexL = 0;
		int indexR = vec.size() - 1;

		//case1: one group from left, another from right
		for (;indexL < indexR ; indexL++, indexR--) 
		{
			auto pairGroupNum = minValue(vec[indexL], vec[indexR]);

			mHappyGroupNum += pairGroupNum;

			vec[indexL] -= pairGroupNum;
			vec[indexR] -= pairGroupNum;
		}
		
		//case2:two group both from middle
		if (indexL == indexR)
		{
			assert(mBoxSize % 2 == 0);//BoxSize is even number;

			auto pairNum = vec[indexL] / 2;
			mHappyGroupNum += pairNum;

			vec[indexL] -= pairNum *2;
		}

		return createLeftGroup(vec);
		
	}

	HeadCountList createLeftGroup(const HeadCountList& vec) // create leftGroup whose num > 0
	{
		HeadCountList leftGroup;
		
		for (auto& num : vec)
		{
			if (num > 0)
			{
				leftGroup.push_back(num);
			}
		}

		assert(leftGroup.size() <= 2);
		return leftGroup;
	}

	void findLeftHappyGroups(const HeadCountList& ivec)
	{ 

		if (ivec.size() == 1)//only a category left
		{
			mHappyGroupNum += divideRoundUp(ivec[0], mBoxSize);
		}
		else//ivec.size() == 2: 
		{
			assert(mBoxSize == 4);//and category=1&&2 or 2&&3
						
			auto min = minValue(ivec[0],ivec[1]);
			auto max = maxValue(ivec[0], ivec[1]);

			assert(min == 1);//only one category2 left.
			mHappyGroupNum += min;			

			if (max > 2) //as one category2 above need match two category1/3;
			{
				max -= 2;
				mHappyGroupNum += divideRoundUp(max, mBoxSize);
			}
			 
		}
	}
	
	int divideRoundUp(int a, int b)
	{
		return a / b  +  (a % b ? 1 : 0);
	}

	int minValue(int v1, int v2)
	{
		return v1 <= v2 ? v1 : v2;
	}
	int maxValue(int v1, int v2)
	{
		return v1 > v2 ? v1 : v2;
	}

private:
	
	const int mGroupNum;
	const int mBoxSize;//candyPerBox
	const HeadCountList& mheadCountList;
	int mHappyGroupNum;
};




#endif // ! _CANDY_DISPATCH_HPP

