//
//  vv_knowledge_nexus.hpp
//  chatbot1
//
//  Created by Benjamin Y Chan on 2/4/16.
//  Copyright © 2016 vervious. All rights reserved.
//

#ifndef vv_knowledge_nexus_hpp
#define vv_knowledge_nexus_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>

/* various representation definitions
 * Represents the base node type for a
 * knowledge nexus. Note that if you visualize
 * the Knowledge Nexus as a graph with nodes, and edges, here we represent
 * edges as nodes as wel... and boundaries are simply defined generically.
 */
typedef std::string Node;
typedef std::vector<std::set<int>> AdjacencyList;
typedef std::pair<Node, Node> Relationship;

/*
 * Represents an information nexus that has
 * "base knowledge elements", in this case
 * taken to be strings and relationships between strings 
 * (taken to be maybe probablistic, at least for this basic version, 
 * for the purpose of lerning C++).
 *
 * Requires a sort of traversal. How do we interpret this? (And neural signals in general?)
 * - all systems are static, in the universe, unless affected by some sort of energy
 * - a signal is simply the propogation of energy from the external universe on the system
 * - consider it a life force, or driving energy, the "input energy" 
 * - Perhaps it's just another dimension, the universe evolving through time, but lets pick 
 *      this dimension out since we sort of have to
 *
 * Other notes
 * - currently in memory, but eventually we could persist the knwoledge graph.
 * - could treat **structure like query**
 * - we store connections in a matrix of 1s and 0s. Note that an inhibition would
 *      be formed by a connection to a negative "string", such as "not".
 *      Also note that we could easily store more than 1s and 0s and eliminate the 
 *      need to connect to an inhibitory node; this may be something to look into,
 *      mathematically, in terms of information entropy and all of that.
 * - This requires more research into representation and information entropy. Is
 *      this graph system really the most simple way to represent this sort of structure
 */
class KnowledgeNexus {
private:
    // the adjacency list and map must be updated concurrently
    AdjacencyList knowledgeRep;
    
    // an ugly bimap, but boost is throwing error after another
    // at me
    std::map<Node, int> nodeToInt;
    std::map<int, Node> intToNode;
    // store an energy value for each node.
    // the vector corresponds to <energy level, direction>, where direction
    // is the source of the node(s) that it came from.
    std::map<int, std::pair<int, std::set<int>>> intNodeToEnergyVector;
    
    int nextInt; // the next unused node id
    
    // get the integer corresponding to the given node
    int intForNodeCreatingNodeIfNeeded(Node);
    std::set<Node> connectionsToNode(Node);
public:
    KnowledgeNexus();
    void createRelationship(Relationship);
    void destroyRelationship(Relationship);
    
    static Relationship aRelationshipBetweenNodes(Node, Node);
    static Node nodeForString(std::string);

    std::string printString();
    // we're treating input as energy, and output as energy, and this might modify the system.
    std::vector<Node> outputForEnergyInput(std::vector<Node>);
    
    // figure out what the input set of nodes is. Answers the question: what is the first step when arbitrary energy affects the system?
    // typically plug in the result into outputForEnergyInput
    std::vector<Node> closestMatchNodesForInputEnergy(std::string);
};

#endif /* vv_knowledge_nexus_hpp */
