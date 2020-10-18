/**
  * @file nmfDonutModelAPI.h
  *
  * @brief API definition for the calculations of the Rank Proportion Algorithm.  No GUI
  * data here, just matrix number crunching.
  *
  * @copyright
  * Public Domain Notice\n
  *
  * National Oceanic And Atmospheric Administration\n\n
  *
  * This software is a "United States Government Work" under the terms of the
  * United States Copyright Act.  It was written as part of the author's official
  * duties as a United States Government employee/contractor and thus cannot be copyrighted.
  * This software is freely available to the public for use. The National Oceanic
  * And Atmospheric Administration and the U.S. Government have not placed any
  * restriction on its use or reproduction.  Although all reasonable efforts have
  * been taken to ensure the accuracy and reliability of the software and data,
  * the National Oceanic And Atmospheric Administration and the U.S. Government
  * do not and cannot warrant the performance or results that may be obtained
  * by using this software or data. The National Oceanic And Atmospheric
  * Administration and the U.S. Government disclaim all warranties, express
  * or implied, including warranties of performance, merchantability or fitness
  * for any particular purpose.\n\n
  *
  * Please cite the author(s) in any work or product based on this material.
  *
  */

#ifndef DONUTMODELAPI_H
#define DONUTMODELAPI_H

#include "nmfConstantsDonut.h"
#include "nmfUtils.h"

#include <boost/numeric/ublas/matrix.hpp>

/**
 * @brief This is the API class for the Rank Proportion Algorithm.  All of the
 * calculations that go into generating the Proportion and Output tables are performed
 * by this class. There are no GUI calls in this class.  It simply accepts a matrix,
 * operates on it, and then sends it back to the calling program (by reference).
 */
class nmfDonutModelAPI
{

private:
    bool calculateProportionMatrix(
            boost::numeric::ublas::matrix<double>& matrix);
    bool calculateOutputMatrix(
            boost::numeric::ublas::matrix<double>& matrix,
            std::vector<double>& RPAData,
            std::vector<double>& AiData,
            std::vector<double>& NullSelectivityData);

public:
    /**
     * @brief The class constructor
     */
    nmfDonutModelAPI();
   ~nmfDonutModelAPI() {}

    /**
     * @brief This method accepts a partially completed matrix and completes it with
     * RPA data as well returning Output vectors
     * @param Matrix : the input matrix containing Species, Rank, Proportion,
     * and Output data (the latter two of which are filled in by this method)
     * @param RPAData : vector containing the resulting RPA Model data values per species
     * @param AiData : vector containing the resulting Null Ambient (Ai) data values per species
     * (this is equivalent to the relative abundance data)
     * @param NullSelectivityData : vector containing the resulting null selectivity data
     * (this is equivalent to 1/N, where N is the number of species)
     * @return Returns true if completed without any errors, else returns false
     */
    bool calculateRPAModel(
            boost::numeric::ublas::matrix<double>& Matrix,
            std::vector<double>& RPAData,
            std::vector<double>& AiData,
            std::vector<double>& NullSelectivityData);
};

#endif
