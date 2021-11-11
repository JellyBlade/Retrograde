/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include "TextHelper.h"


void TextHelper::readFile(std::string textPath) {
  // TODO(hipt2720): Implement.
  return;
}

void TextHelper::commandProcessor(std::string command) {
  // TODO(hipt2720): Implement.
  return;
}

std::string TextHelper::tolower(std::string s) {
  if (s.size() <= 0 ) { return ""; }
  for (auto& c : s) {
    c = std::tolower(c);
  }
  return s;
}

std::string TextHelper::toupper(std::string s) {
  if (s.size() <= 0 ) { return ""; }
  for (auto& c : s) {
    c = std::toupper(c);
  }
  return s;
}

std::string TextHelper::trim(std::string s) {
  if (s.size() <= 0 ) { return ""; }
  s.erase(0, s.find_first_not_of(" \t\r\n"));
  s.erase(s.find_last_not_of(" \t\r\n") + 1, s.size() - 1);
  return s;
}

std::string TextHelper::trimAll(std::string s) {
  if (s.size() <= 0 ) { return ""; }
  s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
  return s;
}
