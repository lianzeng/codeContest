
#include "stdafx.h"
#include "ParseTestData.hpp"
#include "FileTestResult.hpp"
#include "BookPurchase.hpp" //quick-cut && cache
//#include "BookPurchaseSlow.hpp" //only cache

int main()
{
    ParseTestData input("input.txt");
    auto testCases = input.getTestCases();  

    std::vector<double> result;

    for (auto& oneCase: testCases)
    {
        BookPurchase bp(oneCase);
        result.push_back(bp.calcuAmount());
    }

    FileTestResult saveFileToResult(result, "output.txt");

    return 0;
}