//
//  demo.cpp
//  Web++
//
//  Created by Alex Movsisyan
//

#include <iostream>
#include <map>

#include "src/web++.hpp"

using namespace WPP;

void web(Request& req, Response& res) {
    std::cout << req.method << " " << req.path << std::endl;

    std::cout << "Headers:" << std::endl;


    for (const auto& iter: req.headers) {
        std::cout << iter.first << " = " << iter.second << std::endl;
    }


    std::cout << "Query:" << std::endl;

    for (const auto& iter: req.query) {
        std::cout << iter.first << " = " << iter.second << std::endl;
    }


    std::cout << "Cookies: " << req.cookies.size() << std::endl;


    for(const auto& iter: req.cookies) {
        std::cout << iter.first << " = " << iter.second << std::endl;
    }
    
    res.body << "HELLO";
}

int main(int argc, const char* argv[]) {
    try {
        std::cout << "Listening on port 5000" << std::endl;
        
        WPP::Server server;
        server.get("/", &web);
        server.all("/dir", "./");
        server.start(5004);
    } catch(WPP::Exception e) {
        std::cerr << "WebServer: " << e.what() << std::endl;
    }
    
    return EXIT_SUCCESS;
}