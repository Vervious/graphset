//
//  vv_graphset.hpp
//  chatbot1
//
//  Created by Benjamin Y Chan on 2/19/16.
//  Copyright © 2016 vervious. All rights reserved.
//
//  Note that the graphset is simply an extension of a
//  probability distribution, with discrete events;
//  if taken to the limit, it becomes a continuous distribution.
//  * Clearly, what we then need is a way to compare
//    discrete and continuous entropy measures
//    (or abstractions with something else)
//
//  Key, intuitive visualizations:
//  * energy: location of a particle.
//  * node: a subspace, or event space. 3D Rectangle.
//  * Abstraction: when a system doesn't know enough to
//    use the full granularity of an object, but the object
//    item exists (e.g. I know that if I turn on a computer,
//    it turns on, but not necessarily what the button did, or
//    all those little details.)
//      - The abstraction event space is strictly greater than
//        any singular instance of its more granular form.

#ifndef vv_graphset_hpp
#define vv_graphset_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <set>

typedef std::string Label;

// represents a graph set.
// a graph set defines relationships between its content nodes.
// So far we enforce the fact that all nodes must be connected.
//
// note that the hierarchy can be collapsed by further defining a relationship
// "member" as simply being another connection in the flat graph.
// in that sense, the relationship flat graph is the more general form of this.
// In set theory, we can equate the braces with the arrows in the flat graph.
//
// Actually, not sure if that is true. But here's an interface where
// Each graphset represents an abstraction of an object.
// A graphset can be used as an interface, representing, for instance, the "relationship between x objects"
// For each graphset, you can then add granularity, or children, and define relationships between siblings.
// (Note: If you take a set of graphsets, you then have an object without abstraction.)
// (The way you interact with a set of graphsets is to take its abstraction and define granularity on that level)
//
// This implementation of a graphset is s.t.:
//      - each graphset is responsible for defining the relationships of its children. Let's just experiment.
//      - children do not define relationship with its parent.
//      - actually strike that. Let's just keep track of neighbors.
// Think hierarchally: We could also have every node describe all neighbors, but that's less intuitive in terms
// of the abstraction mechanism.
class VVGraphSet {
private:
    // an unique label, for intuitive use. Should probably set it
    // at least on the most granular level.
    Label stringLabel;
    // In addition, graphsets are identified by composition.
    // internal rep
    std::set<Label> *neighbors;
    Label neighborCompositionLabel; // to help with identifying
    // print our structure, for debugging
    void printStructure();
    void updateCompositionLabel();
public:
    // get a graphset for the given unique label
    // Also enables implicit conversions for below methods
    // Note, VVGraphSet is simply a client to a global knowledge database (all graph sets)
    // so we won't have singleton objects.
    // A client may be out of date. Try to instantiate only one client at a time.
    VVGraphSet(Label label);
    // create/get a graphset interface representing a set of graphsets. Always unique/singleton
    static VVGraphSet Abstraction(std::set<Label>);
    
    static void relateGraphSets(VVGraphSet*, VVGraphSet*);
    static void delateGraphSets(VVGraphSet*, VVGraphSet*);
    
    // enable implicit conversion between label and graphset
    
    // Add a child graph. Can be thought of as drawing another boundary
    // bidirectional. Adds ourselves to child's children too.
    // equivalent to add neighbor
    // The way you access the interface then determines what perspective you have into the structure.
    void addChild(VVGraphSet childGraph);
    // simple deassociation
    void removeChild(VVGraphSet childGraph);
    void relateChildren(VVGraphSet child1, VVGraphSet child2);
    void delateChildren(VVGraphSet child1, VVGraphSet child2);
    
    // print current string label, and also composition of composing nodes labels
    std::string getLabel(bool composition = false);
    // relabel the current label
    void relabel(std::string newLabel);
    
    // moonshots
    // get the information content of this graph set relative to another graph set.
    // 0 if no boundaries.
    // - #todo define a metric.
    double informationContent(VVGraphSet referenceSet);
    
    
    /**
     * USING THE MODEL
     * Simulation, generating predictions
     * What is the motivation for this? Why does generating
     * a prediction maximize information resonance? (or rather,
     * entropy generation?) #todo prove, even in boolean case
     */
public:
    // should probably think about a better interface for this
    // that doesn't expose it.
    // Set of nodes that are exposed to the environment in
    // the context of the simulation, can be treated as
    // input/output nodes.
    std::set<Label> boundaryNodes;
    
    // thoughts on boundaryNodes:
    // it seems meaningful to have energy perpetually escape
    // since not very many systems (if any) are thermodynamically
    // ideal... Perhaps because of how granular the universe is,
    // and also in the brain, signals die... but theoretically
    // our model should be able ot learn that? #todo think about
    // energy dissipation and entropy (motivation)
    // We could just add boundary nodes at every node, but
    // our brain doesn't think about heat generated when abstract
    // -ing a system.
    
    // ok. Useful stuff. Simulate behavior. In an environment.
    // does energy need to be vectorized?
    // input energy merely refers to an energy differential.
    //     - Can be negative (e.g. hot object in cold water).
    // how about this: vectorized in the sense that energy is
    // either going in (+) or going out (-). Everything else
    // can be encapsulated in terms of relationships. (e.g.
    // direction a system is traveling, etc)
    // --
    // returns a converged energy state for labels on the
    // input/output boundaries specified for the graph set.
    // note: typically probably won't converge. FEedback loops
    // will maintain state. #todo: run a true simulation.
    // Here we just assume that energy doesn't get trapped and
    // that it just leaves the system, like it does a function.
    // #todo implement otherwise
    // --
    // inputEnergy must be a subset of boundaryNodes
    // #todo: how does this reduce to a turing machine? Can it?
    //        - write a reduction.
    std::set<std::pair<Label, float>> simulateBehavior(std::set<std::pair<Label, float>> inputEnergy);
    
};

#endif /* vv_graphset_hpp */
