#ifndef _FILE_TEST_RESULT_HPP
#define _FILE_TEST_RESULT_HPP

#include <string>
#include <vector>
#include <fstream>

class FileTestResult
{
public:
	//each line indicate a score
	FileTestResult(const std::vector<int>&  result, const std::string dstFileName)
	{
		std::ofstream ofs(dstFileName);

		int caseIndex = 1;
		for (auto& i : result)
		{			
			ofs <<"Case #" <<std::to_string(caseIndex) <<": "<< std::to_string(i) << "\n";
			caseIndex++;
		}

		ofs.flush();
		ofs.close();
	}


	
};


#endif
