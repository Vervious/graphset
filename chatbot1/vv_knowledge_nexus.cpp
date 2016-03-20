//
//  vv_knowledge_nexus.cpp
//  chatbot1
//
//  Created by Benjamin Y Chan on 2/4/16.
//  Copyright © 2016 vervious. All rights reserved.
//

#include "vv_knowledge_nexus.hpp"
#include "vv_utilities.hpp"
#include <iostream>

// constructor
KnowledgeNexus::KnowledgeNexus() {
}

// main introduction method
std::vector<Node> KnowledgeNexus::closestMatchNodesForInputEnergy(std::string information) {
    // this is a little deterministic. At first, probably just one node match.
    // as the system adds more information, there is a better match for nodes.
    
    std::vector<Node> inputNodes;
    
    // Let's keep the most granularity possible at an ordered list of individual words
    // this is the most powerful the closest match nodes can be.
    // Why not just hard code the best possible closest match nodes?
    // IDK. Just to experiment, with the information gain mechanism.
    std::vector<std::string> words = utility::split(information, ' ');
    
    for (auto &i : words) {
        std::cout << "Debug Message: " << i << std::endl;
        // should we automatically add new information or words for every new node???
        // ^ create the mechanism for this!!!
        // ^ this is an amalgation of various items of disrepair
        Relationship newRel = this->aRelationshipBetweenNodes("A", "B");
        this->createRelationship(newRel);
    }
    
    return inputNodes;
}

// main propogation method
std::vector<Node> KnowledgeNexus::outputForEnergyInput(std::vector<Node> inputEnergy) {
    std::vector<Node> outputEnergy;
    
    // alright, propogate energy. Note that this does not terminate with loops (think about it!!) #todo...
    for (auto const& node : inputEnergy) {
        int nodeInt = this->intForNodeCreatingNodeIfNeeded(node);
        
        // my energy vector
        std::set<int> myEnergyVector = this->intNodeToEnergyVector[nodeInt].second;
        // there's a discrepancy between the input and output energy vectors by design, so
        // we need to make an update step.
        std::set<int> myOutputEnergyVector;

        // a node doesn't do anything except pass on its energy
        std::set<Node> children = this->connectionsToNode(node);

        // for each connected node.
        for (auto const& child: children) {
            // add the vector energy as appropriate
            
            // energy vector is currently (presence of energy, source)
            int childInt = this->intForNodeCreatingNodeIfNeeded(child);
            std::set<int> childEnergyVector = this->intNodeToEnergyVector[childInt].second;
            const bool is_in = childEnergyVector.find(nodeInt) != childEnergyVector.end();
            if (is_in) {
                // remove us. If childEnergyVector has size one, set scalar to 0.
                childEnergyVector.erase(nodeInt);
                if (childEnergyVector.size() < 1) {
                    this->intNodeToEnergyVector[childInt].first = 0;
                }
            } else {
                // add us. Set scalar to one. Hopefully this sets by reference... #tocheck
                childEnergyVector.insert(nodeInt);
                this->intNodeToEnergyVector[childInt].first = 1;
            }
            
            this->intNodeToEnergyVector[childInt] = std::make_pair(1, childEnergyVector);
            
            // update our own energy vector, to match the output energy.
            myOutputEnergyVector.insert(childInt);
        }
        
        // note that our energy is turned off by a reaction from a child node.
        this->intNodeToEnergyVector[nodeInt].second = myOutputEnergyVector;
    }
    
    // now iterate through all nodes with positive energy, and return
    for(auto const &energyVectorKeyValue : this->intNodeToEnergyVector) {
        if (energyVectorKeyValue.second.first > 0) {
            outputEnergy.push_back(this->intToNode[energyVectorKeyValue.first]);
        }
    }
    return outputEnergy;
}

// public methods
void KnowledgeNexus::createRelationship(Relationship rel) {
    int nodeA = this->intForNodeCreatingNodeIfNeeded(rel.first);
    int nodeB = this->intForNodeCreatingNodeIfNeeded(rel.second);
    // check if the relationship exists already
    std::set<int>::iterator i = this->knowledgeRep[nodeA].find(nodeB);
    if (i == this->knowledgeRep[nodeA].end()) {
        // not found. Add to knowledge rep.
        this->knowledgeRep[nodeA].insert(nodeB);
        this->knowledgeRep[nodeB].insert(nodeA);
    }
    else {
        // found, no need to do anything
    }
}

void KnowledgeNexus::destroyRelationship(Relationship rel) {
    int nodeA = this->intForNodeCreatingNodeIfNeeded(rel.first);
    int nodeB = this->intForNodeCreatingNodeIfNeeded(rel.second);
    this->knowledgeRep[nodeA].erase(nodeB);
    this->knowledgeRep[nodeB].erase(nodeA);
}

//// public static methods
Relationship KnowledgeNexus::aRelationshipBetweenNodes(Node nodeA, Node nodeB) {
    return std::make_pair(nodeA, nodeB);
}

Node KnowledgeNexus::nodeForString(std::string aString) {
    return (Node) aString;
}

// helper methods

// when reflecting: #todo: why are we using nodes as the base graph
// for information? Why a graph? Why not bits and things? What's elementary about this?
// WTF are connections? Are they not sort of arbitrary.
//    here's some intuition
//    you have some space
//        assumption: not everything is in the spot in this space
//        some things are closer to each other than others
//        hence information, and connections between nodes.
//        space can be abstracted away into various less "space-like" dimensions, by the graph
std::set<Node> KnowledgeNexus::connectionsToNode(Node node) {
    std::set<Node> outgoingConnections;
    int nodeId = this->intForNodeCreatingNodeIfNeeded(node);
    std::set<int> connections = this->knowledgeRep[nodeId];
    for (auto const& nId : connections) {
        Node realNode = this->intToNode[nId];
        outgoingConnections.insert(realNode);
    }
    return outgoingConnections;
}

int KnowledgeNexus::intForNodeCreatingNodeIfNeeded(Node givenNode) {
    // check if the node is in our map
    std::map<Node, int>::iterator i = this->nodeToInt.find(givenNode);
    if (i == this->nodeToInt.end()) {
        // not found. Create and add to mapp and knowledgeRep
        int returnVal = this->nextInt;
        this->nodeToInt[givenNode] = returnVal;
        this->intToNode[returnVal] = givenNode;
        this->nextInt++;
        // insert it into the knowledge rep
        std::set<int> emptySet;
        this->knowledgeRep.push_back(emptySet);
        return returnVal;
    } else {
        return i->second;
    }
}

std::string KnowledgeNexus::printString() {
    return "This is a printed version of the string";
}
