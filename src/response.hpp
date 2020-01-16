//
// Created by sebas on 1/15/20.
//

#ifndef WPP_RESPONSE_HPP
#define WPP_RESPONSE_HPP

#include <string>
#include <sstream>
#include <type_traits>

#include "status_codes.hpp"


namespace WPP {
    class Response {
            public:
            Response();


            StatusCode code;
            std::string phrase;
            std::string type;
            std::string date;
            std::stringstream body;



            template<typename T>
            void send(T str) {
                body << str;
            };


            private:
    };

    template<typename T>
    std::stringstream& operator << (Response& lhs, T rhs) {
        lhs.body << rhs;
        return lhs.body;
    }

}
#endif //WPP_RESPONSE_HPP
