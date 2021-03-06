#ifndef WPP_DEFINITIONS_HPP
#define WPP_DEFINITIONS_HPP

#include <functional>



namespace WPP {
    class Request;
    class Response;

    constexpr std::string_view server_name = "Web++";
    constexpr std::string_view server_version = "1.0.1";
    constexpr std::size_t bufsize = 8096;

    using callbackType = std::function<void(Request&, Response&)>;


}
#endif //WPP_DEFINITIONS_HPP
