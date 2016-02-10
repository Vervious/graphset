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
    std::map<Node, int> nodeToInt;
    int nextInt; // the next unused node id
    
    // get the integer corresponding to the given node
    int intForNodeCreatingNodeIfNeeded(Node);
public:
    KnowledgeNexus();
    void createRelationship(Relationship);
    void destroyRelationship(Relationship);
    static Relationship makeRelationshipBetweenNodes(Node, Node);
    static Node nodeForString(std::string);
    std::string printString();
};

#endif /* vv_knowledge_nexus_hpp */
