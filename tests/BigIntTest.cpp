#include <BigInt/BigInt.h>
#include <gtest/gtest.h>

#include <vector>

using namespace ACA;
using namespace std;

TEST(summary, sum_1)
{
    ACA::BigInt number_1("0");
    ACA::BigInt number_2("0");
    const auto expected = number_1;
    const auto actual = number_1 + number_2;
    ASSERT_EQ(expected, actual);
}

TEST(summary, sum_2)
{
    ACA::BigInt number_1("555555");
    ACA::BigInt number_2("555555");
    const auto expected = ACA::BigInt("1111110");
    const auto actual = number_1 + number_2;
    ASSERT_EQ(expected, actual);
}

TEST(deduction, ded_1)
{
    ACA::BigInt number_1("5555555555");
    ACA::BigInt number_2("5555555555");
    const auto expected = ACA::BigInt("0");
    const auto actual = number_1 - number_2;
    ASSERT_EQ(expected, actual);
}

TEST(deduction, ded_2)
{
    ACA::BigInt number_1("5555555555");
    ACA::BigInt number_2("555555555");
    const auto expected = ACA::BigInt("5000000000");
    const auto actual = number_1 - number_2;
    ASSERT_EQ(expected, actual);
}

TEST(deduction, ded_3)
{
    ACA::BigInt number_1("55555555");
    ACA::BigInt number_2("555555555");
    const auto expected = std::exception("Trying to make BigInt negative!!!");

    EXPECT_THROW(
        {
            try
            {
                const auto actual = number_1 - number_2;
            }
            catch (const std::exception &err)
            {
                EXPECT_STREQ(err.what(), expected.what());
                throw;
            }
        },
        std::exception);
}

TEST(multiplication, mul_1)
{
    BigInt number_1("0");
    BigInt number_2("555555555");
    const auto expected = number_1;
    const auto actual = number_1 * number_2;
    ASSERT_EQ(expected, actual);
}

TEST(multiplication, mul_2)
{
    BigInt number_1("2");
    BigInt number_2("555555555");
    const auto expected = BigInt("1111111110");
    const auto actual = number_1 * number_2;
    ASSERT_EQ(expected, actual);
}

TEST(division, div_1)
{
    BigInt number_1("2");
    BigInt number_2("0");
    const auto expected = std::exception("Trying to divide by 0 !!!\n");

    EXPECT_THROW(
        {
            try
            {
                const auto actual = number_1 / number_2;
            }
            catch (const std::exception &err)
            {
                EXPECT_STREQ(err.what(), expected.what());
                throw;
            }
        },
        std::exception);
}

TEST(division, div_2)
{
    BigInt number_1("8");
    BigInt number_2("2");
    const auto expected = BigInt("4");
    const auto actual = number_1 / number_2;
    ASSERT_EQ(expected, actual);
}

TEST(residual, res_1)
{
    BigInt number_1("8");
    BigInt number_2("2");
    const auto expected = BigInt("0");
    const auto actual = number_1 % number_2;
    ASSERT_EQ(expected, actual);
}

TEST(residual, res_2)
{
    BigInt number_1("8");
    BigInt number_2("3");
    const auto expected = BigInt("2");
    const auto actual = number_1 % number_2;
    ASSERT_EQ(expected, actual);
}

TEST(degree, deg_1)
{
    BigInt number_1("8");
    BigInt number_2("2");
    const auto expected = BigInt("64");
    const auto actual = number_1 ^ number_2;
    ASSERT_EQ(expected, actual);
}

TEST(degree, deg_2)
{
    BigInt number_1("0");
    BigInt number_2("2");
    const auto expected = BigInt("0");
    const auto actual = number_1 % number_2;
    ASSERT_EQ(expected, actual);
}

TEST(compare_big, cmp_b_1)
{
    BigInt number_1("8");
    BigInt number_2("2");
    const auto expected = true;
    const auto actual = number_1 > number_2;
    ASSERT_EQ(expected, actual);
}

TEST(compare_big, cmp_b_2)
{
    BigInt number_1("8");
    BigInt number_2("22222");
    const auto expected = false;
    const auto actual = number_1 > number_2;
    ASSERT_EQ(expected, actual);
}

TEST(compare_small, cmp_s_1)
{
    BigInt number_1("8888888888");
    BigInt number_2("22222");
    const auto expected = false;
    const auto actual = number_1 < number_2;
    ASSERT_EQ(expected, actual);
}

TEST(compare_small, cmp_s_2)
{
    BigInt number_1("8888888888");
    BigInt number_2("2222222222222");
    const auto expected = true;
    const auto actual = number_1 < number_2;
    ASSERT_EQ(expected, actual);
}

/*
TEST(BigInt, Increment) {
    const vector<pair<BigInt, BigInt>> ExpectedActualList = {
        { BigInt("0"), BigInt("1") },
        { BigInt("8"), BigInt("9") },
        { BigInt("9"), BigInt("10") },
        { BigInt("99999"), BigInt("100000") }
    };

    for (auto [num, num_plus_one] : ExpectedActualList) {
        EXPECT_EQ(++num, num_plus_one);
    }
}
*/

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
