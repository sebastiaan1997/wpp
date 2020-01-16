#ifndef WPP_EXCEPTION_HPP
#define WPP_EXCEPTION_HPP
#include <exception>
namespace WPP {
    class Exception : public std::exception {
        public:
            Exception() : pMessage("") {}
            Exception(const char* pStr) : pMessage(pStr) {}
            const char* what() const throw () { return pMessage; }
        private:
            const char* pMessage;
            //        const int pCode;
    };
}
#endif //WPP_EXCEPTION_HPP
