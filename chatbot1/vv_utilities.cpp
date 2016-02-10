//
//  vv_utilities.cpp
//  chatbot1
//
//  Created by Benjamin Y Chan on 2/6/16.
//  Copyright © 2016 vervious. All rights reserved.
//

#include "vv_utilities.hpp"

namespace utility
{
    // string split utils. Taken from stack overflow
    // (http://stackoverflow.com/a/236803/307881)
    std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> elems;
        utility::split(s, delim, elems);
        return elems;
    }
}
