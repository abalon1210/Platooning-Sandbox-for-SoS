/****************************************************************************/
/// @file    ApplRSU_04_Classify.h
/// @author  Mani Amoozadeh <maniam@ucdavis.edu>
/// @author  second author name
/// @date    Nov 2015
///
/****************************************************************************/
// VENTOS, Vehicular Network Open Simulator; see http:?
// Copyright (C) 2013-2015
/****************************************************************************/
//
// This file is part of VENTOS.
// VENTOS is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#ifndef APPLRSUCLASSIFY_H_
#define APPLRSUCLASSIFY_H_

#include "ApplRSU_03_ActiveTL.h"
#include <boost/circular_buffer.hpp>

#undef ev

#include <shark/Data/Dataset.h>
#include <shark/Data/Csv.h>
#include <shark/ObjectiveFunctions/Loss/ZeroOneLoss.h>

#include <shark/LinAlg/Base.h>
#include <shark/Rng/GlobalRng.h>
#include <shark/Models/Converter.h>
#include <shark/Models/Kernels/GaussianRbfKernel.h>
#include <shark/Algorithms/Trainers/McSvmOVATrainer.h>
#include <shark/Algorithms/Trainers/McSvmCSTrainer.h>
#include <shark/Algorithms/Trainers/McSvmWWTrainer.h>
#include <shark/Algorithms/Trainers/McSvmLLWTrainer.h>
#include <shark/Algorithms/Trainers/McSvmADMTrainer.h>
#include <shark/Algorithms/Trainers/McSvmATSTrainer.h>
#include <shark/Algorithms/Trainers/McSvmATMTrainer.h>
#include <shark/Algorithms/Trainers/McSvmMMRTrainer.h>
#include <shark/Algorithms/Trainers/McReinforcedSvmTrainer.h>

#define ev  (*cSimulation::getActiveEnvir())

// un-defining ev!
// why? http://stackoverflow.com/questions/24103469/cant-include-the-boost-filesystem-header
#undef ev
#include "boost/filesystem.hpp"
#define ev  (*cSimulation::getActiveEnvir())

namespace VENTOS {

class sample_type
{
public:
    double xPos;
    double yPos;
    double speed;

    sample_type(double x, double y, double z)
    {
        this->xPos = x;
        this->yPos = y;
        this->speed = z;
    }
};


class resultEntry
{
public:
    unsigned int label_predicted;
    unsigned int label_true;
    double time;

    resultEntry(unsigned int i1, unsigned int i2, double d)
    {
        this->label_predicted = i1;
        this->label_true = i2;
        this->time = d;
    }
};


class ApplRSUCLASSIFY : public ApplRSUTLVANET
{
public:
    ~ApplRSUCLASSIFY();
    virtual void initialize(int stage);
    virtual void finish();
    virtual void handleSelfMsg(cMessage* msg);

protected:
    void virtual executeEachTimeStep();

    virtual void onBeaconVehicle(BeaconVehicle*);
    virtual void onBeaconBicycle(BeaconBicycle*);
    virtual void onBeaconPedestrian(BeaconPedestrian*);
    virtual void onBeaconRSU(BeaconRSU*);
    virtual void onData(LaneChangeMsg*);

private:
    void initializeGnuPlot();
    void draw();
    int loadTrainer();
    int trainClassifier(shark::AbstractSvmTrainer<shark::RealVector, unsigned int> *);
    template <typename beaconGeneral> void onBeaconAny(beaconGeneral wsm);
    template <typename beaconGeneral> unsigned int makePrediction(beaconGeneral wsm);
    template <typename beaconGeneral> void collectSample(beaconGeneral wsm);
    void saveSampleToFile();
    void saveClassificationResults();

private:
    bool classifier;
    bool collectTrainingData;
    double trainError;
    double GPSerror;
    int debugLevel;

    FILE *plotterPtr = NULL;
    boost::filesystem::path trainingFilePath      = "results/ML/trainData.txt";
    std::vector<sample_type> samples;
    std::vector<int> labels;

    std::map< std::string /*class name*/, unsigned int /*label*/> classLabel = {
            {"WC_4", 0},
            {"SC_4", 1},
            {"NC_4", 2},
            {"EC_4", 3},
            {"NC_2", 4},
            {"EC_2", 5},
            {"WC_2", 6},
            {"SC_2", 7},
            {"EC_3", 8},
            {"WC_3", 9},
            {"NC_3", 10},
            {"SC_3", 11}
    };

    shark::ClassificationDataset sampleData;
    shark::blas::matrix<double, shark::blas::row_major> shark_sample;
    shark::KernelClassifier<shark::RealVector> *kc_model;
    std::map< std::string /*entity id*/, std::vector<resultEntry> > classifyResults;
    std::map< std::string /*entity id*/, boost::circular_buffer<unsigned int> > lastClassifications;
};

}

#endif
