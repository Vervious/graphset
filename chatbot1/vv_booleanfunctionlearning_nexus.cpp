//
//  vv_functionlearning_nexus.cpp
//  chatbot1
//
//  Created by Benjamin Y Chan on 3/19/16.
//  Copyright © 2016 vervious. All rights reserved.
//

#include "vv_booleanfunctionlearning_nexus.hpp"

bool BooleanFunctionLearningNexus::classifyInput(std::string) {
    // pass through an input through our model of the boolean function,
    // (or in general, system), predict what it does, and act
    // based on that prediction (forced action. There's only one choice).
    // -----
    return true;
}

// in the motivation world, we don't want this function ever
// to be called. Erm. I guess if this function is called, we
// aren't maximizing the information integral.
// - thought: all an RNN is doing is using parts of the input
//   (or past input) to predict other members of the input.
//   It's literally attempting to extract relationships out
//   of the observed universe in order to predict more of the
//   observed universe.
std::string BooleanFunctionLearningNexus::acknowledgeMistake() {
    return "ack";
}

void BooleanFunctionLearningNexus::acknowledgeSuccess() {
    
}

BooleanFunctionLearningNexus::BooleanFunctionLearningNexus():
    functionModel("SuperModel") {
    // What's the simplest forced boolean output system?
    // general: input -> system -> input = output
    
}