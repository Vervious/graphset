//
//  vv_motivation_circuit.hpp
//  chatbot1
//
//  Created by Benjamin Y Chan on 2/4/16.
//  Copyright © 2016 vervious. All rights reserved.
//

#ifndef vv_motivation_circuit_hpp
#define vv_motivation_circuit_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "vv_knowledge_nexus.hpp"

/**
 * motivation is an integral part of intelligence,
 * part of the definition, if you will...
 * - generally, motivation to self-perpetuate
 * - the only way to combat entropy over time is to 
 *       encompass information
 * - thus, every system must have a mechanism to encompass
 *       even more information. We can call this a motivation,
 *       regardless of whether it is intentional or accidental.
 * - a motivation can manifest as a desire to self-replicate
 *       (in life, to procreate), or more artificially, as we
 *       define below.
 */
class MotivationCircuit {
    // let's make this motivation really simple and very straightforward.
    // Basically, compare our own information with the universe information.
    // - since we don't know what universe information is, we must guess
    // - so this circuit, every so often, motivates a prediction about the universe
    //   and checks its correctness. It then motivates self-modification to become
    //   more correct about the universe (this is important)
    // - in a sense, this is quite like your typical machine learning training mechanism
public:
    // OK. So this is going to sort of need to be an online measure
    // that can evaluate a chatbot state (as an argument).
    // - the metric we use is going to be: the anti-"find out more". This is wehther
    //       the chatbot "successfully interpreted the text".
    // - one potential approach is to give a robot an understanding score, having seen an input string/sentence
    //       and after interpreting it.
    // - this version takes in an array of sentences, and returns an integer score, from
    //       0 (no understanding) to something enormous.
    // we can sort of define this recursively!
    int understandingScoreForSentenceVectors(std::vector<std::string> graphset);
};

#endif /* vv_motivation_circuit_hpp */
