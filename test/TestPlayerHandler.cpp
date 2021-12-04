/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <fstream>

#include "PlayerHandler.h"
#include "Game.h"
#include "InteractHelper.h"
#include "Room.h"
#include "Door.h"
#include "Globals.h"
#include "gtest/gtest.h"

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
  Game* game = new Game();
  InteractHelper::game = game;
  PlayerHandler* ph = InteractHelper::getPlayerHandler();
  Room* r1 = new Room("Boiler room", "It is swelteringly hot and humid.");
  Room* r2 = new Room("Liminal Void", "A space between time and dimensions.");
  Object* o1 = new Object("Crescent Wrench", "For tightening bolts.");
  Object* o2 = new Object("Box of Boilery Stuff", "All sorts of things in it.");
  Object* o3 = new Object("Apple", "It has a bite taken out of it. Gross!");
  NPC* n1 = new NPC("Test NPC", "He likes to test things.");
  NPC* n2 = new NPC("Joe", "It's Joe!");
  n1->moveNPC(r1);
  n2->moveNPC(r2);
  game->addNPC(n1);
  game->addNPC(n2);
  game->getMap()->addRoom(r1);
  game->getMap()->addRoom(r2);

  r1->getRoomObjects()->addObject(o1);
  r1->getRoomObjects()->addObject(o2);
  r1->getRoomObjects()->addObject(o3);

  ph->getPlayer()->setCurrentRoom(r1);
  ph->look();
  ph->examine("crescent wrench");
  ph->examine("box of boilery stuff");
  ph->examine("    apple  ");
  std::cout << "Next one should be 'You cannot find that here.'" << std::endl;
  ph->examine("Croissant Wrench");
  ph->examine(n1);
  ph->examine(n2);

  delete game;
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

TEST(TestPlayerHandler, inputTest) {
  Game* game = new Game();
  InteractHelper::game = game;
  InteractHelper::chapter = 0;
  Room* r1 = new Room("Boiler room", "Hot and steamy!");
  Room* r2 = new Room("Illegal Whitespace", "It's nothing but white.");
  Door* d1 = new Door(r1, r2);
  Object* o1 = new Object("Apple", "It's an apple.", true);
  Object* o2 = new Object("Orange", "It's an orange.", true);
  Object* o3 = new Object("Neutron Star", "Why is this here?", false);
  PlayerHandler* ph = InteractHelper::getPlayerHandler();
  NPC* n1 = new NPC("Test NPC", "He likes to test things.");
  n1->moveNPC(r1);
  game->getMap()->addRoom(r1);
  game->getMap()->addRoom(r2);
  game->getMap()->addDoor(d1);
  game->addNPC(n1);

  r1->changeDoor(d1, Globals::Direction::NORTH);
  r2->changeDoor(d1, Globals::Direction::SOUTH);
  r1->getRoomObjects()->addObject(o1);
  r1->getRoomObjects()->addObject(o2);
  r1->getRoomObjects()->addObject(o3);
  ph->getPlayer()->setCurrentRoom(r1);

  std::ifstream file("test/text/inputTest_pickup.txt");
  EXPECT_EQ(r1->getRoomObjects()->size(), 3);
  EXPECT_TRUE(ph->input(file));
  EXPECT_EQ(r1->getRoomObjects()->size(), 2);
  EXPECT_TRUE(ph->input(file));
  EXPECT_EQ(r1->getRoomObjects()->size(), 1);
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_EQ(r1->getRoomObjects()->size(), 1);
  file.close();

  file.open("test/text/inputTest_drop.txt");
  EXPECT_TRUE(ph->input(file));
  EXPECT_EQ(r1->getRoomObjects()->size(), 2);
  EXPECT_TRUE(ph->input(file));
  EXPECT_EQ(r1->getRoomObjects()->size(), 3);
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  file.close();

  file.open("test/text/inputTest_talk.txt");
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  file.close();

  file.open("test/text/inputTest_interact.txt");
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  ph->input(file);
  EXPECT_FALSE(ph->input(file));
  file.close();

  file.open("test/text/inputTest_ask.txt");
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  file.close();

  file.open("test/text/inputTest_stab.txt");
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  file.close();

  file.open("test/text/inputTest_move.txt");
  EXPECT_TRUE(ph->input(file));
  EXPECT_EQ(ph->getPlayer()->getCurrentRoom(), r2);
  EXPECT_TRUE(ph->input(file));
  EXPECT_EQ(ph->getPlayer()->getCurrentRoom(), r1);
  EXPECT_TRUE(ph->input(file));
  EXPECT_EQ(ph->getPlayer()->getCurrentRoom(), r2);
  EXPECT_TRUE(ph->input(file));
  EXPECT_EQ(ph->getPlayer()->getCurrentRoom(), r1);
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_EQ(ph->getPlayer()->getCurrentRoom(), r1);
  file.close();

  // Add apple back to inventory for bag/examine testing
  ph->pickUp("apple");

  file.open("test/text/inputTest_examine.txt");
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  d1->blockDoor("Closed for testing purposes.");
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  file.close();

  file.open("test/text/inputTest_misc.txt");
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  // drop apple for bag coverage.
  ph->drop("apple");
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  EXPECT_FALSE(ph->input(file));
  file.close();

  delete game;
}
