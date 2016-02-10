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

int main(int argc, const char * argv[]) {
//    std::string Response[] = {
//        "I heard you!",
//        "This is a test response.",
//        "All ears bro",
//        "Drop a ball on the ceiling and you will make a hole in it.",
//        "Test number 6."
//    };
//    
//    // seed a random number
//    srand((unsigned) time(NULL));
//    std::string sInput = "";
//    std::string sResponse = "";
//    
//    // run loop
//    while (true) {
//        // wait for input
//        std::cout << ">";
//        std::getline(std::cin, sInput);
//        
//        // pick a random message and display it
//        int nSelection = rand() % 5;
//        sResponse = Response[nSelection];
//        std::cout << sResponse << std::endl;
//    }
    
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
    
    return 0;
}
