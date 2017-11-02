#ifndef _BOWLING_BALL_HPP
#define _BOWLING_BALL_HPP

#include <string>
#include <vector>
#include <utility>

using INTVECTOR = std::vector<int>;


class BowlingBall
{

public:

	int getScore(const std::string& frames);

private:
	INTVECTOR convertStringToDigitScore(const std::string& frames);
	int charToDigit(char c);
	int getScore(const INTVECTOR&);

	bool isSpare(char c) const
	{
		return c == '/';
	}

	bool isBoundary(char c) const
	{
		return c == '|';
	}
	bool isStrike(int i) const
	{
		return i == FULLSCORE_PER_FRAME;
	}

	int ballsInCurrentFrame(int scoreOf1stBall)
	{
		static const int ONE_BALL = 1;
		static const int TWO_BALL = 2;

		return isStrike(scoreOf1stBall) ? ONE_BALL : TWO_BALL;
	}

	static const int MAX_FRAMES = 10;
	static const int FULLSCORE_PER_FRAME = 10;
};

#endif
