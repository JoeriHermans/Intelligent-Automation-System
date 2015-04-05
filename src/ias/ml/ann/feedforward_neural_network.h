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

#ifndef FEEDFORWARD_NEURAL_NETWORK_H_
#define FEEDFORWARD_NEURAL_NETWORK_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cstdint>
#include <Eigen/Dense>

// END Includes. /////////////////////////////////////////////////////

class FeedforwardNeuralNetwork {

    public:

    // BEGIN Class constants. ////////////////////////////////////////

    /**
     * Contains the default learning rate of the learning algorithm.
     *
     * @note    This value will be equal to 0.05.
     */
    const static double kDefaultLearningRate;

    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * The dimension of the input vector of the feedforward neural network.
     */
    std::size_t mDimensionInput;

    /**
     * The dimension of the hidden layer in the feedforward neural network.
     */
    std::size_t mDimensionHidden;

    /**
     * The dimension of the output layer in the feedforward neural network.
     */
    std::size_t mDimensionOutput;

    /**
     * Contains the weight matrix between the input and the hidden layer.
     */
    Eigen::MatrixXd mWeightMatrix_1;

    /**
     * Contains the weight matrix between the hidden and the output layer.
     */
    Eigen::MatrixXd mWeightMatrix_2;

    /**
     * The learning rate of the algorithm.
     *
     * @note    By default, this value will be equal to kDefaultLearningRate.
     */
    double mLearningRate;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void );

    inline void setDimensionInput( const std::size_t dimInput );

    inline void setDimensionHidden( const std::size_t dimHidden );

    inline void setDimensionOutput( const std::size_t dimOutput );

    void initializeWeightMatrices( void );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    FeedforwardNeuralNetwork( const std::size_t dimensionInput,
                              const std::size_t dimensionHidden,
                              const std::size_t dimensionOuput );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~FeedforwardNeuralNetwork( void ) = default;

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    void setLearningRate( const double learningRate );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* FEEDFORWARD_NEURAL_NETWORK_H_ */
