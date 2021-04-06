#include <gtest/gtest.h>

#include "model/data/preprocessing/label_encoder.h"


using std::string;
using std::vector;
using namespace neotitanicml;


TEST(LabelEncoderTest, Transform) {

    vector<string> labels = {"l1", "l2"};

    LabelEncoder le(labels);

    EXPECT_EQ (0, le.Transform("l1"));
    EXPECT_EQ (1, le.Transform("l2"));
    EXPECT_EQ (-1, le.Transform("not-exist"));
}