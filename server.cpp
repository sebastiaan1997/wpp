#include <cstring>
#include <regex>
#include <netinet/in.h>
#include <fstream>
#include <sstream>
#include <unistd.h>

#include "server.hpp"

#include "request.hpp"
#include "response.hpp"

#include "list_dir.hpp"
#include "method.hpp"

#include "exception.hpp"

void WPP::Server::split(std::string str, std::string separator, int max, std::vector<std::string>* results){
    int i = 0;
    size_t found = str.find_first_of(separator);

    while(found != std::string::npos){
        if(found > 0){
            results->push_back(str.substr(0, found));
        }
        str = str.substr(found+1);
        found = str.find_first_of(separator);

        if(max > -1 && ++i == max) break;
    }

    if(str.length() > 0){
        results->push_back(str);
    }
}

std::string WPP::Server::trim(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());

    return s;
}



void WPP::Server::parse_headers(char* headers, Request& req, Response& res) {
    // Parse request headers
    int i = 0;
    char * pch;
    for (pch = strtok(headers, "\n"); pch; pch = strtok(NULL, "\n" ))
    {
        if(i++ == 0)  {
            std::vector<std::string> R;
            std::string line(pch);
            this->split(line, " ", 3, &R);

            //            cout << R.size() << endl;

            if(R.size() != 3) {
                //                throw error
            }

            if(R[0] == "get") {
                req.method = WPP::Method::get;

            }
            else if(R[0] == "post") {
                req.method = WPP::Method::post;
            }
            else{
                req.method = WPP::Method::all;
            }



            req.path = R[1];

            size_t pos = req.path.find('?');

            // We have GET params here
            if(pos != std::string::npos)  {
                std::vector<std::string> Q1;
                this->split(req.path.substr(pos + 1), "&", -1, &Q1);

                for(std::vector<std::string>::size_type q = 0; q < Q1.size(); q++) {
                    std::vector<std::string> Q2;
                    this->split(Q1[q], "=", -1, &Q2);

                    if(Q2.size() == 2) {
                        req.query[Q2[0]] = Q2[1];
                    }
                }

                req.path = req.path.substr(0, pos);
            }
        } else {
            std::vector<std::string> R;
            std::string line(pch);
            this->split(line, ": ", 2, &R);

            if(R.size() == 2) {
                req.headers[R[0]] = R[1];

                // Yeah, cookies!
                if(R[0] == "Cookie") {
                    std::vector<std::string> C1;
                    this->split(R[1], "; ", -1, &C1);

                    for(std::vector<std::string>::size_type c = 0; c < C1.size(); c++) {
                        std::vector<std::string> C2;
                        this->split(C1[c], "=", 2, &C2);

                        req.cookies[C2[0]] = C2[1];
                    }
                }
            }
        }
    }
}

void WPP::Server::get(std::string path, callbackType callback) {
    Route r = {
            path,
            Method::get,
            callback
    };

    this->_routes.push_back(r);
}

void WPP::Server::post(std::string path, callbackType callback) {
    Route r = {
            path,
            Method::post,
            callback
    };

    this->_routes.push_back(r);
}

void WPP::Server::all(std::string path, callbackType callback) {
    Route r = {
            path,
            Method::all ,
            callback
    };

    this->_routes.push_back(r);
}

void WPP::Server::get(std::string path, std::string loc) {
    Route r = {
            path,
            Method::get,
            &list_dir,
            loc
    };

    this->_routes.push_back(r);
}

void WPP::Server::post(std::string path, std::string loc) {
    Route r = {
            path,
            Method::post,
            &list_dir,
            loc
    };

    this->_routes.push_back(r);
}

void WPP::Server::all(std::string path, std::string loc) {
    Route r = {
            path,
            Method::all,
            &list_dir,
            loc
    };

    this->_routes.push_back(r);
}

bool WPP::Server::match_route(Request& req, Response& res) {
    for (std::vector<Route>::size_type i = 0; i < this->_routes.size(); i++) {
        std::regex pattern (this->_routes[i].path);
        if( regex_match(req.path, pattern) || this->_routes[i].path == req.path && (this->_routes[i].method == req.method || this->_routes[i].method == Method::all)) {
            req.params = this->_routes[i].params;
            this->_routes[i].callback(req, res);
            return true;
        }
    }

    return false;
}

void* WPP::Server::main_loop(void* arg) {
    int* port = reinterpret_cast<int*>(arg);

    int newsc;

    int sc = socket(AF_INET, SOCK_STREAM, 0);

    if (sc < 0) {
        throw WPP::Exception("ERROR opening socket");
    }

    struct sockaddr_in serv_addr, cli_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(*port);

    if (::bind(sc, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) != 0) {
        throw WPP::Exception("ERROR on binding");
    }

    listen(sc, 5);

    socklen_t clilen;
    clilen = sizeof(cli_addr);

    while(true) {
        newsc = accept(sc, (struct sockaddr *) &cli_addr, &clilen);

        if (newsc < 0) {
            throw WPP::Exception("ERROR on accept");
        }

        // handle new connection
        Request req;
        Response res;

        static char headers[bufsize + 1];
        long ret = read(newsc, headers, bufsize);
        if(ret > 0 && ret < bufsize) {
            headers[ret] = 0;
        } else {
            headers[0] = 0;
        }

        this->parse_headers(headers, req, res);

        if(!this->match_route(req, res)) {
            res.code = 404;
            res.phrase = "Not Found";
            res.type = "text/plain";
            res.send("Not found");
        }

        char header_buffer[bufsize];
        std::string body = res.body.str();
        size_t body_len = body.size();

        // build http response
        sprintf(header_buffer, "HTTP/1.0 %d %s\r\n", res.code, res.phrase.c_str());

        // append headers
        sprintf(&header_buffer[strlen(header_buffer)], "Server: %s %s\r\n", server_name, server_version);
        sprintf(&header_buffer[strlen(header_buffer)], "Date: %s\r\n", res.date.c_str());
        sprintf(&header_buffer[strlen(header_buffer)], "Content-Type: %s\r\n", res.type.c_str());
        sprintf(&header_buffer[strlen(header_buffer)], "Content-Length: %zd\r\n", body_len);

        // append extra crlf to indicate start of body
        strcat(header_buffer, "\r\n");

        ssize_t t;
        t = write(newsc, header_buffer, strlen(header_buffer));
        t = write(newsc, body.c_str(), body_len);
    }
}

bool WPP::Server::start(unsigned int port, std::string host) {
    this->main_loop(&port);
    return true;
}

bool WPP::Server::start(unsigned int port) {
    return this->start(port, "0.0.0.0");
}

bool WPP::Server::start() {
    return this->start(80u);
}