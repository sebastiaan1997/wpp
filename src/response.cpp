#include "response.hpp"


WPP::Response::Response(): code(StatusCode::ok), phrase("OK"), type("text/html") {
    body << "";
    // set current date and time for "Date: " header
    char buffer[100];
    time_t now = time(0);
    struct tm tstruct = *gmtime(&now);
    strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S %Z", &tstruct);
    date = buffer;
}

