//
//  vv_graphset.cpp
//  chatbot1
//
//  Created by Benjamin Y Chan on 2/19/16.
//  Copyright © 2016 vervious. All rights reserved.
//

#include "vv_graphset.hpp"
#include <map>

// a bidirectional adjacency list
std::map<Label, std::set<Label>> backingStructure;
// lookup a graphset by composition
std::map<Label, std::set<Label>> graphSetForCompositionLabel;

// for lookup via composition
Label compositionLabelForNeighbors(std::set<Label> neighbors) {
    // order the set into a vector
    std::vector<Label> orderedSet(neighbors.begin(), neighbors.end());
    std::sort(orderedSet.begin(), orderedSet.end());
    Label compositionLabel = "";
    for(auto f : orderedSet) {
        compositionLabel += f;
        compositionLabel += "@"; // a delimiter
    }
    return compositionLabel;
}

void VVGraphSet::printStructure() {
    
}

// constructor/conversion
VVGraphSet::VVGraphSet(Label label) {
    std::set<Label> neighbors = backingStructure[label];
    this->stringLabel = label;
    this->neighbors = &neighbors;
    // note, creating a new graphset does not create a composition label
}

// create/get a graphset interface representing a set of graphsets. Not necessarily unique (the only one), may return one of many options.
VVGraphSet VVGraphSet::Abstraction(std::set<Label> sets) {
    Label compositionlabel = compositionLabelForNeighbors(sets);
    std::set<Label> matchingGraphSets = graphSetForCompositionLabel[compositionlabel];
    if (matchingGraphSets.size() > 0) {
        // one exists already! Just take the first.
        return VVGraphSet(*matchingGraphSets.begin());
    }
    // else, construct new abstraction.
    VVGraphSet returnSet = VVGraphSet(compositionlabel);
    if (returnSet.neighbors->size() == 0) {
        // the relationships need to be instantiated
        for (auto neighbor : sets) {
            returnSet.addChild(neighbor);
        }
    }
    return returnSet;
}

// update the cached composition label and the backing store
// appropriately
void VVGraphSet::updateCompositionLabel() {
    graphSetForCompositionLabel[neighborCompositionLabel].erase(this->stringLabel);
    this->neighborCompositionLabel = compositionLabelForNeighbors(*this->neighbors);
    graphSetForCompositionLabel[neighborCompositionLabel].insert(this->stringLabel);
}


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

void VVGraphSet::relateGraphSets(VVGraphSet *g1, VVGraphSet *g2) {
    // this propogates to the global map
    g1->neighbors->insert(g2->getLabel());
    // should probably make an addParent method at some point instead
    g2->neighbors->insert(g1->getLabel());
    // update composition labels
    g1->updateCompositionLabel();
    g2->updateCompositionLabel();
}

void VVGraphSet::delateGraphSets(VVGraphSet *g1, VVGraphSet *g2) {
    g1->neighbors->erase(g2->getLabel());
    g2->neighbors->erase(g1->getLabel());
    // update composition labels
    g1->updateCompositionLabel();
    g2->updateCompositionLabel();
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

/*==========================================*\
*  SIMULATION                                *
*  See header file for theoretical concerns. *
\*==========================================*/

std::set<std::pair<Label, float>> VVGraphSet::simulateBehavior(std::set<std::pair<Label, float>> inputEnergy) {
    // inputEnergy should be in boundaryNodes. We should check this
    // in a future version. #HACKLYFE
    // if there are multiple boundary nodes, some energy might escape
    // there sooner than others. Some nodes may exude energy multiple
    // times per simulation. We need a callback? How do we deal with
    // time? We could just attach an input/output time encoder/decoder
    // but that would yield a much larger network.
    // #todo time<->space tradeoff. Formalize. But our input/output
    //       is probably going to be in the time domain already.
    //       why even convert? (it's easier to code)
    
    // TEMPORARY: Only support the sum over time of energy leaving the
    // system. Should be ok at least for boolearning.
    // Will loop forever if energy gets trapped. #todo fix this.
    
    std::map<Label, float> currentEnergyLocs;
    std::set<std::pair<Label, float>> finalEnergyLocs;
    for (auto energyInput : inputEnergy) {
        currentEnergyLocs[energyInput.first] = energyInput.second;
    }
    
    // now, loop until "convergence"
    while (currentEnergyLocs.size() > 0) {
        // when energy encounters a fork, which way does it go?
        // please don't tell me that weights are necessary here.
        // What does it mean for two nodes to be connected to a third?
        // they share a relationship. An abstraction. They are reduced
        // to equality under parentship. What if we just assume
        // that everyone gets a fair share? Errrrr. All neighbors
        // are the same. Otherwise they wouldn't share the same
        // relationship. Right? (I'm not convinced) #todo formalize
        // #todo: would adding weights simplify the number
        //        of computations that you'd have to make?
        // (why not weights? My head doesn't explicitly give certain
        //  thoughts more weight... otherwise they'd be lost?)
        for (auto i : currentEnergyLocs) {
            // don't instantiate a new graphset every time
            // just to save some memory #prematureOptimization?
            VVGraphSet currentNode = i.first;
            float currentEnergy = i.second;
            std::set<Label> *neighbors = currentNode.neighbors;
            
            // treat boundary nodes as another neighbor
            long numOutbound = neighbors->size();
            // AHHHHHHH HOW TO DETECT BOUNDARY
            
            
            float distributedEnergy = currentEnergy / numOutbound;
            for (auto target : *neighbors) {
                currentEnergyLocs[target] += distributedEnergy;
                // note: this will explode with feedback loops.
                // also next loop this will just go back to the parent
                // ERRRRRRRR NO ENERGY HAS A DIRECTION AHHHHHH
            }
            // all the energy has left.
            // Note, that if we ever decide to parallelize this,
            // this will not be correct.
            currentEnergyLocs.erase(i.first);
        }
    }
    
    return finalEnergyLocs;
}

