//
//  vv_chatbot_nexus.hpp
//  chatbot1
//
//  Created by Benjamin Y Chan on 2/4/16.
//  Copyright © 2016 vervious. All rights reserved.
//

#ifndef vv_chatbot_nexus_hpp
#define vv_chatbot_nexus_hpp

#include <stdio.h>
#include <string>
#include "vv_knowledge_nexus.hpp"
#include "vv_motivation_circuit.hpp"

/* 
 * Represents the information nexus
 * that is the chatbot.
 * Note division of pure "universe knowledge"
 * vs input stimulus. This is just to help us (the programmer)
 * distinguish information gained about words and language vs
 * translation.
 */
class ChatbotNexus {
private:
    KnowledgeNexus knowledgeNexus;
    MotivationCircuit motivationCircuit;
    void encodeNewInformation(std::string);
public:
    // represents the sole observation and sole action the chatbot can take
    std::string observeAndReact(std::string);
    ChatbotNexus();
};

#endif /* vv_chatbot_nexus_hpp */
