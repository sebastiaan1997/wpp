//
// Created by sebas on 1/15/20.
//

#ifndef WPP_ROUTE_HPP
#define WPP_ROUTE_HPP
#include "definitions.hpp"
#include "method.hpp"

namespace WPP {
    struct Route {
        std::string path;
        Method method;
        callbackType callback;
        std::string params;
    };
}

#endif //WPP_ROUTE_HPP
