/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "ObjectContainer.h"
using namespace std;

ObjectContainer::~ObjectContainer(){
  for (Object* o : objects) {
    delete o;
  }
}

int ObjectContainer::size(){
  return objects.size();
}

void ObjectContainer::clear() {
  /*
  TODO(mart2720): This is to deallocate the memory before all the
  objects are cleared. Clearing does not deallocate the
  memory(search it on google), this may cause seg fault since destructor
  might do this too.  Just a possibility, watch for seg fault.
  */
  for (Object* o : objects) {
    delete o;
  }
  objects.clear();
}

void ObjectContainer::addObject(Object* object) {
  objects.push_back(object);
}

void ObjectContainer::removeObject(Object* object) {
  /*
  TODO:(mart2720) This should be here however we do not have a exceptions.h yet
  if(object == nullptr)
    throw invalid_parameter_error("Null pointer passed");
  */
  vector<Object*>::iterator it = find(objects.begin(), objects.end(), object);
  if (it != objects.end()) {
    delete (*it);
    swap((*it), objects.back());
    objects.pop_back();
  }
}

Object* ObjectContainer::getObject(string objectName) {
  for (int i = 0; i < objects.size(); i++) {
    if (objects.at(i)->getName() == objectName)
      return objects.at(i);
  }
  return nullptr;
}

vector<Object*> ObjectContainer::getObjects() {
  return objects;
}

bool ObjectContainer::isObjectInContainer(Object* object) {
  vector<Object*>::iterator it = find(objects.begin(), objects.end(), object);
  if (it != objects.end())
    return true;
  else
    return false;
}

bool ObjectContainer::isObjectInContainer(string objectName) {
  for (int i = 0; i < objects.size(); i++) {
    if (objects.at(i)->getName() == objectName)
      return true;
  }
  return false;
}
