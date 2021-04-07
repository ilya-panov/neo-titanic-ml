#include "model/data/preprocessing/standart_scaler.h"

#include <gtest/gtest.h>

#include <iostream>

using std::cout;
using std::string;
using std::vector;
using namespace neotitanicml;

// == REFERENCE for test in 'standart_scaler.ipynb'

TEST(StandartScalerTest, SetMeasures) {
    StandartScaler scaler;

    EXPECT_TRUE(scaler.SetMeasures({0.15, 0.25}, {0.02, 0.05}));
    EXPECT_FALSE(scaler.SetMeasures({0.15, 0.25, 0.6}, {0.02, 0.05}));
    EXPECT_FALSE(scaler.SetMeasures({0.15, 0.25}, {0.02, 0.05, 0.6}));
}

TEST(StandartScalerTest, Transform) {
    StandartScaler scaler;
    scaler.SetMeasures(
        {358.33333333, 62.66666667, 6.66666667},  // mean
        {151.34581446, 7.13364485, 2.62466929}    // std
    );

    int i = 0;

    NeoML::CSparseFloatVector vect;

    for (float v : {150, 65, 3}) {
        vect.SetAt(i, v);
        i++;
    }
    vect = scaler.Transform(vect);
    i = 0;
    for (float v : {-1.37653845, 0.32708852, -1.3970014}) {
        EXPECT_NEAR(v, vect.GetValue(i), 0.001);
        i++;
    }

    vect.Nullify();
    i = 0;

    for (float v : {420, 53, 8}) {
        vect.SetAt(i, v);
        i++;
    }
    vect = scaler.Transform(vect);
    i = 0;
    for (float v : {0.40745538, -1.35508101, 0.50800051}) {
        EXPECT_NEAR(v, vect.GetValue(i), 0.001);
        i++;
    }

    vect.Nullify();
    i = 0;

    for (float v : {505, 70, 9}) {
        vect.SetAt(i, v);
        i++;
    }
    vect = scaler.Transform(vect);
    i = 0;
    for (float v : {0.96908307, 1.02799249, 0.88900089}) {
        EXPECT_NEAR(v, vect.GetValue(i), 0.001);
        i++;
    }
}