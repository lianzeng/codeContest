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
		for (auto& score : result)
		{
			auto str = std::to_string(score);
			ofs << str << "\n";
		}

		ofs.flush();
		ofs.close();
	}

};


#endif
