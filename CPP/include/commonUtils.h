#ifndef COMMON_UTILS_H_
#define COMMON_UTILS_H_

#include <string>
#include <iostream>

using namespace std;

int padString(string *str, const size_t padLength, const char padChar)
{
  int retCode = 0;
  size_t padLeftAmt;
  if (padLength > str->size())
  {
    padLeftAmt = ((padLength - str->size())/2);
    str->insert(0, padLeftAmt, padChar);
    str->insert(str->size(), (padLength - str->size()), padChar);
  }
  else
  {
    retCode = -1;
  }
  return retCode;
}

#endif
