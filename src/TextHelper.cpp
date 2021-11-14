/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

#include "TextHelper.h"


void TextHelper::readFile(std::string textPath) {
  // TODO(hipt2720): Implement.
  return;
}

void TextHelper::commandProcessor(std::string command) {
  // TODO(hipt2720): Implement.
  return;
}

std::string TextHelper::makePercent(int i) {
  std::string s = std::to_string(i);
  if (i < 100) {
    s.insert(s.begin(), '0');
  }
  if (i < 10) {
    s.insert(s.begin(), '0');
  }
  s.insert(s.end() - 2, '.');
  return s + "%";
}

std::string TextHelper::listObjects(std::vector<Object*> objects) {
  std::string s = "";
  switch (objects.size()) {
    case 0:
      s = " it is empty.";
      return s;
    case 1:
      s = startsWithVowel(objects[0]->getName()) ? " an " : " a ";
      s += objects[0]->getName() + ".";
      return s;
    default:
      for (Object* o : objects) {
        if (o == objects.back()) {
          s += startsWithVowel(o->getName()) ? " and an " : " and a ";
          s += o->getName() + ".";
          continue;
        }
        s += startsWithVowel(o->getName()) ? " an " : " a ";
        s += o->getName() + ",";
      }
      return s;
  }
}

bool TextHelper::startsWithVowel(std::string s) {
  char c = tolower(trim(s))[0];
  return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
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
