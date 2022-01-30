# Labyrinthe

## Introduction
The objectif of this project to make a simplified version of the game Kill'em All based on a provided prototype using C++. The prototype provided the API for graphic display of the game. What we need to do is fullfill the whole procedure of the game and implement its rules.

In this report, we presented the result of our work, the analyse of the problems of various aspects, and our solutions to these problems.


## Prograss

### Features
The game can be lanched from a valid map file. If the map file misses key elements, like the initial location of the hunter, location of the tresure, the program will produce error messages and exit. The behavior with other error is unknown.

The gurdiens have 2 state, patrol and attack. In peace state, its action is determinist, when blocked by an obstacle, it will try other direction in a fixed order. It will trun to attack mode when seeing the hunter and shoot him.

The hunter possede a initial health, when he is hit, he will lose 5 points. The health will not recover automatically and there are no firt-aid in the map. When the hunter lose all the health, the player will lose the game.

The makefile for this project is cross-platform, however we only tested it on Windows. The depenency management of this makefile is semi-automatical, which means when adding a new module to the project, for example "module_A.h" and "module_A.cc", we need to add the name "module_A" in the makefile.

### Bugs
In the game, the map seems to be transposed and we don't know why.
When lanching the game with a big map, like the one provided "labyrinthe.txt", the lanch will failed, just try a few more times. We don't have the problem with a small map.

## Objectives of the project
Kill'em All is a 3D, first-person perspective, FPS game. Player will control a character named the hunter to look for a treasure in a labyrinth. There are ennemys in the labyrinth named the gurdiens who will attack the hunter.

The objective of the project is to develop a simplfied version of the game Kill'em All using C++ based on a protrotype. The proptotype provides us APIs to render models in a 3D environment. Besides we can use some interfaces to design their behaviors.

From the view of developper, the game has following steps from its launch to the end:
1. Read a file that describes all the information of the labyrinth.
2. Render graphical models, then enter into the main loop of the game.
3. In each loop, the characters will act by following the behiviors that we defined in code.
4. In each loop, we will detect the condition to end the game, win or lose.

Thus, in general, we have two problem to complete the development of the game:
1. Parse the map file to retrive the data and represent it in the structure accepted by the API.
2. Define the behaviors of characters based on the rule of the game by implementing correspondant interfaces.

Meanwhile, as we are using C++, a powerful but sephiscated language as development tool, some problems coming from itself during its application.

## Analyse of map file
The analyse of the map file is decomposed into severals steps:
1. Read the file and transforme it into a vector of string.
2. Analyse and separate the vector into 2 vectors:
    - letter replacement rules for picture
    - definition of the structure of the game map
3. Parse the rules and store them as the data structure: map
4. Parse the definition and transforme it into a 2 dimentions array of char.
5. Go through the array to find out the walls and pictures with help of the rules.
6. Go through the array again to search for other elements of the game map: the initial location hunter, the location of treasure, the locations of gurdiens.
7. Render all the elements in the game.

Step 1 to 4 is done by class `MapFile`, class `MapData` do the step 5 and 6, class `labyrinthe` charge the step 7, some auxilary data structures that are necessary during the analyse of map file are defined in the file `MapElement`

## Implementation of game rules

### Firing
Apart from all the behaviors defined in class `Mover`, we find some others commen attributes and methods between hunter and gurdiens, in consequence, we defined an other abstract class `Shooter` above them but detrvive from `Mover`.

Class `Shooter` declears the behaviors involving firing, demage receiving and fireball controlling. It implements the behivors of movement of fireball, sound effet of explonation of ball, and consequence of being demaged.

However, certain behaviors of firing differ from actual shooter, there are virtual methods that are left for child class to implement:
- the behavior after the explosion of fireball, because the gurdien will shoot after last explosion.
- the behavior while the fireball is moving, this is because we detect the collision of gurdien for the fireball shooted by hunter and dectect the collision of hunter for gurdien, it's different depends on the real shooter.

### Data flux
While runing the game, the hunter and the gurdiens needs to know each others' data to perform some tasks. For example, the state of gurdiens needs the location of the hunter to be determined. To solve this problem, we create the class `Bridge` charging for the transformation of data flux. The hunter and all the gurdiens share the same instance of Bridge, so that then can retrive data from each others. By manipulating header files and source files, we managed to define bridge as a attribute of the hunter and of all the gurdiens, and vice versa.

## Recessource Management
### Static ressources of the game
The static ressources, like modeles, sounds and textures are located in a peticular directory related to the position of the executable. We use a module `config.h` to manage all the path of these resources. For example, to get the path of the texture of the box in the game, `string get_texture_path(const string& name)` will do the job. If we change the structure of the directory of the project, only some configration in the header file need to be changed.
### Memory
Unfortunately, we don't have the time to manage the memory that we demande, that is to say, we don't gurante that all the "new" will be deleted proprely, specialy those we demande during the analyse of the map file. We choose to delegate this job to the operating system by the end of the game.
Meanwhile, we ensure that we don't use extra memory during the game loop, that is to say, the memory usage will not increase when enrolling the main phrase of the game.

## Language itself
### Generation of binary program
To have a clean structure of directory, the project is reorgnized, to see the explanition of structure, please refer to the README.md of the project.In this project, the makefile should be able to produce a binary program depending on the

### Management of dependency
The principle of the design of module is to ensure that its dependency graphe contains no loop.

However, in the project, to communicate data among all the shooters(the hunter and the gurdiens) as we mentioned above, all the shooters share the same instance of class `Bridge` as an attribute. Meanwhile, instance of bridge records all the instances of the shooters as attributes too.

As consequence, in the header files of these 2 class, they have to know each other's definition. But, if we simplely include each other in their own header file, that will cause a loop of inclusion. Further more, if we add include gurde in the header files, one definition of 2 class will missing depends on the order of compilation. To resolve this problem, we apply the partiel class definition and do some tricks in the source file. "Bridge.h" include "Shooter.h" and we decleared a partiel class in the "Shooter.h" and make "Shooter.cc" include "Bridge.h" as well, so that the implementation of Shooter could know Bridge's definition.


## Conclusion
Before this course, I have a lot experience in Language C and Java programing. In this project, I've learned the syntax of C++ and how to do object-oriented programming using C++ concretely, for instance, derive a class, using polymophsiome.
This project also gives me a chance to pratice the tools of C family language. For example, the application of makefile to automatize the compilation and the management of .
In this project, it's a little shame that we couldn't appy more advanced tecniques of memory management like share_ptr, unique_ptr. 

By the end of these project, I believe I have acquired all basic notion of C++. 用C++ 应用了学过的OOP技术