#ifndef _BIG_NUMBER_PLUS_HPP
#define _BIG_NUMBER_PLUS_HPP

#include <string>
#include <algorithm> //reverse

using std::string;

class BigNumberPlus //todo: implement in another way (first determin bigger number by compare string, then abs(biggerNumer) - abs(smallNumber)).
{
public:
	BigNumberPlus(const string& num1, const string& num2):finalResult() //input num has sign char ahead.
	{
		if (!num1.empty() && !num2.empty())
		{
			if (sameSign(num1, num2))
			{
				bigNumberPlus_SameSign(num1, num2);
			}
			else
			{
				bigNumberPlus_DiffSign(num1, num2);
			}

			finalResult = removeInvalidZeroAhead(finalResult);
		}
	}

	string output() const
	{
		assert(validateResult(finalResult));
		return finalResult;
	}

private:
	string removeInvalidZeroAhead(const string& str) const //003 ==> 3, -003 ==>-3,000 ==> 0
	{
		//std::cout <<"\n before remove: " << str << "\n";
		assert(!str.empty());
						
		string temp;
		bool allZero = true;
		int i = isNegative(str) ? 1 : 0;

		for (; i < str.size(); i++)
		{
			if (str[i] != '0')
			{
				allZero = false;
				break;
			}
		}

		if (allZero)  temp = "0";		
		else          temp = str.substr(i, str.size() - i);
		
		temp = isNegative(str) ? ("-" + temp) : temp;
		//std::cout << "\n after remove: " << temp << "\n";
		return temp;
	}

	bool validateResult(const string& str) const
	{
		//std::cout <<"\n final result:  " << str << "\n";
		if (str.empty()) return false;
		else if (str.size() == 1 && isNegative(str)) return false;
		else if (str.size() > 1)
		{
			if (isNegative(str) && str[1] == '0') return false; //negative number can't start with -0xxx
			if (str[0] == '0') return false; //positive number can't start with 0xxx
		}
		else 
			return true;

	}

	bool isNegative(const string& num) const
	{
		return num[0] == '-';
	}
	bool sameSign(const string& num1, const string& num2)
	{
		bool bothNegative = isNegative(num1) && isNegative(num2);
		bool bothPositive = !isNegative(num1) && !isNegative(num2);
		return bothNegative || bothPositive;
	}
	void bigNumberPlus_SameSign(const string& num1, const string& num2)
	{
		bool bothNegative = isNegative(num1);
		if (bothNegative)
		{
			auto left = removeSignChar(num1);
			auto right = removeSignChar(num2);
			auto ret = bigNumberPlus_Positive(left, right);
			finalResult = "-" + ret;
		}
		else //bothPositive
		{
			finalResult = bigNumberPlus_Positive(num1, num2);
		}
	}

	SPair appendZeroAheadToSameLength(const string& num1, const string& num2)//(15, 2) =>(15,02); (2, 15) => (02, 15);
	{
		if (num1.size() == num2.size())
			return {num1, num2};
		else
		{
			auto& shortNum = (num1.size() < num2.size() ? num1 : num2);
			auto& longNum = (num1.size() < num2.size() ? num2 : num1);
			string zeroPadding(longNum.size() - shortNum.size(),'0');
			
			if(num1.size() < num2.size())
			  return { zeroPadding + shortNum, longNum };
			else
			  return {longNum , zeroPadding + shortNum };
		}
	}

	string bigNumberPlus_Positive(const string& inum1, const string& inum2)
	{
		//for ex: 1 + 123 ==> 001 + 123 = 124 
		auto nums = appendZeroAheadToSameLength(inum1, inum2);
		assert(nums.first.size() == nums.second.size());
		
		const auto& num1 = nums.first;
		const auto& num2 = nums.second;
		size_t length = num1.size();

		string sum;
		int carry = 0;

		for (int i = length-1; i > -1; --i) //LSB -> MSB
		{
			auto temp = add(num1[i], num2[i], carry);
			carry = temp.second;
			sum.push_back(temp.first);
		}

		if (carry != 0) //carry == 1;
			sum.push_back('1');

		std::reverse(sum.begin(), sum.end());
		return sum;
	}

	int c2i(char c) 
	{
		assert('0' <= c && c <= '9');
		return c - '0';
	}

	char i2c(int i) 
	{
		assert(0 <= i && i <= 9);
		return i + '0';
	}

	std::pair<char, int> add(char c1, char c2, int icarry)
	{
		int sum = c2i(c1) + c2i(c2) + icarry;
		return {i2c(sum % 10), sum / 10};//{mod, carry}
	}

	std::pair<char, int> sub(char c1, char c2, const int icarry)
	{
		int diff = c2i(c1) - c2i(c2) - icarry;
		int diffcomp = (diff < 0) ? (10 + diff) : diff;
		int carry = (diff < 0) ? 1 : 0;
		return {i2c(diffcomp % 10), carry};
	}

	string removeSignChar(const string str)
	{
		assert(isNegative(str) && str.size() >= 2 );
		return str.substr(1, str.size() - 1);
	}

	void bigNumberPlus_DiffSign(const string& num1, const string& num2)
	{//-A + B = B - A
		string left = isNegative(num1) ? num2 : num1; // positive
		string right = isNegative(num1) ? num1 : num2; //negtive
		right = removeSignChar(right);

		finalResult = positiveBigNumberMinus(left, right);
	}

	string positiveBigNumberMinus(const string& left, const string& right)//left - right
	{
		//first,append(zero ahead) to same length, then minus, if result is negative, then caculate complement;
		//for ex: 0 - 1  = {9,carry=-1} ===>complement to: 1, add sign to -1;
		//for ex: 1 - 123 == 001 - 123 = {878,carry=-1} ===>complement to: 122, add sign to -122;
		//for ex: 3 - 2 = {1, carry = 0}, no need complement;
		assert(!isNegative(left) && !isNegative(right));

		auto nums = appendZeroAheadToSameLength(left, right);
		auto num1 = nums.first;
		auto num2 = nums.second;
		int length = num1.size();
		int carry = 0;
		string minus;
		for (int i = length - 1; i > -1; --i) //LSB--MSB
		{
			auto temp = sub(num1[i], num2[i], carry);
			carry = temp.second;
			minus.push_back(temp.first);
		}
		if (carry != 0)// left < right
		{
			minus = complement(minus);
		}
		std::reverse(minus.begin(), minus.end());//after reverse: MSB...LSB

		return (carry == 0) ? minus : ("-" + minus);
			
	}



	string complement(const string& str) //str: LSB....MSB, output: LSB..MSB
	{
		//0634 ==> 0465, 0034 ==> 0075
		//878 ==> 221
		//099 ==> 010, if 1st== 0, next=10 - i;
		//explain: 0 = 0, 1st nonzero LSB = 10 - i; Others = 9 - i ;
		assert(!str.empty());

		
		static const int LSB_COMP = 10;
		static const int MSB_COMP = 9;

		string ret;
		
		int i = 0;
		for (; i < str.size(); i++)
		{
			if (str[i] == '0') ret.push_back('0');//LSB zeros keeps.
			else break;
		}

		if(i < str.size())
			ret.push_back(i2c(LSB_COMP - c2i(str[i])));//1st nonzero LSB = 10 - i;

		for (i++; i < str.size(); i++)
		{
			ret.push_back(i2c(MSB_COMP - c2i(str[i])));//Others = 9 - i ;
		}
		return ret;
	}

private:

	string finalResult;
};



#endif
