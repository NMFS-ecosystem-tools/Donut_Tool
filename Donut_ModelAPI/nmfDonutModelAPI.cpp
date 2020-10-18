#include "nmfDonutModelAPI.h"


nmfDonutModelAPI::nmfDonutModelAPI()
{
}


bool
nmfDonutModelAPI::calculateProportionMatrix(
        boost::numeric::ublas::matrix<double>& Matrix)
{
    int numRows = Matrix.size1();
    double RankTotal = 0;
    double val;

    for (int row=0; row<numRows; ++row) {
        // Calculate Proportion fields
        for (int col  = nmfConstantsDonut::COLUMN_PROP_DETECTION;
                 col <= nmfConstantsDonut::COLUMN_PROP_PRODUCT; ++col) {
            RankTotal = 0;
            for (int row2=0;row2<numRows;++row2) {
                RankTotal += Matrix(row2,col-5);
            }
            if (! nmfUtils::isNearlyZero(RankTotal)) {
                Matrix(row,col) = ((numRows+1) - Matrix(row,col-5))/RankTotal;
            }
        }
        // Calculate Product field
        val = 1;
        for (int col  = nmfConstantsDonut::COLUMN_REL_ABUND;
                 col <= nmfConstantsDonut::COLUMN_OVERLAP; ++col) {
            val *= Matrix(row,col);
        }
        for (int col  = nmfConstantsDonut::COLUMN_PROP_DETECTION;
                 col <= nmfConstantsDonut::COLUMN_PROP_PRODUCT; ++col) {
            val *= Matrix(row,col);
        }
        Matrix(row,nmfConstantsDonut::COLUMN_PROP_PRODUCT) = val;
    }

    return true;
}

bool
nmfDonutModelAPI::calculateOutputMatrix(
        boost::numeric::ublas::matrix<double>& Matrix,
        std::vector<double>& RPAData,
        std::vector<double>& AiData,
        std::vector<double>& NullSelectivityData)
{
    int numRows = Matrix.size1();
    double sumProducts=0;
    double val;

    RPAData.clear();
    AiData.clear();
    NullSelectivityData.clear();

    for (int row=0; row<numRows; ++row) {
        sumProducts += Matrix(row,nmfConstantsDonut::COLUMN_PROP_PRODUCT);
    }
    if (nmfUtils::isNearlyZero(sumProducts)) {
        return false;
    }

    // Calculate Outputs
    for (int row=0; row<numRows; ++row) {
        for (int col  = nmfConstantsDonut::COLUMN_RPA_MODEL;
                 col <= nmfConstantsDonut::COLUMN_NULL_SELECTIVITY; ++col) {
            val = 0;
            if (col == nmfConstantsDonut::COLUMN_RPA_MODEL) {
                val = (Matrix(row,nmfConstantsDonut::COLUMN_PROP_PRODUCT) / sumProducts) * 100.0;
                RPAData.push_back(val);
            } else if (col == nmfConstantsDonut::COLUMN_NULL_AMBIENT) {
                val = Matrix(row,nmfConstantsDonut::COLUMN_REL_ABUND) * 100.0;
                AiData.push_back(val);
            } else if (col == nmfConstantsDonut::COLUMN_NULL_SELECTIVITY) {
                val = (1.0/numRows) * 100.0;
                NullSelectivityData.push_back(val);
            }
            Matrix(row,col) = val;
        }
    }

    return true;
}

bool
nmfDonutModelAPI::calculateRPAModel(
        boost::numeric::ublas::matrix<double>& Matrix,
        std::vector<double>& RPAData,
        std::vector<double>& AiData,
        std::vector<double>& NullSelectivityData)
{
    bool ok;

    // Calculate Proportion Table
    ok = calculateProportionMatrix(Matrix);
    if (! ok) {
        return false;
    }

    // Calculate Output Table
    ok = calculateOutputMatrix(Matrix,RPAData,AiData,NullSelectivityData);
    if (! ok) {
        return false;
    }

    return true;
}
