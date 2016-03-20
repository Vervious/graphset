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
    std::set<std::pair<Label, float>> finalEnergyLocations;
    return finalEnergyLocations;
}

