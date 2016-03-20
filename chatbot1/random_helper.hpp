//
//  random_helper.hpp
//  coinminer
//
//  Created by Benjamin Y Chan on 2/26/16.
//  Copyright © 2016 vervious. All rights reserved.
//

#ifndef random_helper_hpp
#define random_helper_hpp

#include <stdio.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>


class RandomHelper {
private:
    boost::mt19937 rng;
    boost::uniform_int<uint64_t> range;
    boost::variate_generator<boost::mt19937&, boost::uniform_int<uint64_t>> nonce;
public:
    RandomHelper(int diff);
    RandomHelper(int diff, int constraint);
    RandomHelper(int diff, int constraint, int seed);
    unsigned long long int rand_nonce();
};

#endif /* random_helper_hpp */
