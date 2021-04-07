#include "tools/preparation/csv_reader.h"

#include <gtest/gtest.h>

#include "settings.h"

using std::string;
using std::vector;
using namespace neotitanicml;

TEST(CsvReaderTest, Init_test) {
    CsvReader reader1("no-exist-file.csv");

    EXPECT_FALSE(reader1.Init());

    CsvReader reader2(string(TEST_DATA_DIR) + "/simple.csv");

    EXPECT_TRUE(reader2.Init());
}

TEST(CsvReaderTest, Next_test) {
    CsvReader reader(string(TEST_DATA_DIR) + "/simple.csv");

    EXPECT_TRUE(reader.Init());

    vector<string> fields;

    // 1 строка из файла
    EXPECT_TRUE(reader.Next(fields));
    EXPECT_EQ(2, fields.size());
    EXPECT_EQ("123", fields[0]);
    EXPECT_EQ("456", fields[1]);
    // 2 строка из файла
    EXPECT_TRUE(reader.Next(fields));
    EXPECT_EQ(1, fields.size());
    EXPECT_EQ("badstring", fields[0]);
    // 3 строка из файла (пустая)
    EXPECT_TRUE(reader.Next(fields));
    EXPECT_EQ(1, fields.size());
    EXPECT_EQ(0, fields[0].length());
    // 4 строка из файла
    EXPECT_TRUE(reader.Next(fields));
    EXPECT_EQ(2, fields.size());
    EXPECT_EQ("789", fields[0]);
    EXPECT_EQ("abc", fields[1]);
    // попытка чтения в конце файла
    EXPECT_FALSE(reader.Next(fields));
    EXPECT_EQ(0, fields.size());
}