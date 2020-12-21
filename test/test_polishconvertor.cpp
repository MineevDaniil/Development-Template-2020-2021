#include "polishconvertor.h"

#include <gtest.h>

TEST(PolishConvertor, konstruktor_rabotaet)
{
	EXPECT_NO_THROW(PolishConvertor conv);
}

TEST(PolishConvertor, ConvertToPolish_rabotaet)
{
    PolishConvertor convertor0;
	char* expression0 = "1 + 2\0";
	char* polish_expression0 = "1 2 +\0";
	char* res0 = convertor0.ConvertToPolish(expression0);
	EXPECT_TRUE(strcmp(res0, polish_expression0)==0);

	PolishConvertor convertor1;
	char* expression1 = "(1 + 2) * 3\0";
	char* polish_expression1 = "1 2 + 3 *\0";
	char* res1 = convertor1.ConvertToPolish(expression1);
	EXPECT_TRUE(strcmp(res1, polish_expression1) == 0);

	PolishConvertor convertor2;
	char* expression2 = "(1.1 + 2.2) * 3.3\0";
	char* polish_expression2 = "1.1 2.2 + 3.3 *\0";
	char* res2 = convertor2.ConvertToPolish(expression2);
	EXPECT_TRUE(strcmp(res2, polish_expression2) == 0);


	PolishConvertor convertor3;
	char* expression3 = "1 ^ 2 * 3\0";
	char* polish_expression3 = "1 2 ^3 *\0";
	char* res3 = convertor3.ConvertToPolish(expression3);
	EXPECT_TRUE(strcmp(res3, polish_expression3) == 0);

	PolishConvertor convertor4;
	char* expression4 = "[3] * 3\0";
	char* polish_expression4 = "3  ]3 *\0";
	char* res4 = convertor4.ConvertToPolish(expression4);
	EXPECT_TRUE(strcmp(res4, polish_expression4) == 0);

	PolishConvertor convertor5;
	char* expression5 = "[_3] * 3\0";
	char* polish_expression5 = " 3 _ ]3 *\0";
	char* res5 = convertor5.ConvertToPolish(expression5);
	EXPECT_TRUE(strcmp(res5, polish_expression5) == 0);
}

TEST(PolishConvertor, Calculate1_rabotaet)
{

	PolishConvertor convertor;
	char* expression = "1.0 + 2.0\0";
	char* res0 = convertor.ConvertToPolish(expression);
	double result = convertor.Calculate(res0);
	EXPECT_TRUE(result == 3);
}

TEST(PolishConvertor, Calculate2_rabotaet)
{
	PolishConvertor convertor;
	char* expression = "4.0 - 2.0\0";
	char* res = convertor.ConvertToPolish(expression);
	double result = convertor.Calculate(res);
	EXPECT_TRUE(result == 2);
}

TEST(PolishConvertor, Calculate3_rabotaet)
{
	PolishConvertor convertor;
	char* expression = "8.0 / 2.0\0";
	char* res = convertor.ConvertToPolish(expression);
	double result = convertor.Calculate(res);
	EXPECT_TRUE(result == 4);
}

TEST(PolishConvertor, Calculate4_rabotaet)
{
	PolishConvertor convertor;
	char* expression = "8.0 * 2.0\0";
	char* res = convertor.ConvertToPolish(expression);
	double result = convertor.Calculate(res);
	EXPECT_TRUE(result == 16);
}

TEST(PolishConvertor, Calculate5_rabotaet)
{
	PolishConvertor convertor;
	char* expression = "4.0 ^ 2.0\0";
	char* res = convertor.ConvertToPolish(expression);
	double result = convertor.Calculate(res);
	EXPECT_TRUE(result == 16);
}

TEST(PolishConvertor, Calculate6_rabotaet)
{
	PolishConvertor convertor;
	char* expression = "[4.0]\0";
	char* res = convertor.ConvertToPolish(expression);
	double result = convertor.Calculate(res);
	EXPECT_TRUE(result == 4);
}

TEST(PolishConvertor, Calculate7_rabotaet)
{
	PolishConvertor convertor;
	char* expression = "(3.0 + 2.0) * 5.0\0";
	char* res = convertor.ConvertToPolish(expression);
	double result = convertor.Calculate(res);
	EXPECT_TRUE(result == 25);
}

