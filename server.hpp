#ifndef WPP_SERVER_HPP
#define WPP_SERVER_HPP
#include <string>
#include <vector>


#include "route.hpp"
#include "definitions.hpp"
namespace WPP {


    class Server {
    public:
        void get(std::string, callbackType);

        void post(std::string, callbackType);

        void all(std::string, callbackType);

        void get(std::string, std::string);

        void post(std::string, std::string);

        void all(std::string, std::string);

        bool start(unsigned int, std::string);

        bool start(unsigned int);

        bool start();

    private:
        std::vector<Route> _routes;


        void *main_loop(void *);

        void parse_headers(char *, Request &, Response &);

        bool match_route(Request &, Response &);

        std::string trim(std::string);

        void split(std::string, std::string, int, std::vector<std::string> *);
    };
}
#endif //WPP_SERVER_HPP
