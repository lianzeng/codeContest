// BookPurchase.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "BookPurchase.hpp"
//#include "BookPurchaseSlow.hpp"

const double BookPurchase::mdiscount[] = { 1.0, 0.95, 0.9, 0.8, 0.75 };


//1*8*1.0;2*8*0.95;3*8*0.9;4*8*0.8;5*8*0.75;
const double BookPurchase::mOneBundleAmount[] = { 8.0, 15.2, 21.6, 25.6, 30 };



BookPurchase::HashMap  BookPurchase::cache(1000, BookPurchase::hash);
int BookPurchase::cacheHit = 0;
int BookPurchase::cacheMiss = 0;




