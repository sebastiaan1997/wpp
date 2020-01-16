//
// Created by sebas on 1/15/20.
//

#ifndef WPP_REQUEST_HPP
#define WPP_REQUEST_HPP
#include <string>
#include <unordered_map>

#include "route.hpp"

namespace WPP{
    class Request {
    private:

    public:
        Request() { }
        WPP::Method method;
        std::string path;
        std::string params;
        std::unordered_map<std::string, std::string> headers;
        std::unordered_map<std::string, std::string> query;
        std::unordered_map<std::string, std::string> cookies;



    };
}
#endif //WPP_REQUEST_HPP
