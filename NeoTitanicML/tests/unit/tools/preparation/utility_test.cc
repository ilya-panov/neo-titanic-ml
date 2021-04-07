#include "tools/preparation/utility.h"

#include <gtest/gtest.h>

using std::string;
using std::vector;
using namespace neotitanicml;

TEST(UtilityTest, split_string_test) {
    vector<string> fields;

    SplitString("123;456", ";", fields);

    EXPECT_EQ(2, fields.size());
    EXPECT_EQ("123", fields[0]);
    EXPECT_EQ("456", fields[1]);

    fields.clear();
    SplitString("123;456", ",", fields);

    EXPECT_EQ(1, fields.size());
    EXPECT_EQ("123;456", fields[0]);

    fields.clear();
    SplitString("", ",", fields);

    EXPECT_EQ(1, fields.size());
    EXPECT_EQ("", fields[0]);
}