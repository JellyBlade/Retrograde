/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef TEXT_HELPER_H
#define TEXT_HELPER_H

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "Object.h"
#include "Room.h"
#include "NPC.h"

/**
* Provides functions for handling file reading, command strings, and modifying
* strings.
*/
namespace TextHelper {
  extern std::map<std::string, bool> rgScriptLocalFlags;
  extern std::map<std::string, bool> rgScriptGlobalFlags;
  extern int line;
  /**
  * Outputs dialogue from file to screen,
  * calling commandProcessor if it encounters a script command to execute.
  * @param textPath to the path of the file to read from.
  * @param input the istream to use for user-input.
  * An fstream is used for automated testing, and std::cin is for user-input.
  */
  void readFile(std::string textPath, std::istream& input = std::cin);

  /**
  * Performs functions based on the inputted command string read
  * from a dialogue file.
  * @param command the script command to parse and execute.
  * @param file the file currently being read.
  * @param input the istream to use for user-input.
  * An fstream is used for automated testing, and std::cin is for user-input.
  * @return true if the file should be closed, false if it should
  * continue to be read.
  * @throws invalid_argument if the command given is not recognized.
  */
  bool commandProcessor(std::string command, std::istream& file,
    std::istream& input = std::cin);

  /**
  * Processes conditional if/else statements from the file based on a set of
  * possible criteria to evaluate, allowing screen output to change based on
  * these criteria, such as objects in the room/inventory, game progress,
  * or global/local flags that can be set prior to "remember" choices the player
  * made during the game.
  *
  * Calls commandProcessor for nested commands.
  *
  * Associated Commands: :if | :else | :endif
  * @param params Vector of strings to use. params[0] should always be
  * the criteria, the rest are names of objects, flags, etc. to use.
  * @param file The currently-open file to read the conditional dialog from.
  * @param input The istream to use for input. std::cin for player input, and
  * fstream for testing purposes via file.
  * @return true if the file should be closed, or false if the file should
  * continue being read.
  * @throws invalid_argument if there are no parameters given.
  * @throws invalid_argument if the criteria used is not recognized.
  */
  bool cpIf(std::vector<std::string> params, std::istream& file,
    std::istream& input);

  /**
  * Processes branching multiple-choice statements from the file. The player
  * is presented with a selection of responses that they can choose from. Only
  * the dialog related to their choice will be displayed. Some choices will
  * return the file to the top of the MC block to allow for re-asking questions.
  *
  * Calls commandProcessor for nested commands.
  *
  * Associated Commands: :mc | :endmcdef | :endmc | :continue | :back |
  * :0, :1, :2, ..., :n
  * @param file The currently-open file to read the branching dialog from.
  * @param input The istream to use for input. std::cin for player input, and
  * fstream for testing purposes via file.
  * @return true if the file should be closed, or false if the file should
  * continue being read.
  */
  bool cpMC(std::istream& file, std::istream& input);

  /**
  * Changes the game's chapter to the given value. Can also use '+' and '-'
  * operators to increment/decrement the chapter value.
  *
  * Associated Command: :chapter
  * @param params Contains parameters. params[0] should always be a valid choice
  * for the chapter. The other parameters are ignored.
  * @throws invalid_arguemnt if there are no parameters.
  * @throws invalid_arguemnt if param[0] isn't +/- or a valid int.
  * @return false
  */
  bool cpChapter(std::vector<std::string> params);

  /**
  * Gives the player an object, adding it to their inventory, based on the
  * name given in the file.
  *
  * Associated Command: :give
  * @param params Strings to combine to get the object name.
  * @return false
  * @throws invalid_argument if there are no parameters given.
  */
  bool cpGive(std::vector<std::string> params);

  /**
  * Blocks a door in the player's current room, based on the direction and
  * reason given in the file.
  *
  * Associated Command: :block
  * @param params Contains parameters. params[0] should always be the
  * directions specified in Globals::Direction. The rest are used as the
  * blockedReason.
  * @return false
  * @throws invalid_argument if there are 1 or less parameters given.
  * @throws runtime_error if the door in the given direction does not exist.
  */
  bool cpBlock(std::vector<std::string> params);

  /*
  * Unblocks a door in the player's current room, based on the direction given
  * in the file.
  *
  * Associated Command: :unblock
  * @param params Contains parameters. params[0] should always be the
  * directions specified in Globals::Direction.
  * @return false
  * @throws invalid_argument if there are no parameters given.
  * @throws runtime_error if the door in the given direction does not exist.
  */
  bool cpUnblock(std::vector<std::string> params);

  /**
  * Sets the local flag with the given name to the given bool from the file.
  * Local flags are cleared when the file is closed.
  * Flags are used as a criteria with the :if command.
  *
  * Associated Command: :setflag
  * @see TextHelper::cpIf
  * @param params Contains parameters. The last parameter should always be
  * true/false/t/f/0/1. The rest are used for the name of the flag.
  * @return false
  * @throws invalid_argument if there are 1 or less parameters given.
  */
  bool cpSetFlag(std::vector<std::string> params);

  /**
  * Sets the global flag with the given name to the given bool from the file.
  * Global flags persist between files, and are cleared only on program close.
  * <b>Local flags with the same name take precedence.</b>
  * Flags are used as a criteria with the :if command.
  *
  * Associated Command: :setgflag | :setflagg
  * @param params Contains parameters. The last parameter should always be
  * true/false/t/f/0/1. The rest are used for the name of the flag.
  * @return false
  * @throws invalid_argument if there are 1 or less parameters given.
  */
  bool cpSetGlobalFlag(std::vector<std::string> params);

  /**
  * Moves the player to the room given from the file.
  *
  * Associated Command: :move
  * @param params Strings to combine to get the name of the room to move to.
  * @return false
  * @throws runtime_error if a room with the name given does not exist.
  */
  bool cpMovePlayer(std::vector<std::string> params);

  /**
  * Moves the NPC given by name to the room given in the file.
  *
  * Associated Command: :movenpc
  * @param params Contains parameters. params[0] should always be the name of
  * the NPC without any spaces. The rest of the params are combined together
  * to get the room name.
  * @return false
  * @throws runtime_error if an NPC with the name given does not exist.
  * @throws runtime_error if a room with the name given does not exist.
  */
  bool cpMoveNPC(std::vector<std::string> params);

  /**
  * Kills the NPC given by name. Does not call NPC::stab(), instead setting
  * their alive value to false directly.
  *
  * Associated Command: :killnpc
  * @param params Strings to combine to get the name of the NPC to kill.
  * @return false
  * @throws runtime_error if an NPC with the name given does not exist.
  */
  bool cpKillNPC(std::vector<std::string> params);

  /**
  * Checks if the file at the given path exists.
  * @return true if the file exists, false otherwise.
  */
  bool fileExists(std::string path);

  /**
  * Turns the given integer into a fake percentage with two decimals of
  * precision by adding a decimal place two places from the last digit.
  * (10000 -> 100.00, 5500 -> 55.00)
  * @param i int to turn into a fake percentage.
  * @return a fake percentage version of the input integer.
  */
  std::string makePercent(int i);

  /**
  * Formats all of the object names in the vector into a drop-in sentence.
  * @param objects the objects to list off.
  * @return a drop-in sentence that lists off all of the objects given, ending
  * with appropriate punctuation and grammar.
  */
  std::string listObjects(std::vector<Object*> objects);

  /*
  * Formats all of the npcs in the vector into a complete sentence.
  * @param npcs the NPCs to list off.
  * @return a complete sentence that lists off all of the npcs in the vector,
  * ending with appropriate punctuation and grammar.
  */
  std::string listNPCs(std::vector<NPC*> npcs);

  /**
  * Formats all of the room's doors into a drop-in sentence, listing doors
  * going clockwise from north.
  * @param room the room to list doors for.
  * @return a drop-in sentence that lists off all of the doors in the room,
  * ending with appropriate punctuation and grammar.
  */
  std::string listDoors(Room* room);

  /**
  * Determines if the string starts with a vowel.
  * @param s the string to check.
  * @return true if the string starts with a vowel, false otherwise.
  */
  bool startsWithVowel(std::string s);

  /**
  * Replaces all characters in the string with their lowercase counterparts.
  * @param s the string to turn into lowercase
  * @return a lowercase version of the input string.
  */
  std::string tolower(std::string s);

  /**
  * Replaces all characters in the string with their uppercase counterparts.
  * @param s the string to turn into uppercase.
  * @return an uppercase version of the input string.
  */
  std::string toupper(std::string s);

  /**
  * Removes leading/trailing whitespace from the string.
  * @param s the string to trim.
  * @return a string without whitespace at the beginning or end.
  */
  std::string trim(std::string s);

  /**
  * Removes all whitespace from the string.
  * @param s the string to remove all whitespace from.
  * @return a string without any whitespace.
  */
  std::string trimAll(std::string s);

  /**
  * Trims, tolowers, and replaces all spaces with underscores.
  * @param s the string to keyify
  * @return a string that can be compared to JSON keys.
  */
  std::string keyify(std::string s);

} // namespace TextHelper

#endif // TEXT_HELPER_H
