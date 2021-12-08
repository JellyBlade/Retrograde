/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <string>
#include <vector>
#include <fstream>

#include "TextHelper.h"
#include "InteractHelper.h"
#include "Room.h"
#include "gtest/gtest.h"

TEST(TestTextHelper, readFileTest) {
  TextHelper::readFile("test/text/readFileTest.txt");
  EXPECT_EQ(TextHelper::line, 10);
}

TEST(TestTextHelper, commandProcessorTest) {
  Game* game = new Game();
  InteractHelper::game = game;
  Map* map = game->getMap();
  Room* r1 = new Room("Room A", "This room is made out of the letter A.");
  Room* r2 = new Room("Room B", "This room is made of bees.");
  Door* d1 = new Door(r1, r2);
  NPC* n1 = new NPC("Test NPC");
  n1->moveNPC(r1);
  game->addNPC(n1);
  r1->changeDoor(d1, Globals::Direction::NORTH);
  r2->changeDoor(d1, Globals::Direction::SOUTH);
  map->addRoom(r1);
  map->addRoom(r2);
  map->addDoor(d1);
  game->getPlayerHandler()->getPlayer()->setCurrentRoom(r1);

  std::cout << "   === Quit Test ===" << std::endl;
  std::ifstream input("test/text/commandProcessorTest_quit_input.txt");
  std::string file = "test/text/commandProcessorTest_quit_dialog.txt";
  TextHelper::readFile(file, input);
  file = "test/text/commandProcessorTest_quit_dialog_askquit.txt";
  TextHelper::readFile(file, input);
  input.close();

  std::cout << "   === Move Test ===" << std::endl;
  EXPECT_EQ(game->getPlayerHandler()->getPlayer()->getCurrentRoom(), r1);
  input.open("test/text/commandProcessorTest_empty_input.txt");
  file = "test/text/commandProcessorTest_move_dialog.txt";
  TextHelper::readFile(file, input);
  EXPECT_EQ(game->getPlayerHandler()->getPlayer()->getCurrentRoom(), r2);
  file = "test/text/commandProcessorTest_move_invalid.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::runtime_error);
  input.close();

  std::cout << "   === Move NPC Test ===" << std::endl;
  input.open("test/text/commandProcessorTest_empty_input.txt");
  file = "test/text/commandProcessorTest_movenpc_dialog.txt";
  TextHelper::readFile(file, input);
  file = "test/text/commandProcessorTest_movenpc_invalid1.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::runtime_error);
  file = "test/text/commandProcessorTest_movenpc_invalid2.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::runtime_error);
  input.close();

  EXPECT_FALSE(game->getPlayerHandler()->getPlayer()
  ->getInventory()->hasSpaceSuit());
  std::cout << "   === Give Test ===" << std::endl;
  EXPECT_EQ(game->getPlayerHandler()->getPlayer()->getInventory()->size(), 0);
  input.open("test/text/commandProcessorTest_empty_input.txt");
  file = "test/text/commandProcessorTest_give_dialog.txt";
  TextHelper::readFile(file, input);
  EXPECT_TRUE(game->getPlayerHandler()->getPlayer()
  ->getInventory()->hasSpaceSuit());
  EXPECT_EQ(game->getPlayerHandler()->getPlayer()->getInventory()->size(), 2);
  file = "test/text/commandProcessorTest_give_invalid.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::runtime_error);
  input.close();

  std::cout << "   === Block Test ===" << std::endl;
  input.open("test/text/commandProcessorTest_empty_input.txt");
  file = "test/text/commandProcessorTest_block_dialog.txt";
  TextHelper::readFile(file, input);
  file = "test/text/commandProcessorTest_block_invalid1.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::runtime_error);
  file = "test/text/commandProcessorTest_block_invalid2.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::invalid_argument);
  input.close();

  std::cout << "   === Unblock Test ===" << std::endl;
  input.open("test/text/commandProcessorTest_empty_input.txt");
  file = "test/text/commandProcessorTest_unblock_dialog.txt";
  TextHelper::readFile(file, input);
  file = "test/text/commandProcessorTest_unblock_invalid1.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::runtime_error);
  file = "test/text/commandProcessorTest_unblock_invalid2.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::invalid_argument);
  input.close();

  std::cout << "   === Setflag Test ===" << std::endl;
  input.open("test/text/commandProcessorTest_empty_input.txt");
  file = "test/text/commandProcessorTest_setflag_dialog.txt";
  TextHelper::readFile(file, input);
  file = "test/text/commandProcessorTest_setflag_invalid.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::invalid_argument);
  input.close();

  std::cout << "   === Setgflag Test ===" << std::endl;
  input.open("test/text/commandProcessorTest_empty_input.txt");
  file = "test/text/commandProcessorTest_setgflag_dialog1.txt";
  TextHelper::readFile(file, input);
  file = "test/text/commandProcessorTest_setgflag_dialog2.txt";
  TextHelper::readFile(file, input);
  file = "test/text/commandProcessorTest_setgflag_invalid.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::invalid_argument);
  input.close();

  TextHelper::rgScriptGlobalFlags["debugmode"] == 1;

  std::cout << "   === If Test ===" << std::endl;
  input.open("test/text/commandProcessorTest_empty_input.txt");
  file = "test/text/commandProcessorTest_if_dialog.txt";
  TextHelper::readFile(file, input);
  file = "test/text/commandProcessorTest_if_invalid1.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::invalid_argument);
  file = "test/text/commandProcessorTest_if_invalid2.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::invalid_argument);
  input.close();

  std::cout << "   === MC Test ===" << std::endl;
  input.open("test/text/commandProcessorTest_mc_input.txt");
  file = "test/text/commandProcessorTest_mc_dialog.txt";
  TextHelper::readFile(file, input);
  input.close();

  std::cout << "   === Chapter Test ===" << std::endl;
  input.open("test/text/commandProcessorTest_empty_input.txt");
  file = "test/text/commandProcessorTest_chapter_dialog.txt";
  TextHelper::readFile(file, input);
  file = "test/text/commandProcessorTest_chapter_invalid1.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::invalid_argument);
  file = "test/text/commandProcessorTest_chapter_invalid2.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::invalid_argument);
  input.close();

  std::cout << "   === Kill NPC Test ===" << std::endl;
  input.open("test/text/commandProcessorTest_empty_input.txt");
  file = "test/text/commandProcessorTest_killnpc_dialog.txt";
  TextHelper::readFile(file, input);
  EXPECT_FALSE(n1->isAlive());
  file = "test/text/commandProcessorTest_killnpc_invalid.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::runtime_error);
  input.close();

  std::cout << "   === Kill Player Test ===" << std::endl;
  input.open("test/text/commandProcessorTest_empty_input.txt");
  file = "test/text/commandProcessorTest_kill_dialog.txt";
  TextHelper::readFile(file, input);
  input.close();

  std::cout << "   === Invalid Test ===" << std::endl;
  input.open("test/text/commandProcessorTest_empty_input.txt");
  file = "test/text/commandProcessorTest_invalid_command_if.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::invalid_argument);
  file = "test/text/commandProcessorTest_invalid_command_mc.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::invalid_argument);
  file = "test/text/commandProcessorTest_invalid_command.txt";
  EXPECT_THROW(TextHelper::readFile(file, input), std::invalid_argument);

  input.close();

  delete game;
}

TEST(TestTextHelper, makePercentTest) {
  int i = 10000;
  EXPECT_EQ(TextHelper::makePercent(i), "100.00%");

  i = 5000;
  EXPECT_EQ(TextHelper::makePercent(i), "50.00%");

  i = 500;
  EXPECT_EQ(TextHelper::makePercent(i), "5.00%");

  i = 50;
  EXPECT_EQ(TextHelper::makePercent(i), "0.50%");

  i = 5;
  EXPECT_EQ(TextHelper::makePercent(i), "0.05%");

  i = 4839;
  EXPECT_EQ(TextHelper::makePercent(i), "48.39%");

  i = 4839;
  EXPECT_EQ(TextHelper::makePercent(i / 2), "24.19%");
}

TEST(TestTextHelper, listObjectsTest) {
  std::vector<Object*> vo;
  Object* o1 = new Object("Fire Extinguisher", "Pew pew, fire go boom!");
  Object* o2 = new Object("Umbrella", "I'm Mary Poppins y'all.");
  Object* o3 = new Object("Boomstick", "This... is my boomstick.");
  Object* o4 = new Object("Uber box", "Beyond mortal comprehension.");

  EXPECT_EQ(TextHelper::listObjects(vo), " nothing useful.");

  vo.push_back(o1);
  EXPECT_EQ(TextHelper::listObjects(vo), " a Fire Extinguisher.");

  vo.push_back(o2);
  EXPECT_EQ(TextHelper::listObjects(vo),
  " a Fire Extinguisher, and an Umbrella.");

  vo.push_back(o3);
  EXPECT_EQ(TextHelper::listObjects(vo),
  " a Fire Extinguisher, an Umbrella, and a Boomstick.");

  vo.push_back(o4);
  EXPECT_EQ(TextHelper::listObjects(vo),
  " a Fire Extinguisher, an Umbrella, a Boomstick, and an Uber box.");

  delete o1;
  delete o2;
  delete o3;
  delete o4;
}

TEST(TestTextHelper, listNPCsTest) {
  std::vector<NPC*> npcs;
  NPC* n1 = new NPC("Test1", "Test!");
  NPC* n2 = new NPC("Test2", "Test!");
  NPC* n3 = new NPC("Test3", "Test!");

  EXPECT_EQ(TextHelper::listNPCs(npcs),
  "There is nobody else in the room with you.");

  npcs.push_back(n1);
  EXPECT_EQ(TextHelper::listNPCs(npcs),
  "Test1 is here.");

  npcs.push_back(n2);
  EXPECT_EQ(TextHelper::listNPCs(npcs),
  "Test1, and Test2 are here.");

  npcs.push_back(n3);
  EXPECT_EQ(TextHelper::listNPCs(npcs),
  "Test1, Test2, and Test3 are here.");

  delete n1;
  delete n2;
  delete n3;
}

TEST(TestTextHelper, listDoorTest) {
  Room* rN = new Room();
  Room* rE = new Room();
  Room* rW = new Room();
  Room* rS = new Room();
  Room* r1 = new Room();
  Room* r2 = new Room();
  Door* d = new Door(r1, r2);

  EXPECT_EQ(TextHelper::listDoors(rN), "There are no doors.");

  rN->changeDoor(d, Globals::Direction::NORTH);
  EXPECT_EQ(TextHelper::listDoors(rN), "There is a door to the north.");
  rE->changeDoor(d, Globals::Direction::EAST);
  EXPECT_EQ(TextHelper::listDoors(rE), "There is a door to the east.");
  rW->changeDoor(d, Globals::Direction::WEST);
  EXPECT_EQ(TextHelper::listDoors(rW), "There is a door to the west.");
  rS->changeDoor(d, Globals::Direction::SOUTH);
  EXPECT_EQ(TextHelper::listDoors(rS), "There is a door to the south.");

  rN->changeDoor(d, Globals::Direction::EAST);
  EXPECT_EQ(TextHelper::listDoors(rN),
  "There are doors to the north, and east.");

  rE->changeDoor(d, Globals::Direction::WEST);
  EXPECT_EQ(TextHelper::listDoors(rE),
  "There are doors to the east, and west.");

  rW->changeDoor(d, Globals::Direction::SOUTH);
  EXPECT_EQ(TextHelper::listDoors(rW),
  "There are doors to the south, and west.");

  rS->changeDoor(d, Globals::Direction::NORTH);
  EXPECT_EQ(TextHelper::listDoors(rS),
  "There are doors to the north, and south.");

  rN->changeDoor(d, Globals::Direction::WEST);
  EXPECT_EQ(TextHelper::listDoors(rN),
  "There are doors to the north, east, and west.");

  rN->changeDoor(d, Globals::Direction::SOUTH);
  EXPECT_EQ(TextHelper::listDoors(rN),
  "There are doors to the north, east, south, and west.");

  delete rN;
  delete rE;
  delete rW;
  delete rS;
  delete r1;
  delete r2;
  delete d;
}

TEST(TestTextHelper, startsWithVowelTest) {
  EXPECT_TRUE(TextHelper::startsWithVowel("iguana"));
  EXPECT_TRUE(TextHelper::startsWithVowel("umbrella"));
  EXPECT_TRUE(TextHelper::startsWithVowel("opera"));
  EXPECT_TRUE(TextHelper::startsWithVowel("apple"));
  EXPECT_TRUE(TextHelper::startsWithVowel("elephant"));
  EXPECT_TRUE(TextHelper::startsWithVowel("    elephant    "));
  EXPECT_TRUE(TextHelper::startsWithVowel(" e l e p h ant"));

  EXPECT_FALSE(TextHelper::startsWithVowel(""));
  EXPECT_FALSE(TextHelper::startsWithVowel("consonant"));
  EXPECT_FALSE(TextHelper::startsWithVowel("vowel"));
  EXPECT_FALSE(TextHelper::startsWithVowel("papaya"));
  EXPECT_FALSE(TextHelper::startsWithVowel("yttrium"));
  EXPECT_FALSE(TextHelper::startsWithVowel(" b a l a b a l o o "));
  EXPECT_FALSE(TextHelper::startsWithVowel("357"));
  EXPECT_FALSE(TextHelper::startsWithVowel("  357"));
}

TEST(TestTextHelper, tolowerTest) {
  std::string s = "Test";
  EXPECT_NE(s, "test");
  EXPECT_EQ(TextHelper::tolower(s), "test");
}

TEST(TestTextHelper, toupperTest) {
  std::string s = "Test";
  EXPECT_NE(s, "TEST");
  EXPECT_EQ(TextHelper::toupper(s), "TEST");
}

TEST(TestTextHelper, trimTest) {
  std::string s = "   test me  ";
  EXPECT_NE(s.size(), 7);
  EXPECT_NE(s, "test me");
  s = TextHelper::trim(s);
  EXPECT_EQ(s.size(), 7);
  EXPECT_EQ(s, "test me");
}

TEST(TestTextHelper, trimAllTest) {
  std::string s = "  t e             s t";
  EXPECT_NE(s.size(), 4);
  EXPECT_NE(s, "test");
  s = TextHelper::trimAll(s);
  EXPECT_EQ(s.size(), 4);
  EXPECT_EQ(s, "test");
}

TEST(TestTextHelper, keyifyTest) {
  std::string s = "    HELLO world   ";
  EXPECT_NE(s.size(), 11);
  EXPECT_NE(s, "hello_world");
  s = TextHelper::keyify(s);
  EXPECT_EQ(s.size(), 11);
  EXPECT_EQ(s, "hello_world");
}
