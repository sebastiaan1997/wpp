//
// Created by sebas on 1/15/20.
//

#ifndef WPP_METHOD_HPP
#define WPP_METHOD_HPP
#include <ostream>
namespace WPP {

    enum class Method {
        get,
        post,
        all
    };
}

std::ostream& operator << (std::ostream& rhs, WPP::Method lhs);


#endif //WPP_METHOD_HPP
