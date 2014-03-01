Name:  Tim Righettini
USC ID: 9445525333
E-mail Address: trighett@usc.edu

-- CSCI 460 Assignment #2 README --

Hello,

This document will go over four key points: The design/structure behind the program, instructions on compilation, any issues that might come up when running the program, and the answers to the review questions.

----- 1. Program Structure & Design -----

Essentially, the program works as described in the assignment 2 doc and from assignment 1.  First, the tree is set up in main(), according to the specifications of the Egyptian Map we were given.  Secondly, the heuristic tables are set up when the tree construction is complete from the values provided in the assignment 2 document.  After that, the GeneralSearch(...) function is called after Alexandria is placed into the currentNodes queue.  In fact, main.cpp is the only file used to create the program, so you will find everything necessary in there.

As requested, the only line you have to change in the program is the queuing function call in the General Search Loop.  These four methods are called in GeneralSearch(...):

EnqueueGreedy(cityNodes, currentNodes, nodeToTest, h1); // Greedy Search H1
EnqueueGreedy(cityNodes, currentNodes, nodeToTest, h2); // Greedy Search H2
EnqueueAStar(cityNodes, currentNodes, nodeToTest, h1); // AStar Search H1
EnqueueAStar(cityNodes, currentNodes, nodeToTest, h2); // AStar Search H2

Comment the appropriate functions and everything should work accordingly in GeneralSearch(...).  Of course, only one of these functions should be run at any given time, or else they will get in each other's way (and that will not be very helpful, will it?).

Besides for the commenting, there is nothing out of the ordinary to be wary of.

----- 2. Instructions for Compilation/Execution -----

Go on aludra (after copying main.cpp to it) and then run the following commands:

g++ -g -o assign2 main.cpp

./assign2

This will compile the file and run it as you deem fit with the queuing function you comment in.

----- 3. Answers to review questions -----

A. Comment on your observations regarding the performance of A* using both h1 and h2 as the
estimated path cost to the goal. Which one (h1 or h2) performs a more efficient search based
on your output data (i.e., the examined nodes)? 

Based upon my output data, both heuristics provided the same results for A*, but h2 performed a more efficient greedy serach than h1.  To fully explain why A* performed the way it did, I will also need to elaborate upon the results of the greedy search too.

Specifically:
 - For greedy search: h2 examined one less node than h1 (h2 skipped Kharga).  h2 skipped        
   Kahrga because in h2 Sohag has a lower heuristic value than Kharga.  In h1 the opposite
   is true, so h1 actually went to Kharga before reaching Sohag, resulting in a slightly        
   less efficient search versus h2. 

 - For A* search: h1 and h2 examined the same number of nodes (all of them, which is 15).
   Both heuristics found the cheapest path, though, which was 775 cost.  Greedy search did
   NOT find a path cheaper than this (h1 and h2 both found the path of 814 cost by going the
   western route through Mut).

 - A* might have searched through more nodes, but it found the cheapest path as a result.
   Thus, A* is more consistent than greedy search, which might be better than efficiency in
   some cases if you want the best solution versus a dirtier solution that is found quickly.

There are a few takeaways here:
1.  Greedy search may find a descent path by checking less nodes, which means it can be more
    efficient if you are lucky.  Just because you check less nodes does not mean it will
    provide the cheapest solution in terms of path cost.  A* might search through more nodes
    on average, but it will usually find the cheapest path in the end.

2.  A good heuristic makes greedy search work well.  The more accurate the heuristic is, the
    better greedy search will perform.  If h(x) was the remaining path cost to get to Luxor,
    for example, greedy search would work like an inversed uniform cost search and h(x)   
    would be both an admissable and accurate heuristic.  Thus, do not use greedy search with 
    an admissible but highly inaccurate heuristic.  Since A* uses both the actual path cost
    and a heuristic, it is not as reliant on the hueristic and will not resort to as much        
    wacky behavior if its hueristic is inaccurate.

B. Provide explanations of how your data either matches the expected or predicted analytical result or why it does not match the expected or predicted result. 

My data from the assignment matches the expected or predicted analytical result because:
1.  For EnqueueGreedy(...), the expanded values are sorted based upon only their heuristic 
    cost.  As such, when looking at the SLD distances provided in the assignment, it makes
    sense why the search took the order it did in both cases.
    a.  Both sets of hueristics have a similar data trend.  When sorting these values in 
        either search at any given point, most of the values have positioning in terms of
        h(x) cost, except for Kharga, which has less cost that Sohag in h1 versus h2.  
        Although the costs have different actual values, their relative placement is mostly
        the same, which explains why the greedy searches almost performed similarly.

2.  For EnqueueAStar(...), on the other hand, h(x) plays an important role in determining  
    the total cost of any given node, but the path cost to get to a certain node also plays 
    a big factor in sorting nodes too.  As such, since the relative ordering/hierarchy of   
    heuristic costs is similar for h1 and h2 (as explained for greedy search), A* performs 
    the same for h1 and h2 because g(x) is the same at any given point where a heuristic   
    from h1 or h2 is compared also.  For example:

    If I am on Alexandria, and
    g(Cairo)  = 112   
    g(Matruh) = 159
    g(Nekhel) = 245       

    h1(Cairo)  = 126   h2(Cairo)  = 139
    h1(Nekhel) = 133   h2(Nekhel) = 148
    h1(Matruh) = 174   h2(Matruh) = 189

    Based upon the implicit ordering of both hueristics, I know I will be going to Cairo in  
    either case for A* (and even greedy).  This holds true for every expansion except when 
    comparing Kharga in greedy, since its implicit place in the ordering of h1 and h2 is 
    different. The reason why A* returns the same result at this point is because g(Kharga) 
    + h1(Kharga) || h2(Kharga) is cheaper than g(Sohag) + h1(Sohag) || h2(Sohag) in terms of
    f(x) = g(x) + h(x) cost.  

-------------------------------------------

And that's a wrap!  Thanks for viewing the README.

Tim
Bloomthegame.com