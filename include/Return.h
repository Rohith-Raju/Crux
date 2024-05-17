#include "utls/Object.h"

struct ReturnValue {
  Object value;
  ReturnValue(Object value) : value(value){};
};
