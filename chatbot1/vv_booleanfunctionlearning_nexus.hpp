//
//  vv_booleanfunctionlearning_nexus.hpp
//  chatbot1
//
//  Created by Benjamin Y Chan on 3/19/16.
//  Copyright © 2016 vervious. All rights reserved.
//
//  Hopefully this can learn arbitrary turing computable functions.
//  All learning can be interpreted as being unsupervised, but in this case let's start
//  with a highly regimented supervised structure.
//  Inputs come in pairs:
//  First, an input.
//  Then, an output. (A classification)
//  Second, an input whether the output is right or wrong. This is the motivator.
//  -- repeat
//
//  Note the diference between the supervised and unsupervised scenarios. In the supervised
//  scenario, the best way to resonate with the input!!! (and maximize that information integral,
//  or whatever the theoretical basis is) is to be able to predict everything correctly.
//  That in and of itself is sufficient motivator.
//
//  We further restrict the space to the classification problem, expecting only a boolean output.
//  Only boolean actions may be taken. (Why not take more action? That reduces resonance. #TODO: prove)
//  #TODO: Prove that resonance equates to some function of information divergence.
//  #TODO: Equate graphset divergence with information divergence.
//  Again, having the right boolean output is the best way to resonate with the input.

#ifndef vv_booleanfunctionlearning_nexus_hpp
#define vv_booleanfunctionlearning_nexus_hpp

#include <stdio.h>
#include <string>
#include "vv_graphset.hpp"

class BooleanFunctionLearningNexus {
private:
    // void encodeNewInformation(std::string);
    VVGraphSet functionModel;
    // let's abstract this out because it's not implicit
    // in this model, although it is in the general case.
    // the "other" source of information that is indirectly
    // observational (probably better to just give "yes/no"
    // information than this "mistake" trickery. But maybe
    // this can let us think differently about motivation.
    void acknowledgeSuccess();
public:
    // represents the sole observation and sole action the chatbot can take
    // why bool? See above.
    // Note: there is also no information to be
    // gained here, because the input can literally
    // be anything. (The observation can literally be
    // random).
    bool classifyInput(std::string);
    // ah. We made a mistake in our last classification.
    // this is an actually useful observation...
    // It's like watching a randomly generated number
    // get passed through a system and seeing an output.
    // We're simply learning about the system in an
    // interactive way, where a) interaction is forced
    // and b) all interactions are equal. A more generalized
    // system would have the option of interaction.
    std::string acknowledgeMistake();
    BooleanFunctionLearningNexus();
};


#endif /* vv_functionlearning_nexus_hpp */
