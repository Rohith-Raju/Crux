//
// Created by Rohith on 1/8/24.
//

#ifndef CRUX_ERROR_H
#define CRUX_ERROR_H

#include <string>
#include "Token.h"

namespace crux {

    extern bool hasError;

    void report(int line, std::string_view where, std::string_view message);

    void error(Token &token, std::string_view message);

    void error(int line, std::string_view message);
}
#endif //CRUX_ERROR_H
