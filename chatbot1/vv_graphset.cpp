//
//  vv_graphset.cpp
//  chatbot1
//
//  Created by Benjamin Y Chan on 2/19/16.
//  Copyright © 2016 vervious. All rights reserved.
//

#include "vv_graphset.hpp"
#include <map>
#include <cmath>

// a bidirectional adjacency list
std::map<Label, std::map<Label, float>> backingStructure;
// lookup a graphset by composition. Unique.
std::map<Label, Label> hashForLabel;

void VVGraphSet::printStructure() {
    
}

// constructor/conversion
VVGraphSet::VVGraphSet(Label label) {
    Label hash = hashForLabel[label];
    std::map<Label, float> neighbors = backingStructure[hash];
    this->stringLabel = label;
    this->neighbors = &neighbors;
    // note, creating a new graphset does not create a composition label
}

//// create/get a graphset interface representing a set of graphsets. Not necessarily unique (the only one), may return one of many options.
//VVGraphSet VVGraphSet::Abstraction(std::set<Label> sets) {
//    Label compositionlabel = compositionLabelForNeighbors(sets);
//    std::set<Label> matchingGraphSets = graphSetForCompositionLabel[compositionlabel];
//    if (matchingGraphSets.size() > 0) {
//        // one exists already! Just take the first.
//        return VVGraphSet(*matchingGraphSets.begin());
//    }
//    // else, construct new abstraction.
//    VVGraphSet returnSet = VVGraphSet(compositionlabel);
//    if (returnSet.neighbors->size() == 0) {
//        // the relationships need to be instantiated
//        for (auto neighbor : sets) {
//            returnSet.addChild(neighbor);
//        }
//    }
//    return returnSet;
//}

void VVGraphSet::addChild(VVGraphSet childGraph) {
    relateGraphSets(this, &childGraph);
}

void VVGraphSet::removeChild(VVGraphSet childGraph) {
    delateGraphSets(this, &childGraph);
}

void VVGraphSet::relateChildren(VVGraphSet child1, VVGraphSet child2) {
    relateGraphSets(&child1, &child2);
}

void VVGraphSet::delateChildren(VVGraphSet child1, VVGraphSet child2) {
    delateGraphSets(&child1, &child2);
}

// relate with equal weight to both
void VVGraphSet::relateGraphSets(VVGraphSet *g1, VVGraphSet *g2) {
    // this propogates to the global map
    (*g1->neighbors)[g2->getLabel()] = g1->averageWeight();
    // should probably make an addParent method at some point instead
    (*g2->neighbors)[g1->getLabel()] = g2->averageWeight();
    // invalidate hash cache
    g1->cachedHash = "";
    g2->cachedHash = "";
}

void VVGraphSet::delateGraphSets(VVGraphSet *g1, VVGraphSet *g2) {
    g1->neighbors->erase(g2->getLabel());
    g2->neighbors->erase(g1->getLabel());
    // invalidate hash cache
    g1->cachedHash = "";
    g2->cachedHash = "";
}

// print current string label, or also composition of composing nodes labels
std::string VVGraphSet::getLabel(bool composition) {
    return this->stringLabel;
}

// relabel the current label
void VVGraphSet::relabel(std::string newLabel) {
    // update backing store location
    backingStructure[newLabel] = std::move(backingStructure[this->stringLabel]);
    backingStructure.erase(this->stringLabel);
    this->stringLabel = newLabel;
}

// - #todo define a metric.
double VVGraphSet::informationContent(VVGraphSet referenceSet) {
    return 0;
}

/*==============*\
*   REP CHECKS   *
\*==============*/

// enforce that weights (movement fractions) add
// up to 1.
// given how we calculate fractions (weight / totalWeight)
// this is now kind of useless
//void VVGraphSet::checkRep() {
//    float total = 0;
//    for (auto neighbor : *this->neighbors) {
//        total += neighbor.second;
//    }
//    float diff = fabs(total - 1.);
//    if (diff > 0.0001) {
//        throw "ERROR: Weights don't add up!";
//    }
//}

/*=============*\
*   UTILITIES   *
\*=============*/

float VVGraphSet::totalWeight() {
    float total = 0;
    for (auto neighbor : *this->neighbors) {
        total += neighbor.second;
    }
    return total;
}

float VVGraphSet::averageWeight() {
    return this->totalWeight() / this->neighbors->size();
}

// generate a probably unique hash for the given graphset
// replaces prior notion of composition label
Label VVGraphSet::hash() {
    if (this->cachedHash.size() != 0) {
        return this->cachedHash;
    }
    // generate an integer hash for our neighbors
    int uniqueSum = 0;
    for (auto neighbor: *this->neighbors) {
        std::string intString = "";
        for (auto c : neighbor.first) {
            intString += std::to_string((int)c);
        }
        int intRep = std::stoi(intString);
        uniqueSum += int(intRep * neighbor.second);
    }
    // eh. This isn't a good hash by any means
    // but it should work enough.
    this->cachedHash = std::to_string(uniqueSum);
    return this->cachedHash;
}

/*==========================================*\
*  SIMULATION                                *
*  See header file for theoretical concerns. *
\*==========================================*/

// diffusion: having weights is basically the same thing.
std::map<Label, float> VVGraphSet::simulateBehavior(std::map<Label, float> inputEnergy) {
    // for now, run for a finite number of iterations
    std::map<Label, float> nextEnergyAlloc;
    std::map<Label, float> *currentEnergy = &inputEnergy;
    std::map<Label, float> *nextEnergy = &nextEnergyAlloc;
    std::map<Label, float> *tempEnergy;

    
    // the current discretized time step
    // (literally everything is discretized)
    const int NUM_ITERS = 1000;
    for (int time = 0; time < NUM_ITERS; time++) {
        // diffuse next energy
        for (auto n : *currentEnergy) {
            VVGraphSet node = n.first;
            float fracTotal = node.totalWeight();
            for (auto nConfig: *node.neighbors) {
                (*nextEnergy)[nConfig.first] +=
                    (nConfig.second / fracTotal) * n.second;
            }
        }
        
        // we can reuse the current energy space
        tempEnergy = currentEnergy;
        currentEnergy = nextEnergy;
        nextEnergy = tempEnergy;
        // eh. reallocating may be better #preopt
        nextEnergy->clear();
    }
    
    // pick out the output nodes
    // (#todo: do we need this reduction?)
    for (Label label : this->boundaryNodes) {
        float outputVal = (*currentEnergy)[label];
        if (outputVal != 0) {
            (*nextEnergy)[label] = outputVal;
        }
    }
    return *nextEnergy;
}


// DEPRECATED
//// justifying the model:
//// OK. So. The universe: an infinitely (or finitely?) dimensional space, with little
//// infinitely small "balls" of energy moving around in space through time.
//// You can build abstractions around a discrete spaces that contain "balls" of energy.
//// Where will a ball go next? within an abstraction, you have no idea.
//// But if you know it will go to another event space, you can draw a line?
//// If you know it will split up, you can draw two lines?
//// if you know it will split up non-equally, you can draw weighted lines?
//// how many ways can the energy move as time progresses?
//
//std::set<std::pair<Label, float>> VVGraphSet::simulateBehavior(std::set<std::pair<Label, float>> inputEnergy) {
//    // inputEnergy should be in boundaryNodes. We should check this
//    // in a future version. #HACKLYFE
//    // if there are multiple boundary nodes, some energy might escape
//    // there sooner than others. Some nodes may exude energy multiple
//    // times per simulation. We need a callback? How do we deal with
//    // time? We could just attach an input/output time encoder/decoder
//    // but that would yield a much larger network.
//    // #todo time<->space tradeoff. Formalize. But our input/output
//    //       is probably going to be in the time domain already.
//    //       why even convert? (it's easier to code)
//    
//    // TEMPORARY: Only support the sum over time of energy leaving the
//    // system. Should be ok at least for boolearning.
//    // Will loop forever if energy gets trapped. #todo fix this.
//    
//    std::map<Label, float> currentEnergyLocs;
//    std::set<std::pair<Label, float>> finalEnergyLocs;
//    for (auto energyInput : inputEnergy) {
//        currentEnergyLocs[energyInput.first] = energyInput.second;
//    }
//    
//    // now, loop until "convergence"
//    while (currentEnergyLocs.size() > 0) {
//        // when energy encounters a fork, which way does it go?
//        // please don't tell me that weights are necessary here.
//        // What does it mean for two nodes to be connected to a third?
//        // they share a relationship. An abstraction. They are reduced
//        // to equality under parentship. What if we just assume
//        // that everyone gets a fair share? Errrrr. All neighbors
//        // are the same. Otherwise they wouldn't share the same
//        // relationship. Right? (I'm not convinced) #todo formalize
//        // #todo: would adding weights simplify the number
//        //        of computations that you'd have to make?
//        // (why not weights? My head doesn't explicitly give certain
//        //  thoughts more weight... otherwise they'd be lost?)
//        for (auto i : currentEnergyLocs) {
//            // don't instantiate a new graphset every time
//            // just to save some memory #prematureOptimization?
//            VVGraphSet currentNode = i.first;
//            float currentEnergy = i.second;
//            std::set<Label> *neighbors = currentNode.neighbors;
//            
//            // treat boundary nodes as another neighbor
//            long numOutbound = neighbors->size();
//            // AHHHHHHH HOW TO DETECT BOUNDARY
//            // LOOKUP: WHY DOES A BALL BOUNCE? (PHYSICS) (elasticity)
//            
//            
//            float distributedEnergy = currentEnergy / numOutbound;
//            for (auto target : *neighbors) {
//                currentEnergyLocs[target] += distributedEnergy;
//                // note: this will explode with feedback loops.
//                // also next loop this will just go back to the parent
//                // ERRRRRRRR NO ENERGY HAS A DIRECTION AHHHHHH
//                // what if we jsut let that happen lol.
//                // some input energy will be lost??
//            }
//            // all the energy has left.
//            // Note, that if we ever decide to parallelize this,
//            // this will not be correct.
//            currentEnergyLocs.erase(i.first);
//        }
//    }
//    
//    return finalEnergyLocs;
//}

