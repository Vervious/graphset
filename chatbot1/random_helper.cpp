//
//  random_helper.cpp
//  coinminer
//
//  Created by Benjamin Y Chan on 2/26/16.
//  Copyright © 2016 vervious. All rights reserved.
//

#include "random_helper.hpp"
#include <ctime>


/**
 * Prepare to return a random integer in [0, 2^(diff - constraint)]
 */
RandomHelper::RandomHelper(int diff, int constraint):
    rng(static_cast<unsigned int>(std::time(0))),
    range(0, pow(2, diff - 1 - constraint)),
    nonce(rng, range) {
}

/**
 * Just 2^(diff) this time
 */
RandomHelper::RandomHelper(int diff):
    rng(static_cast<unsigned int>(std::time(0))),
    range(0, pow(2, diff - 1)),
    nonce(rng, range) {
}

RandomHelper::RandomHelper(int diff, int constraint, int seed):
    rng(static_cast<unsigned int>(std::time(0)) + seed),
    range(0, pow(2, diff - 1 - constraint)),
    nonce(rng, range) {
}



/**
 * Generate a random integer, as configured
 */
unsigned long long int RandomHelper::rand_nonce() {
    return nonce();
}