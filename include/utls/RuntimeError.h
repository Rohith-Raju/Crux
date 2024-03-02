//
// Created by Rohith on 2/21/24.
//

#ifndef CRUX_RUNTIMEERROR_H
#define CRUX_RUNTIMEERROR_H

#include "Token.h"
#include <stdexcept>

class RuntimeError : public std::runtime_error {
public:
  const Token &token;

  RuntimeError(const Token &token, std::string_view message)
      : std::runtime_error{message.data()}, token{token} {}
};

#endif // CRUX_RUNTIMEERROR_H
