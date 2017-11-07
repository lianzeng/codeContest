// CandyGift.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "FileTestResult.hpp"
#include "ParseTestData.hpp"
#include "CandyDispatch.hpp"

/*
analysis: 
1.A team was happy only if all the member within team get new candys;
2.Once team sequency is fixed, the previous left candy must give to next,
  can't open new box,so the next team is unhappy.
3.total candys not exactly same(but more than) with total students, least waste(may not);
4.output the maxmum happy teams.

input：[num1,num2...numN], candyPerBox(BoxSize).
output：adjust the team sequence to achive max happy group num.

solution：
suppose BoxSize = 4, input[4,8,3,1,6,7,10,6]
0.convert the input to an equivalent representation by (% BoxSize) : newinput = [0,0,3,1,2,3,2,2],
  and classify the result to BoxSize groups:{vector[newinput[i]]++ }, vec[BoxSize] = {2,1,3,2};
1.pick independ groups first, so happyNum = vec[0] = 2;leftvec[boxSize-1]={1,3,2};
2.pick pair groups:happyNum += min(leftvec[0],leftvec[2]) + leftvec[1]/2 = 1+1=2; leftvec2[]={0,1,1};
3.pick left groups(triple group or quarter group): happyNum += 1; this step need deduce from the special case.

note: step2 and step3 is virtually a two-sum and three-sum problem , but here has special solution.
*/

int main()
{
	ParseTestData input("input.txt");
	auto testCases = input.getTestCases();

	std::vector<int> result;

	for (auto& oneCase : testCases)
	{
		CandyDispatch dispatch(oneCase.first, oneCase.second);
		result.push_back(dispatch.getHappyGroupNum());
		std::cout << "\n" << dispatch.getHappyGroupNum() << "\n\n";
	}


	
	FileTestResult saveResultToFile(result, "output.txt");
	std::cout << "Candy ok." << "\n";
    return 0;
}

