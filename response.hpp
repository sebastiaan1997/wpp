//
// Created by sebas on 1/15/20.
//

#ifndef WPP_RESPONSE_HPP
#define WPP_RESPONSE_HPP

#include <string>
#include <sstream>
namespace WPP {
    class Response {
            public:
            Response() {
                code = 200;
                phrase = "OK";
                type = "text/html";
                body << "";

                // set current date and time for "Date: " header
                char buffer[100];
                time_t now = time(0);
                struct tm tstruct = *gmtime(&now);
                strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S %Z", &tstruct);
                date = buffer;
            }
            int code;
            std::string phrase;
            std::string type;
            std::string date;
            std::stringstream body;

            void send(std::string str) {
                body << str;
            };
            void send(const char* str) {
                body << str;
            };
            private:
    };

}
#endif //WPP_RESPONSE_HPP
