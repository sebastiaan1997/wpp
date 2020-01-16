#include "method.hpp"

std::ostream& operator << (std::ostream& lhs, WPP::Method rhs) {
    switch (rhs) {
        case WPP::Method::get:
            lhs << "get";
            break;
        case WPP::Method::post:
            lhs << "post";
            break;
        case WPP::Method::all:
            lhs << "all";
            break;
        default:
            lhs << "[[No Representation for method]]";
    }
    return lhs;
}