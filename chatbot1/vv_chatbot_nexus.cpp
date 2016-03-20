//
//  vv_chatbot_nexus.cpp
//  chatbot1
//
//  Created by Benjamin Y Chan on 2/4/16.
//  Copyright © 2016 vervious. All rights reserved.
//

#include "vv_chatbot_nexus.hpp"
#include "vv_utilities.hpp"
#include <iostream>

// constructor
ChatbotNexus::ChatbotNexus() {
}

// should never return null
std::string ChatbotNexus::observeAndReact(std::string observation) {
    // run a simulation of the system, literally, atoms
    // call "finalNeuron(previous_neuron(text)) to perform action
    // ^ only action that is performable and affects the external
    // ^ note that self-modification can also be thought of as an action.
    // note that base atom is a string
    
    this->encodeNewInformation(observation);
    return "not implemented";
}


void ChatbotNexus::encodeNewInformation(std::string newInformation) {
    // first, parse new information into ordered list of words
    
    // from a sentence, you can derive many different types of relationships...
    // If each word is a symbol, basically every word will have a connection between them.
    // These are, however, different types of connections. The goal is to abstract this mechanism and not
    // need to hard code it. This can be done with the parallel mechanism of signalling...
    // ************
    // The question of the day: when do you start adding granularity???? (new nodes between nodes representing special relationships)
    // Answer: you add granularity when you need to encapsulate more information about the universe. It is motivated by information gravity.
    // we're sort of treating information gravity as a deus ex machina here but that's jsust for exploratory purposes.
    // ************
    // two types of algorithm:
    // - non greedy:
    //       * upon determining that the current information nexus encapsulates insufficient information, add a node
    // - greedy
    //       * add a node regardless, and cut if it is useless (provides no extra information) <--- this seems to be the neural mechanism
    //         with synaptic pruning.
    // ************
    // all of this should be "motivated" by the motivation circuit. But what is the best way to hook the
    // motivation circuit into the system? Because honestly, the motivation circuit should be part of the information nexus.
    // What does evolution of the motivation circuit look like?
    // ************
    // for now we can just hardcode a motivation circuit, as appropriate. "Hungry for information" will be a definition that changes as
    // the system gets more and more complex. Human level hungriness might not be superintelligence level motivation. For instance
    // humans have an element of curiosity that lesser creatures don't have.
    //
    // ************
    // Make sure to preserve information.
    // especially the order of words.
    // ************
    //
    std::vector<Node> inputEnergyAffectedNodes = this->knowledgeNexus.closestMatchNodesForInputEnergy(newInformation);
    std::vector<Node> nodesProducingOutputEnergy = this->knowledgeNexus.outputForEnergyInput(inputEnergyAffectedNodes);
    return;
}