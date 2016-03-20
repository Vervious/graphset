//
//  main.cpp
//  chatbot1
//
//  Created by Benjamin Y Chan on 2/4/16.
//  Copyright © 2016 vervious. All rights reserved.
//

#include <iostream>
#include <string>
#include <ctime>
#include "vv_chatbot_nexus.hpp"
#include "vv_booleanfunctionlearning_nexus.hpp"
#include "random_helper.hpp"

void blockAndRunPresetResponseBot() {
    std::string Response[] = {
        "I heard you!",
        "This is a test response.",
        "All ears bro",
        "Drop a ball on the ceiling and you will make a hole in it.",
        "Test number 6."
    };

    // seed a random number
    srand((unsigned) time(NULL));
    std::string sInput = "";
    std::string sResponse = "";

    // run loop
    while (true) {
        // wait for input
        std::cout << ">";
        std::getline(std::cin, sInput);

        // pick a random message and display it
        int nSelection = rand() % 5;
        sResponse = Response[nSelection];
        std::cout << sResponse << std::endl;
    }
}

void blockAndRunChatBot() {
    // input output storage
    std::string sInput = "";
    std::string sResponse = "";
    
    // instantiate the brain
    ChatbotNexus chatbotNexus;
    
    // run loop
    while (true) {
        // wait for input
        std::cout << "> ";
        std::getline(std::cin, sInput);
        
        sResponse = chatbotNexus.observeAndReact(sInput);
        std::cout << sResponse << std::endl;
    }
}

void blockAndRunClassifierBotWithNexus(BooleanFunctionLearningNexus* boolNexus) {
    std::string sInput = "";
    bool bResponse = false;
    
    while (true) {
        // wait for input
        std::cout << "> ";
        std::getline(std::cin, sInput);
        bResponse = boolNexus->classifyInput(sInput);
        std::cout << bResponse << std::endl;
        std::cout << "ok(y/n)? > ";
        std::getline(std::cin, sInput);
        if (sInput == "n" || sInput == "N") {
            std::cout << boolNexus->acknowledgeMistake() << std::endl;
        }
    }
}

void blockAndRunClassifierBot() {
    BooleanFunctionLearningNexus boolNexus;
    blockAndRunClassifierBotWithNexus(&boolNexus);
}

void autoRunClassifierBotWithEvenFunction(BooleanFunctionLearningNexus* boolNexus, int iterationCount=100) {
    // train the boolean bot to recognize even/odd function
    // #todo: should this be just the same thing as a
    // infinitely-kerneled perceptron?
    // A simple classifier.
    
    RandomHelper randomHelper(10, 0);
    unsigned long long int anonce;
    bool classification;
    
    int mistakeCount = 0;

    // train on 100 inputs.
    // How long does it take to converge?
    // (It can never observe complete granularity...)
    // (especially in a non-finite universe)
    // (but this universe is quite finite)
    // #todo: Prove that this can resonate 100%. Since
    //        the universe is finite. Also prove bounds on
    //        how long it will take (despie probabilistic)
    for (int i = 0; i < iterationCount; i++) {
        // generate a random number
        anonce = randomHelper.rand_nonce();
        classification = false;
        if (anonce % 2 == 0) {
            classification = true;
        }
        if (boolNexus->classifyInput(std::to_string(anonce)) != classification) {
            boolNexus->acknowledgeMistake();
            mistakeCount += 1;
        }
    }
    std::cout << "mistakes! " << mistakeCount << std::endl;
}

void trainAndRunClassifierBotForEvenFunction() {
    // typical machine learning paradigm.
    // Except now, based on number of iterations, we should
    // know how much the bot already resonates.
    BooleanFunctionLearningNexus boolNexus;
    autoRunClassifierBotWithEvenFunction(&boolNexus);
    blockAndRunClassifierBotWithNexus(&boolNexus);
}

int main(int argc, const char * argv[]) {
    trainAndRunClassifierBotForEvenFunction();
    return 0;
}
