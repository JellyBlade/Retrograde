/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>

#include "Log.h"
#include "TextHelper.h"

Log::Log(std::string s) : textPath{s} {}

void Log::interact() {
  std::cout << "This is the filePath" << textPath << std::endl;
  TextHelper::readFile(textPath);
}
