//
//  vv_knowledge_nexus.cpp
//  chatbot1
//
//  Created by Benjamin Y Chan on 2/4/16.
//  Copyright © 2016 vervious. All rights reserved.
//

#include "vv_knowledge_nexus.hpp"

// constructor
KnowledgeNexus::KnowledgeNexus() {
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

// public static methods
static Relationship makeRelationshipBetweenNodes(Node nodeA, Node nodeB) {
    return std::make_pair(nodeA, nodeB);
}

static Node nodeForString(std::string aString) {
    return (Node) aString;
}

// helper methods

int KnowledgeNexus::intForNodeCreatingNodeIfNeeded(Node givenNode) {
    // check if the node is in our map
    std::map<Node, int>::iterator i = this->nodeToInt.find(givenNode);
    if (i == this->nodeToInt.end()) {
        // not found. Create and add to mapp and knowledgeRep
        int returnVal = this->nextInt;
        this->nodeToInt[givenNode] = returnVal;
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
