Name:  Tim Righettini
USC ID: 9445525333
E-mail Address: trighett@usc.edu

-- CSCI 460 Assignment #1 README --

Hello,

This document will go over three key points: The design/structure behind the program, instructions on compilation, and any issues that might come up when running the program.

----- 1. Program Structure & Design -----

Essentially, the program works as described in the assignment doc.  First, the tree is set up in main(), according to the specifications of the Egyptian Map we were given.  After that, the GeneralSearch(...) function is called after Alexandria is placed into the currentNodes queue.  In fact, main.cpp is the only file used to create the program, so you will find everything necessary in there.

As requested, the only line you have to change in the program is the queuing function call in the General Search Loop.  These three methods are called in GeneralSearch(...):

EnqueueBFS(...); // Breadth First Search (BFS)
EnqueueDFS(...); // Depth First Search (DFS)
EnqueueUCS(...); // Uniform COst Search (UCS)

Comment the appropriate functions and everything should work accordingly in GeneralSearch(...).  Of course, only one of these functions should be run at any given time, or else they will get in each other's way (and that will not be very helpful, will it?).

Besides for the commenting, there is nothing out of the ordinary to be wary of.

----- 2. Instructions for Compilation/Execution -----

Go on aludra (after copying main.cpp to it) and then run the following commands:

g++ -g -o assign1 main.cpp

./assign1

This will compile the file and run it as you deem fit with the queuing function you comment in.  Simple and to the *point, right?

Anyway, have a nice day, and thanks for viewing the README!

Tim
Bloomthegame.com