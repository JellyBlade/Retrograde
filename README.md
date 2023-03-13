# Retrograde
A short text-based adventure game developed for CPSC 2720 at the University of Lethbridge.

Created by Landon Constantin, Tyrell Martens, and Tyler Hippard

Retrograde features a few NPCs to talk to, a few short puzzles to complete, as well as simple oxygen management mechanics for yourself, the crew, and the spaceship. Take too long to solve the puzzles and you will asphyxiate. Accidentally open an airlock to vent atmosphere will kill you and the crew.

This version of Retrograde is complete, albeit short, and serves as a tech demo for RGScript's capabilities.

Features a custom interpreted scripting language (RGScript), written in C++ for interacting with the world, npcs, objects, and the player through commands in text files.

[View RGScript Documentation](text/README.md)

The game world, items, and NPCs are all read from JSON files using [nlohmann's C++ json library](https://github.com/nlohmann/json).

## Story
Retrograde takes place aboard the AUF SIRONA, a doomed spaceship that went missing. You find yourself alone, and without any recollection of what happened aboard the SIRONA.

