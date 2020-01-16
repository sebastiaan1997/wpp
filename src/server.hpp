#ifndef WPP_SERVER_HPP
#define WPP_SERVER_HPP
#include <string>
#include <vector>


#include "route.hpp"
#include "definitions.hpp"
namespace WPP {
    /**
     * @brief Server class
     */
    class Server {
    public:
        Server();
        ~Server();


        void get(std::string, callbackType);

        void post(std::string, callbackType);

        void all(std::string, callbackType);

        void get(std::string, std::string);

        void post(std::string, std::string);

        void all(std::string, std::string);

        bool start(unsigned int, std::string);

        bool start(unsigned int);

        bool start();

        bool start_async();

        bool start_async(unsigned int);

        bool start_async(unsigned int, std::string);




        bool is_running() const noexcept;

        std::optional<unsigned int> port() const noexcept;
    private:
        unsigned int _port;
        int _socket;

        std::unordered_map<std::string, Route> _routes;
        void *main_loop(unsigned int);
        void parse_headers(char*, Request &, Response &);
        bool match_route(Request &, Response &);
        std::string trim(std::string);
        void split(std::string, std::string, int, std::vector<std::string> *);


    };
}
#endif //WPP_SERVER_HPP
