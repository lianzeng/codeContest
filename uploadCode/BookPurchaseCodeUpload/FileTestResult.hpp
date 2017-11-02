#ifndef _FILE_TEST_RESULT_HPP
#define _FILE_TEST_RESULT_HPP

#include <string>
#include <vector>
#include <fstream>

class FileTestResult
{
public:
	//each line indicate a score
	FileTestResult(const std::vector<double>&  result, const std::string dstFileName)
	{
		std::ofstream ofs(dstFileName);

		ofs << std::to_string(result.size()) << "\n";

		for (auto& d : result)
		{			
			ofs << removeTailZero(std::to_string(d)) << "\n";			
		}

		ofs.flush();
		ofs.close();
	}

private:
	static std::string removeTailZero(const std::string str)//56.00 -->56, 56.600 -->56.6, 500.000000 -->500
	{
		int i = str.size() - 1;
		for (; i >= 0; --i)
		{
			if (str[i] != '0') break;
		}
		int length = (str[i] == '.') ? i : i + 1;
		return str.substr(0, length);
	}
};


#endif
