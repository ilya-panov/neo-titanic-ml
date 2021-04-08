#include "model/data/passenger_info_converter.h"

#include <gtest/gtest.h>

#include <iostream>

#include "model/data/passenger_info.h"

using std::cout;
using std::string;
using std::vector;
using namespace neotitanicml;
using namespace NeoML;

class PassengerInfoConverterTest : public ::testing::Test {
 protected:
    PassengerInfoConverter converter;

    void SetUp() override {
        LabelEncoder sex_encoder({"male", "female"});
        LabelEncoder embarked_encoder({"C", "S", "Q"});
        converter = PassengerInfoConverter(9, 0, 80);
        converter.SetEncoders(sex_encoder, embarked_encoder);
    }
};

TEST_F(PassengerInfoConverterTest, FromStrings1) {
    vector<string> strings = {
        "80", "0", "3", "male", "22.0", "0", "0", "9.0", "S"};

    PassengerInfo info;

    bool ok = converter.FromStrings(strings, info);

    EXPECT_TRUE(ok);
    EXPECT_EQ(0, info.surviveded);
    EXPECT_EQ(3, info.pclass);
    EXPECT_EQ("male", info.sex);
    EXPECT_EQ(22, info.age);
    EXPECT_EQ(0, info.sib_sp);
    EXPECT_EQ(0, info.parch);
    EXPECT_NEAR(9.0, info.fare, 0.001);
    EXPECT_EQ("S", info.embarked);
}

TEST_F(PassengerInfoConverterTest, FromStrings2) {
    vector<string> strings = {
        "177", "0", "1", "female", "50.0", "0", "0", "28.7125", "C"};

    PassengerInfo info;

    bool ok = converter.FromStrings(strings, info);

    EXPECT_TRUE(ok);
    EXPECT_EQ(0, info.surviveded);
    EXPECT_EQ(1, info.pclass);
    EXPECT_EQ("female", info.sex);
    EXPECT_EQ(50, info.age);
    EXPECT_EQ(0, info.sib_sp);
    EXPECT_EQ(0, info.parch);
    EXPECT_NEAR(28.7125, info.fare, 0.001);
    EXPECT_EQ("C", info.embarked);
}

// Исправление поля embarked. (последнее поле)
TEST_F(PassengerInfoConverterTest, FromStrings3) {
    vector<string> strings = {
        "177", "0", "1", "female", "50.0", "0", "0", "28.7125", ""};

    PassengerInfo info;

    bool ok = converter.FromStrings(strings, info);

    EXPECT_TRUE(ok);
    EXPECT_EQ("S", info.embarked);
}

// Некорректное кол-во полей
TEST_F(PassengerInfoConverterTest, FromStrings4) {
    vector<string> strings = {
        "177", "0", "1", "female"};

    PassengerInfo info;

    bool ok = converter.FromStrings(strings, info);

    EXPECT_FALSE(ok);
}

// Числовое поле с некорректными данными
TEST_F(PassengerInfoConverterTest, FromStrings5) {
    vector<string> strings = {
        "177", "0", "1", "female", "50.0", "ABC", "0", "28.7125", ""};

    PassengerInfo info;

    bool ok = converter.FromStrings(strings, info);

    EXPECT_FALSE(ok);
}

// Не указан пол
TEST_F(PassengerInfoConverterTest, FromStrings6) {
    vector<string> strings = {
        "177", "0", "1", "", "50.0", "0", "0", "28.7125", ""};

    PassengerInfo info;

    bool ok = converter.FromStrings(strings, info);

    EXPECT_FALSE(ok);
}

TEST_F(PassengerInfoConverterTest, Validate1) {
    vector<string> strings = {
        "177", "0", "1", "ABC", "50.0", "0", "0", "28.7125", ""};

    PassengerInfo info;

    bool ok = converter.FromStrings(strings, info);

    EXPECT_FALSE(ok);
}

TEST_F(PassengerInfoConverterTest, Validate2) {
    vector<string> strings = {
        "177", "0", "1", "male", "50.0", "0", "0", "28.7125", "T"};

    PassengerInfo info;

    bool ok = converter.FromStrings(strings, info);

    EXPECT_FALSE(ok);
}

TEST_F(PassengerInfoConverterTest, Validate3) {
    vector<string> strings = {
        "177", "0", "1", "male", "150", "0", "0", "28.7125", "Q"};

    PassengerInfo info;

    bool ok = converter.FromStrings(strings, info);

    EXPECT_FALSE(ok);
}

TEST_F(PassengerInfoConverterTest, Info2Vec1) {
    vector<string> strings = {
        "177", "0", "1", "female", "50.0", "0", "0", "28.7125", "C"};

    PassengerInfo info;

    bool ok = converter.FromStrings(strings, info);

    EXPECT_TRUE(ok);

    CSparseFloatVector vect;
    int class_id = converter.Info2Vec(info, vect);

    EXPECT_EQ(0, class_id);

    EXPECT_NEAR(1.0, vect.GetValue(0), 0.001);
    EXPECT_NEAR(1.0, vect.GetValue(1), 0.001);
    EXPECT_NEAR(50.0, vect.GetValue(2), 0.001);
    EXPECT_NEAR(0.0, vect.GetValue(3), 0.001);
    EXPECT_NEAR(0.0, vect.GetValue(4), 0.001);
    EXPECT_NEAR(28.7125, vect.GetValue(5), 0.001);
    EXPECT_NEAR(0.0, vect.GetValue(6), 0.001);
}

TEST_F(PassengerInfoConverterTest, Info2Vec2) {
    vector<string> strings = {
        "177", "0", "1", "male", "50.0", "0", "0", "28.7125", "S"};

    PassengerInfo info;

    bool ok = converter.FromStrings(strings, info);

    EXPECT_TRUE(ok);

    CSparseFloatVector vect;
    int class_id = converter.Info2Vec(info, vect);

    EXPECT_EQ(0, class_id);

    EXPECT_NEAR(0.0, vect.GetValue(1), 0.001);
    EXPECT_NEAR(1.0, vect.GetValue(6), 0.001);
}

TEST(PassengerInfoConverter_FromJson, T1) {
    nlohmann::json json;

    auto converter = PassengerInfoConverter::FromJson(json);

    EXPECT_FALSE(converter);
}

TEST(PassengerInfoConverter_FromJson, T2) {
    nlohmann::json json;

    json["expected-fields"] = 9;
    json["min-age"] = 0;
    json["max-age"] = 80;

    auto converter = PassengerInfoConverter::FromJson(json);

    EXPECT_FALSE(converter);
}

TEST(PassengerInfoConverter_FromJson, T3) {
    nlohmann::json json;

    json["expected-fields"] = 9;
    json["min-age"] = 0;
    json["max-age"] = 80;
    json["sex-labels"] = {"male", "female"};
    json["embarked-labels"] = {"C", "S", "Q"};

    auto converter = PassengerInfoConverter::FromJson(json);

    EXPECT_TRUE(converter);

    vector<string> strings = {
        "177", "0", "1", "female", "50.0", "0", "0", "28.7125", "C"};

    PassengerInfo info;

    bool ok = converter->FromStrings(strings, info);

    EXPECT_TRUE(ok);
}