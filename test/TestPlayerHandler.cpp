/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include "PlayerHandler.h"
#include "Room.h"
#include "Door.h"
#include "Globals.h"
#include "gtest/gtest.h"

TEST(TestPlayerHandler, DISABLED_inputTest) {
  PlayerHandler* ph = new PlayerHandler();

  ph->input();

  delete ph;
}

TEST(TestPlayerHandler, movePlayerTest) {
  Room* r1 = new Room("Boiler room", "Hot and steamy!");
  Room* r2 = new Room("Illegal Whitespace", "It's nothing but white.");
  Door* d1 = new Door(r1, r2);
  PlayerHandler* ph = new PlayerHandler();

  r1->changeDoor(d1, Globals::Direction::NORTH);
  r2->changeDoor(d1, Globals::Direction::SOUTH);

  ph->getPlayer()->setCurrentRoom(r1);
  EXPECT_EQ(ph->getPlayer()->getCurrentRoom(), r1);
  EXPECT_TRUE(ph->movePlayer(Globals::Direction::NORTH));
  EXPECT_EQ(ph->getPlayer()->getCurrentRoom(), r2);
  EXPECT_FALSE(ph->movePlayer(Globals::Direction::WEST));
  EXPECT_FALSE(ph->movePlayer(Globals::Direction::EAST));
  EXPECT_FALSE(ph->movePlayer(Globals::Direction::NORTH));

  d1->blockDoor("A large cat in an spacesuit blocks your path. Meow!");
  EXPECT_FALSE(ph->movePlayer(Globals::Direction::SOUTH));

  d1->unblockDoor();
  EXPECT_TRUE(ph->movePlayer(Globals::Direction::SOUTH));
  EXPECT_EQ(ph->getPlayer()->getCurrentRoom(), r1);

  delete r1;
  delete r2;
  delete d1;
  delete ph;
}

TEST(TestPlayerHandler, lookExamineTest) {
  Room* r1 = new Room("Boiler room", "It is swelteringly hot and humid.");
  Object* o1 = new Object("Crescent Wrench", "For tightening bolts.");
  Object* o2 = new Object("Box of Boilery Stuff", "All sorts of things in it.");
  Object* o3 = new Object("Apple", "It has a bite taken out of it. Gross!");
  PlayerHandler* ph = new PlayerHandler();

  r1->getRoomObjects()->addObject(o1);
  r1->getRoomObjects()->addObject(o2);
  r1->getRoomObjects()->addObject(o3);

  ph->getPlayer()->setCurrentRoom(r1);
  ph->look();
  ph->exame("crescent wrench");
  ph->examine("box of boilery stuff");
  ph->examine("    apple  ");
  std::cout << "---Following examinations should fail---" << std::endl;
  ph->examine(" a p p l e ");
  ph->examine("box   of   boilery    stuff");
  ph->examine("Croissant Wrench");

  delete r1;
  delete ph;
}

TEST(TestPlayerHandler, pickUpTest) {
  Room* r1 = new Room("Boiler room", "It is swelteringly hot and humid.");
  Object* o1 = new Object("Crescent Wrench", "For tightening bolts.", true);
  PlayerHandler* ph = new PlayerHandler();

  ph->getPlayer()->setCurrentRoom(r1);

  EXPECT_EQ(r1->getRoomObjects()->size(), 0);
  r1->getRoomObjects()->addObject(o1);
  EXPECT_EQ(r1->getRoomObjects()->size(), 1);
  EXPECT_FALSE(ph->pickUp("apple"));
  EXPECT_FALSE(ph->pickUp(""));

  EXPECT_EQ(ph->getPlayer()->getInventory()->size(), 0);
  EXPECT_TRUE(ph->pickUp("crescent wrench"));
  EXPECT_EQ(ph->getPlayer()->getInventory()->size(), 1);
  EXPECT_EQ(r1->getRoomObjects()->size(), 0);

  delete ph;
  delete r1;
}

TEST(TestPlayerHandler, dropTest) {
  Room* r1 = new Room("Boiler room", "It is swelteringly hot and humid.");
  Object* o1 = new Object("Crescent Wrench", "For tightening bolts.", true);
  PlayerHandler* ph = new PlayerHandler();

  ph->getPlayer()->setCurrentRoom(r1);

  EXPECT_EQ(ph->getPlayer()->getInventory()->size(), 0);
  ph->getPlayer()->getInventory()->addObject(o1);
  EXPECT_EQ(ph->getPlayer()->getInventory()->size(), 1);

  EXPECT_FALSE(ph->drop("apple"));
  EXPECT_FALSE(ph->drop("banana"));
  EXPECT_FALSE(ph->drop("barrel of monkeys"));
  EXPECT_EQ(r1->getRoomObjects()->size(), 0);
  EXPECT_TRUE(ph->drop("crescent wrench"));
  EXPECT_EQ(r1->getRoomObjects()->size(), 1);
  EXPECT_EQ(ph->getPlayer()->getInventory()->size(), 0);
  EXPECT_FALSE(ph->drop("crescent wrench"));

  delete ph;
  delete r1;
}
