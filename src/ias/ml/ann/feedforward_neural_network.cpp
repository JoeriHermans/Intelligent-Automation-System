/**
 * A class which represents the properties and actions of a feedforward
 * neural network.
 *
 * @date                    5 April, 2015
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2015 Joeri HERMANS
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <cmath>

// Application dependencies.
#include <ias/ml/ann/feedforward_neural_network.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const double FeedforwardNeuralNetwork::kDefaultLearningRate = 0.05;

// END Constants. ////////////////////////////////////////////////////

inline void FeedforwardNeuralNetwork::initialize( void ) {
    mLearningRate = kDefaultLearningRate;
    initializeWeightMatrices();
}

inline void FeedforwardNeuralNetwork::setDimensionInput(
        const std::size_t dimInput ) {
    // Checking the precondition.
    assert( dimInput > 0 );

    mDimensionInput = dimInput;
}

inline void FeedforwardNeuralNetwork::setDimensionHidden(
        const std::size_t dimHidden ) {
    // Checking the precondition.
    assert( dimHidden > 0 );

    mDimensionHidden = dimHidden;
}

inline void FeedforwardNeuralNetwork::setDimensionOutput(
        const std::size_t dimOutput ) {
    // Checking the precondition.
    assert( dimOutput > 0 );

    mDimensionOutput = dimOutput;
}

void FeedforwardNeuralNetwork::initializeWeightMatrices( void ) {
    mWeightMatrix_1 = Eigen::MatrixXd::Random(mDimensionInput,mDimensionHidden);
    mWeightMatrix_2 = Eigen::MatrixXd::Random(mDimensionHidden,mDimensionOutput);
    // Matrices are uniformly sampled between [-1.1], we want to initialize the
    // weight between [-0.5,0.5], as a result, we do a scalar multiplication
    // of the matrices with 0.5.
    mWeightMatrix_1 *= 0.5;
    mWeightMatrix_2 *= 0.5;
}

void FeedforwardNeuralNetwork::applyActivation( Eigen::VectorXd & layer ) const {
    std::size_t nRows = layer.rows();
    double x;

    for( std::size_t i = 0 ; i < nRows ; ++i ) {
        x = layer(i);
        layer(i) = (1/(1 + exp(-x)));
    }
}

FeedforwardNeuralNetwork::FeedforwardNeuralNetwork(
        const std::size_t dimensionInput,
        const std::size_t dimensionHidden,
        const std::size_t dimensionOutput ) {
    setDimensionInput(dimensionInput);
    setDimensionHidden(dimensionHidden);
    setDimensionOutput(dimensionOutput);
    initialize();
}

void FeedforwardNeuralNetwork::setLearningRate( const double learningRate ) {
    // Checking the precondition.
    assert( learningRate > 0 );

    mLearningRate = learningRate;
}

Eigen::VectorXd FeedforwardNeuralNetwork::propagate(
        const Eigen::VectorXd & input ) const {
    Eigen::VectorXd output;
    Eigen::VectorXd hidden;

    hidden = (input.transpose() * mWeightMatrix_1);
    applyActivation(hidden);
    output = (hidden.transpose() * mWeightMatrix_2);
    applyActivation(output);

    return ( output );
}

void FeedforwardNeuralNetwork::backpropagate(
    const Eigen::VectorXd & input, const Eigen::VectorXd & expectedOutput ) {
    Eigen::VectorXd output;
    Eigen::VectorXd errorOutput(mDimensionOutput);
    Eigen::VectorXd errorHidden(mDimensionHidden);
    Eigen::VectorXd hidden;
    Eigen::VectorXd hiddenPreactivation;

    // Checking the precondition.
    assert( static_cast<std::size_t>(input.rows()) == mDimensionInput &&
            static_cast<std::size_t>(expectedOutput.rows()) == mDimensionOutput );

    // Propagate the signal through the neurons.
    hiddenPreactivation = (input.transpose() * mWeightMatrix_1);
    hidden = hiddenPreactivation;
    applyActivation(hidden);
    output = (hidden.transpose() * mWeightMatrix_2);
    applyActivation(output);
    // Calculate the error at the output layer.
    for( std::size_t i = 0 ; i < mDimensionOutput ; ++i ) {
        double o_i = output(i);
        double e_i = expectedOutput(i);
        double delta = o_i * (1 - o_i) * (e_i - o_i);
        errorOutput(i) = delta;
    }
    // Calculate the error at the hidden layer.
    for( std::size_t i = 0 ; i < mDimensionHidden ; ++i ) {
        double errorSum = 0;
        // Calculate the error of the associated weights.
        for( std::size_t j = 0 ; j < mDimensionOutput ; ++j )
            errorSum += mWeightMatrix_2(i,j) * errorOutput(j);
        double h_i = hidden(i);
        double delta = h_i * (1 - h_i) * errorSum;
        errorHidden(i) = delta;
    }
    // Adjust the weights from the hidden to the output layer.
    for( std::size_t i = 0 ; i < mDimensionInput ; ++i ) {
        for( std::size_t j = 0 ; j < mDimensionHidden ; ++j ) {
            double delta = mLearningRate * errorHidden(j) * input(i);
            mWeightMatrix_1(i,j) += delta;
        }
    }
    // Adjust the weights from the input to the hidden layer.
    for( std::size_t i = 0 ; i < mDimensionHidden ; ++i ) {
        for( std::size_t j = 0 ; j < mDimensionOutput ; ++j ) {
            double delta = mLearningRate * errorOutput(j) * hiddenPreactivation(i);
            mWeightMatrix_2(i,j) += delta;
        }
    }
}
