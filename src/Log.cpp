/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>

#include "Log.h"
#include "TextHelper.h"

Log::Log(std::string n, std::string d, bool h, std::string s) {
  setName(n);
  setDescription(d);
  setHoldable(h);
  textPath = s;
}

void Log::interact() {
  TextHelper::readFile(textPath);
}
