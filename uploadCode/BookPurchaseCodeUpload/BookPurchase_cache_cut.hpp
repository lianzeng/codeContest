#ifndef BOOK_PURCHASE_INCLUDED
#define BOOK_PURCHASE_INCLUDED



#include <vector>
#include <algorithm>
#include <functional>
#include <cfloat>
#include <iostream>
#include <unordered_map>

using IVector = std::vector<int>;
using BOOKS = IVector;

#define assert(x)   
//#include <cassert>

enum DiscountType
{
	One_Kind_Book = 0,
	Two_Kind_Book,
	Three_Kind_Book,
	Four_Kind_Book,
	Five_Kind_Book,
	DISCOUNT_TYPE_NUM
};

class BookPurchase
{
public:
	BookPurchase(const IVector& ibooks) :mAmount(1.0e+10), mbooks(ibooks)
	{
		assert(mbooks.size() == BOOK_TYPE_NUM);
	}

	double calcuAmount()
	{
		if (mbooks.empty()) return 0.0;

		reOrderInDescend(mbooks);

		calcuAmount(mbooks, 0.0);
		return mAmount;
	}

private:
	double calcuAmount(const IVector& books, const double preCost)//preCost for quick-cut during recursive for performance
	{
		assert(isDescendSort(books));

		if (onlyContainOneKindBook(books)) //leaf
		{
			return caculOneKindBookAmount(books[0], preCost);
		}
		double minAmount = DBL_MAX;
		for (int i = Five_Kind_Book; i > One_Kind_Book; --i)
		{
			auto type = static_cast<DiscountType>(i);
			if (meetDiscount(books, type) && !exceedBestCost(preCost))
			{
				auto currCost = oneBundleAmount(type);
				auto totalCost = currCost + leftBooksAmount(books, type, preCost + currCost);
				if (totalCost < minAmount) minAmount = totalCost;
			}
		}

		return minAmount;
	}

	bool exceedBestCost(double preCost)
	{
		return preCost >= mAmount;
	}

	double leftBooksAmount(const IVector& books, const DiscountType type, const double preCosted)
	{
		assert(type < DISCOUNT_TYPE_NUM);
		auto leftBooks = books;
		updateBooksAccordingToTypeSelection(leftBooks, type);
		reOrderInDescend(leftBooks);
		return getOrUpdate(leftBooks, preCosted);
	}

	double getOrUpdate(const IVector& books, const double preCosted)
	{
		auto iter = cache.find(books);
		if (iter != cache.end())
		{
			cacheHit++;
			updateBestCost(iter->second + preCosted);
			return iter->second;
		}
		else
		{
			cacheMiss++;
			return cache[books] = calcuAmount(books, preCosted);
		}
	}

	void updateBooksAccordingToTypeSelection(IVector& books, DiscountType type)
	{
		for (int i = 0; i <= type; i++)
		{
			assert(books[i] > 0);
			books[i] -= 1;
		}
	}

	void updateBestCost(double cost)
	{
		if (cost < mAmount)
			mAmount = cost;
	}

	double caculOneKindBookAmount(int num, double preCost)
	{
		auto lastCost = num*oneBundleAmount(One_Kind_Book);
		updateBestCost(lastCost + preCost);
		return lastCost;
	}

	bool onlyContainOneKindBook(const IVector& books) const
	{
		return books[1] == 0;//because books in descend order
	}



	bool meetDiscount(const IVector&  books, DiscountType type)//books:descendOrder
	{
		switch (type)
		{
		case One_Kind_Book:  return books[0] >= 1;
		case Two_Kind_Book:  return books[1] >= 1;
		case Three_Kind_Book:return books[2] >= 1;
		case Four_Kind_Book: return books[3] >= 1;
		case Five_Kind_Book: return books[4] >= 1;
		default: { assert(0); return false; }
		}
	}

	double oneBundleAmount(DiscountType type) const
	{
		return mOneBundleAmount[type];
	}



	void reOrderInDescend(IVector& books)
	{
		std::sort(books.begin(), books.end(), std::greater<int>());
	}

	static bool isDescendSort(const IVector& vec)
	{
		if (vec.size() <= 1) return true;

		for (size_t i = 0; i < vec.size() - 1; i++)
		{
			if (vec[i] < vec[i + 1]) return false;
		}
		return true;
	}



private:

	static const size_t BOOK_TYPE_NUM = 5;
	static const double mdiscount[DISCOUNT_TYPE_NUM];
	static const double mOneBundleAmount[DISCOUNT_TYPE_NUM];
	double  mAmount;//bestCost
	IVector mbooks;

public:

	static size_t hash(const BOOKS& books)
	{
		assert(isDescendSort(books));
		return books[0] + books[1] * 2 + books[2] * 3 + books[3] * 5 + books[4] * 7;
	}
	using HashMap = std::unordered_map<BOOKS, double, decltype(hash)*>;
	static HashMap  cache;//books -> amount
	static int cacheHit;
	static int cacheMiss;
};

#endif



