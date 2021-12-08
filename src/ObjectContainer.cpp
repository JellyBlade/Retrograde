/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <string>
#include <vector>
#include <algorithm>
#include "ObjectContainer.h"
#include "TextHelper.h"

ObjectContainer::~ObjectContainer() {
  for (int i = 0; i < objects.size(); i++) {
    delete objects[i];
  }
  objects.clear();
}

int ObjectContainer::size() {
  return objects.size();
}

void ObjectContainer::clear() {
  for (int i = 0; i < objects.size(); i++) {
    delete objects[i];
  }
  objects.clear();
}

void ObjectContainer::addObject(Object* object) {
  objects.push_back(object);
}

void ObjectContainer::removeObject(Object* object) {
  objects.erase(std::remove(objects.begin(), objects.end(),
   object), objects.end());
}

Object* ObjectContainer::getObject(std::string objectName) {
  for (int i = 0; i < objects.size(); i++) {
    if (TextHelper::tolower(TextHelper::trimAll(objects.at(i)->getName())) ==
    TextHelper::tolower(TextHelper::trimAll(objectName)))
      return objects.at(i);
  }
  return nullptr;
}

std::vector<Object*> ObjectContainer::getObjects() {
  return objects;
}

bool ObjectContainer::isObjectInContainer(Object* object) {
  if (std::find(objects.begin(), objects.end(), object) != objects.end()) {
    return true;
  }
  return false;
}

bool ObjectContainer::isObjectInContainer(std::string objectName) {
  for (int i = 0; i < objects.size(); i++) {
    if (TextHelper::tolower(TextHelper::trimAll(objects.at(i)->getName())) ==
    TextHelper::tolower(TextHelper::trimAll(objectName)))
      return true;
  }
  return false;
}
