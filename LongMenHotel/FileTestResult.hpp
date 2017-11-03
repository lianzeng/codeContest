#ifndef _FILE_TEST_RESULT_HPP
#define _FILE_TEST_RESULT_HPP

#include <string>
#include <vector>
#include <fstream>

class FileTestResult
{
public:
	//each line indicate a score
	FileTestResult(const std::vector<string>&  result, const std::string dstFileName)
	{
		std::ofstream ofs(dstFileName);

		int i = 1;
		for (auto& d : result)
		{			
			ofs <<"Case #" <<std::to_string(i) <<": "<< d << "\n";			
			i++;
		}

		ofs.flush(); 
		ofs.close();
	}


	
};


#endif
