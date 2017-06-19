#pragma once

#include <sstream>
#include <cstring>
#include <cfloat>
#include <cmath>
#include "../Calculation.h"

#define REQUIRE_EQUAL(first, second) \
	{ \
	auto firstValue = (first); \
	auto secondValue = (second); \
	if (firstValue != secondValue) { \
		std::ostringstream oss; \
		oss<<"Require equal failed: "<< # first << "!= " << # second \
		   <<" (" << firstValue << "!= "<<secondValue << ")\n" \
		   <<"At "<<__FILE__<<":"<<__LINE__<<"\n"; \
		   cout <<oss.str(); \
		   throw -1; \
		} \
	else { \
		std::cout<<"Require equal passed: "<< # first << " == " << # second \
		   <<" (" << firstValue << " == "<<secondValue << ")\n"; \
	} \
} 

#define TEST(test_name) void test_name ## _inner(); \
	void test_name() { \
		std::cerr << "Running test " #test_name ":\n"; \
		try { \
			test_name ## _inner(); \
			std::cerr << "passed\n\n"; \
		} catch(...) { \
			std::cerr<<"FAILED\n\n"; \
		} \
	} \
	void test_name ## _inner()


TEST(testDelimeter)
{
	REQUIRE_EQUAL(Calculation("-1        + 2 -5 +       12"),8);
	REQUIRE_EQUAL(Calculation("  "),DBL_MAX);
	REQUIRE_EQUAL(Calculation(" , "),DBL_MAX);
	REQUIRE_EQUAL(Calculation(",.,."),DBL_MAX);
	REQUIRE_EQUAL(Calculation(",1"),DBL_MAX);
	REQUIRE_EQUAL(Calculation("1.+1,"),2);
}

TEST(testCurrentCalculation)
{

	REQUIRE_EQUAL(Calculation("-1+5-3"),1);
	REQUIRE_EQUAL(Calculation("-10 + (8 * 2.5) -1- (3 / 1,5)"),7);
	REQUIRE_EQUAL(Calculation("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)"),11);
	REQUIRE_EQUAL(Calculation("1.2323/2. + 343*2-3"),683.62);
	REQUIRE_EQUAL(Calculation("3/0.0"),INFINITY);
	REQUIRE_EQUAL(Calculation("0/3"),0);

}

TEST(testNotCurrentDelimeter)
{
	REQUIRE_EQUAL(Calculation(""),DBL_MAX);
	REQUIRE_EQUAL(Calculation("-1 + vv"),DBL_MAX);
	REQUIRE_EQUAL(Calculation("v"),DBL_MAX);
	REQUIRE_EQUAL(Calculation("=1"),DBL_MAX);
	REQUIRE_EQUAL(Calculation("+"),DBL_MAX);
}

	int RunAllTest()
	{
		try
		{
			testDelimeter();
			testCurrentCalculation();
			testNotCurrentDelimeter();
			//testBracket();
			//testNot
		}
		catch(std::exception& ex)
		{
			std::cerr << ex.what() << "\n";
			return 1;
		} 
		return 0;
	}