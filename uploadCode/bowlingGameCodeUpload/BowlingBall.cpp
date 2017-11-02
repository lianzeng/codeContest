
#include "stdafx.h"
#include "BowlingBall.hpp"

using std::string;

int BowlingBall::getScore(const string& frames)
{
	INTVECTOR frameScores = convertStringToDigitScore(frames);
	return getScore(frameScores);
}

INTVECTOR BowlingBall::convertStringToDigitScore(const string& frames)
{
	INTVECTOR vec;
	for (const auto & c : frames)
	{
		if (isSpare(c))
			vec.push_back(FULLSCORE_PER_FRAME - vec.back());//exception
		else if (!isBoundary(c))
			vec.push_back(charToDigit(c));
	}

	return vec;
}

int BowlingBall::charToDigit(char c)
{
	switch (c)
	{
	case 'X': //strike
		return FULLSCORE_PER_FRAME;
	case '-': //miss
		return 0;
	default: //0~9
		return c - '0';
	}
}


int BowlingBall::getScore(const INTVECTOR& vec)
{
	int sum = 0;
	for (size_t i = 0, frame = 0; frame < MAX_FRAMES; frame++)
	{
		if ((vec[i] == FULLSCORE_PER_FRAME) ||
			(vec[i] + vec[i + 1]) == FULLSCORE_PER_FRAME)
		{
			sum += vec[i] + vec[i + 1] + vec[i + 2];
		}
		else
			sum += vec[i] + vec[i + 1];

		i += ballsInCurrentFrame(vec[i]);//step to next frame

	}


	return sum;
}

