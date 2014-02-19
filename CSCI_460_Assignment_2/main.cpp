// CSCI_460_Assignment_1.cpp : Defines the entry point for the console application.
//

// Preprocessor Directives

#include <map>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

// NOTE: -std=gnu++0x or -std=c++0x must be enabled for c++ 2011 stuff to work
// NOTEL C++ 2011 does NOT work on aludra, using C++ 1998 for this assignment

// Globals to be used for the program

struct ConnectedNode // Will be a struct used for children to expand from
{
    std::string name;
    int cost; // Cost between this Node and the Node it is attached to

    ConnectedNode(std::string name, int cost)
    {
        this->name = name;
        this->cost = cost;
    }
};

struct Node // Struct for holding node information
{
    std::vector<ConnectedNode> children; // List of descendants
    std::string name; // Name of the Node

    // To be used for Uniform Cost and A* Search
    // Will be used for the cost up to this Node,
    // and can be made smaller and smaller as time goes on
    int gCost;

    // To be used for A* search and a special comparator function
    int hCost;

    bool isQueued; // If the Node is expanded, this will be true, will prevent loops
};

// Used for UCS sorting comparison
struct FunctorUCS
{
        // Overloading () operators for std::sort()
    bool operator ()(Node *a, Node *b)
    {
        if (a->gCost < b->gCost) return true;
        if (a->gCost > b->gCost) return false;

        if (a->name < b->name) return true;
        if (a->name > b->name) return false;

        return false;
    }
} functorUCS;

// Used for A* sorting comparison
struct FunctorAStar
{
        // Overloading () operators for std::sort()
    bool operator ()(Node *a, Node *b)
    {
        if ((a->gCost + a->hCost) < (b->gCost + b->hCost)) return true;
        if ((a->gCost + a->hCost) > (b->gCost + b->hCost)) return false;

        if (a->name < b->name) return true;
        if (a->name > b->name) return false;

        return false;
    }
} functorAStar;

bool isUCS = false;

// Function Prototypes
void GeneralSearch(std::map<std::string, Node*>&, std::vector<Node*> &, std::vector<Node*> &, Node *, std::map<std::string, ConnectedNode*> &, std::map<std::string, ConnectedNode*> &);
void EnqueueBFS(std::map<std::string, Node*>&, std::vector<Node*> &, Node *);
void EnqueueDFS(std::map<std::string, Node*>&, std::vector<Node*> &, Node *);
void EnqueueUCS(std::map<std::string, Node*>&, std::vector<Node*> &, Node *);
void EnqueueGreedy(std::map<std::string, Node*>&, std::vector<Node*> &, Node *, std::map<std::string, ConnectedNode*> &);
void EnqueueAStar(std::map<std::string, Node*>&, std::vector<Node*> &, Node *, std::map<std::string, ConnectedNode*> &);

bool GoalTest(Node *, Node* );

int main(int argc, char* argv[])
{
    // Instantiate the map
    std::map<std::string, Node*> cityNodes;
    std::vector<Node*> currentNodes; // Will be the vector used for Queuing for the three Queuing functions
    std::vector<Node*> exploredNodes; // Will be the vector used for keeping track of what has been found so far
    // NOTE: I use this vector as a queue. stack, and priority queue all at once to save on instantiating different lists

    // Instantiate the Tables for h1, h2
    std::map<std::string, ConnectedNode*> h1;
    std::map<std::string, ConnectedNode*> h2;

    // Build the tree

    // Alexandria Node
    Node* n = new Node();

    n->name = "Alexandria";
    n->isQueued = false;
    n->gCost = 0;
    n->children.push_back(ConnectedNode("Matruh", 159));
    n->children.push_back(ConnectedNode("Cairo", 112));
    n->children.push_back(ConnectedNode("Nekhel", 245));

    cityNodes[n->name] = n;

    // Nekhel Node
    n = new Node();

    n->name = "Nekhel";
    n->isQueued = false;
    n->gCost = 0;
    n->children.push_back(ConnectedNode("Alexandria", 245));
    n->children.push_back(ConnectedNode("Suez", 72));
    n->children.push_back(ConnectedNode("Quseir", 265));

    cityNodes[n->name] = n;

    // Suez Node
    n = new Node();

    n->name = "Suez";
    n->isQueued = false;
    n->gCost = 0;
    n->children.push_back(ConnectedNode("Nekhel", 72));

    cityNodes[n->name] = n;

    // Quseir Node
    n = new Node();

    n->name = "Quseir";
    n->isQueued = false;
    n->gCost = 0;
    n->children.push_back(ConnectedNode("Sohag", 163));
    n->children.push_back(ConnectedNode("Nekhel", 265));

    cityNodes[n->name] = n;

    // Sohag Node
    n = new Node();

    n->name = "Sohag";
    n->isQueued = false;
    n->gCost = 0;
    n->children.push_back(ConnectedNode("Mut", 184));
    n->children.push_back(ConnectedNode("Qena", 69));
    n->children.push_back(ConnectedNode("Quseir", 163));

    cityNodes[n->name] = n;

    // Qena Node
    n = new Node();

    n->name = "Qena";
    n->isQueued = false;
    n->gCost = 0;
    n->children.push_back(ConnectedNode("Luxor", 33));
    n->children.push_back(ConnectedNode("Sohag", 69));

    cityNodes[n->name] = n;

    // Luxor Node
    n = new Node();

    n->name = "Luxor";
    n->isQueued = false;
    n->gCost = 0;
    n->children.push_back(ConnectedNode("Qena", 33));

    cityNodes[n->name] = n;

    // Kharga Node
    n = new Node();

    n->name = "Kharga";
    n->isQueued = false;
    n->gCost = 0;
    n->children.push_back(ConnectedNode("Mut", 98));

    cityNodes[n->name] = n;

    // Mut Node
    n = new Node();

    n->name = "Mut";
    n->isQueued = false;
    n->gCost = 0;
    n->children.push_back(ConnectedNode("Qasr Farafra", 126));
    n->children.push_back(ConnectedNode("Sohag", 184));
    n->children.push_back(ConnectedNode("Kharga", 98));

    cityNodes[n->name] = n;

    // Qasr Farafra Node
    n = new Node();

    n->name = "Qasr Farafra";
    n->isQueued = false;
    n->gCost = 0;
    n->children.push_back(ConnectedNode("Bawiti", 104));
    n->children.push_back(ConnectedNode("Mut", 126));

    cityNodes[n->name] = n;

    // Bawiti Node
    n = new Node();

    n->name = "Bawiti";
    n->isQueued = false;
    n->gCost = 0;
    n->children.push_back(ConnectedNode("Siwa", 210));
    n->children.push_back(ConnectedNode("Cairo", 186));
    n->children.push_back(ConnectedNode("Qasr Farafra", 104));

    cityNodes[n->name] = n;

    // Cairo Node
    n = new Node();

    n->name = "Cairo";
    n->isQueued = false;
    n->gCost = 0;
    n->children.push_back(ConnectedNode("Bawiti", 186));
    n->children.push_back(ConnectedNode("Alexandria", 112));
    n->children.push_back(ConnectedNode("Asyut", 198));

    cityNodes[n->name] = n;

    // Asyut Node
    n = new Node();

    n->name = "Asyut";
    n->isQueued = false;
    n->gCost = 0;
    n->children.push_back(ConnectedNode("Cairo", 198));

    cityNodes[n->name] = n;

    // Siwa Node
    n = new Node();

    n->name = "Siwa";
    n->isQueued = false;
    n->gCost = 0;
    n->children.push_back(ConnectedNode("Matruh", 181));
    n->children.push_back(ConnectedNode("Bawiti", 210));

    cityNodes[n->name] = n;

    // Matruh Node
    n = new Node();

    n->name = "Matruh";
    n->isQueued = false;
    n->gCost = 0;
    n->children.push_back(ConnectedNode("Siwa", 181));
    n->children.push_back(ConnectedNode("Alexandria", 159));

    cityNodes[n->name] = n;

    // Add Alexandria to the starting set of nodes for GeneralSearch()
    currentNodes.push_back(cityNodes["Alexandria"]);
    currentNodes[0]->isQueued = true;

    // Populate the h1, h2 tables with the appropriate data
    h1["Matruh"] = new ConnectedNode("Matruh" , 174);
    h1["Cairo"]  = new ConnectedNode("Cairo"  , 126);
    h1["Nekhel"] = new ConnectedNode("Nekhel" , 133);
    h1["Siwa"]   = new ConnectedNode("Siwa"   , 132);
    h1["Bawiti"] = new ConnectedNode("Bawiti" , 105);
    h1["Asyut"]  = new ConnectedNode("Asyut"  , 52);
    h1["Suez"]   = new ConnectedNode("Suez"   , 121);
    h1["Qasr Farafra"] = new ConnectedNode("Qasr Farafra", 68);
    h1["Quseir"] = new ConnectedNode("Quseir" , 55);
    h1["Mut"]    = new ConnectedNode("Mut"    , 51);
    h1["Kharga"] = new ConnectedNode("Kharga" , 24);
    h1["Sohag"]  = new ConnectedNode("Sohag"  , 27);
    h1["Qena"]   = new ConnectedNode("Qena"   , 10);
    h1["Luxor"]  = new ConnectedNode("Luxor"   , 0);

    h2["Matruh"] = new ConnectedNode("Matruh" , 189);
    h2["Cairo"]  = new ConnectedNode("Cairo"  , 139);
    h2["Nekhel"] = new ConnectedNode("Nekhel" , 145);
    h2["Siwa"]   = new ConnectedNode("Siwa"   , 148);
    h2["Bawiti"] = new ConnectedNode("Bawiti" , 118);
    h2["Asyut"]  = new ConnectedNode("Asyut"  , 67);
    h2["Suez"]   = new ConnectedNode("Suez"   , 136);
    h2["Qasr Farafra"] = new ConnectedNode("Qasr Farafra", 77);
    h2["Quseir"] = new ConnectedNode("Quseir" , 59);
    h2["Mut"]    = new ConnectedNode("Mut"    , 65);
    h2["Kharga"] = new ConnectedNode("Kharga" , 38);
    h2["Sohag"]  = new ConnectedNode("Sohag"  , 36);
    h2["Qena"]   = new ConnectedNode("Qena"   , 19);
    h2["Luxor"]  = new ConnectedNode("Luxor"   , 0);

    // Run the Search Function
    // Argument 0 = map of all nodes
    // Argument 1 = queue of expanded nodes
    // Argument 2 = Goal Node
    GeneralSearch(cityNodes, currentNodes, exploredNodes, cityNodes["Luxor"], h1, h2);

    // Make sure to deallocate everything on the heap
    std::map<std::string, Node*>::iterator mapIterator = cityNodes.begin();

    for (mapIterator = cityNodes.begin(); mapIterator != cityNodes.end(); ++mapIterator)
    {
        delete mapIterator->second;
    }
    cityNodes.clear();
    currentNodes.clear();

    std::map<std::string, ConnectedNode*>::iterator tableIterator;

    // Make sure to deallocate the tables when finished
    for (tableIterator = h1.begin(); tableIterator != h1.end(); ++tableIterator)
    {
        delete tableIterator->second;
    }
    h1.clear();

    for (tableIterator = h2.begin(); tableIterator != h2.end(); ++tableIterator)
    {
        delete tableIterator->second;
    }
    h2.clear();

    // Exit

    std::cout << "Exiting..." << std::endl;

    return 0;
}

void GeneralSearch(std::map<std::string, Node*> &cityNodes, std::vector<Node*> &currentNodes, std::vector<Node*> &exploredNodes, Node *goalNode,
                   std::map<std::string, ConnectedNode*> &h1, std::map<std::string, ConnectedNode*> &h2){
    while (true)
    {
        // If nothing left to search, then exit
        if (currentNodes.size() == 0)
        {
            std::cerr << "ERROR: Path to Goal not found: " << goalNode->name << std::endl;
            return;
        }

        // Grab the first node off of the currentNodes queue
        Node* nodeToTest = currentNodes[0];
        currentNodes.erase(currentNodes.begin());

        // Goal Test
        if (GoalTest(nodeToTest, goalNode))
        {
            // Output the list of cities searched here
            std::cout << "Order of cities traversed: " << std::endl;
            for (unsigned int i = 0; i < exploredNodes.size(); i++)
            {
                std::cout << exploredNodes[i]->name;
                if (i != exploredNodes.size() - 1)
                {
                    std::cout << ", ";
                }
                else
                {
                    std::cout << ", " << goalNode->name << std::endl;
                }
            }
            return;
        }

        // Queuing Function
        //EnqueueGreedy(cityNodes, currentNodes, nodeToTest, h1); // Greedy Search H1
        //EnqueueGreedy(cityNodes, currentNodes, nodeToTest, h2); // Greedy Search H2
        //EnqueueAStar(cityNodes, currentNodes, nodeToTest, h1); // AStar Search H1
        EnqueueAStar(cityNodes, currentNodes, nodeToTest, h2); // AStar Search H2

        exploredNodes.push_back(nodeToTest);

//        // Print out the explored nodes list
//        for (int i = 0; i < exploredNodes.size(); i++)
//        {
//            std::cout << exploredNodes[i]->name << " ";
//        }
//        std::cout << std::endl;
//
//        for (int i = 0; i < currentNodes.size(); i++)
//        {
//            std::cout << currentNodes[i]->name << " " << currentNodes[i]->gCost << " ";
//        }
//        std::cout << std::endl;
    }
}

void EnqueueBFS(std::map<std::string, Node*> &cityNodes, std::vector<Node*> &currentNodes, Node *nodeToTest)
{
    // Add values from expanded node into a temp vector
    std::vector<std::string> expandedNames;

    for (unsigned int i = 0; i < nodeToTest->children.size(); i++)
    {
        if (!cityNodes[nodeToTest->children[i].name]->isQueued) // Check to see if the node has already been expanded
        {
            expandedNames.push_back(nodeToTest->children[i].name);
        }
    }

    // Sort Them
    std::sort(expandedNames.begin(), expandedNames.end());

    // Add them into the currentNodes Queue
    // Insert each element into the back of the vector,
    // as seen with a queue data structure
    while (!expandedNames.empty())
    {
        currentNodes.push_back(cityNodes[expandedNames[0]]);
        cityNodes[expandedNames[0]]->isQueued = true;
        expandedNames.erase(expandedNames.begin());
    }
}

void EnqueueDFS(std::map<std::string, Node*> &cityNodes, std::vector<Node*> &currentNodes, Node *nodeToTest)
{
    // Add values from expanded node into a temp vector
    std::vector<std::string> expandedNames;

    for (unsigned int i = 0; i < nodeToTest->children.size(); i++)
    {
        if (!cityNodes[nodeToTest->children[i].name]->isQueued) // Check to see if the node has already been expanded
        {
            expandedNames.push_back(nodeToTest->children[i].name);
        }
    }

    // Sort Them
    std::sort(expandedNames.begin(), expandedNames.end());

    // Add them into the currentNodes Stack in reverse order
    // so currentNodes acts like a stack, and the node that
    // is first in the temp list comes up first.
    while (!expandedNames.empty())
    {
        currentNodes.insert(currentNodes.begin(), cityNodes[expandedNames[expandedNames.size() - 1]]);
        cityNodes[expandedNames[expandedNames.size() - 1]]->isQueued = true;
        expandedNames.erase(expandedNames.end());
    }
}

void EnqueueUCS(std::map<std::string, Node*> &cityNodes, std::vector<Node*> &currentNodes, Node *nodeToTest)
{
    isUCS = true;
    for (unsigned int i = 0; i < nodeToTest->children.size(); i++)
    {
        if (!cityNodes[nodeToTest->children[i].name]->isQueued) // Check to see if the node has already been expanded
        {
            currentNodes.push_back(cityNodes[nodeToTest->children[i].name]);
            currentNodes[currentNodes.size() - 1]->gCost = nodeToTest->gCost + nodeToTest->children[i].cost;
            currentNodes[currentNodes.size() - 1]->isQueued = true;
        }
        // Check where the cost for something to a node is less than another way, and overwrite the more expensive cost
        else if (nodeToTest->gCost + nodeToTest->children[i].cost < cityNodes[nodeToTest->children[i].name]->gCost)
        {
            // This is why I like pointers -> I do not need to loop again to find what I need to change
            cityNodes[nodeToTest->children[i].name]->gCost = nodeToTest->gCost + nodeToTest->children[i].cost;
        }
    }

    // Sort Them -> First based upon cost, and if they are the same, then by name
    // Refer to functorUCS for the specific comparison used for std::sort()
    // Notice I do not need a temp list here, I am adding straight to currentNodes
    std::sort(currentNodes.begin(), currentNodes.end(), functorUCS);
}

void EnqueueGreedy(std::map<std::string, Node*> &cityNodes, std::vector<Node*> &currentNodes, Node *nodeToTest, std::map<std::string, ConnectedNode*> &hTable)
{
    // For greedy search, always sort the entire queue based upon h(x)
    // of who enters, versus just a level of nodes. Refer to lecture 6 -> p.42

    for (unsigned int i = 0; i < nodeToTest->children.size(); i++)
    {
        if (!cityNodes[nodeToTest->children[i].name]->isQueued) // Check to see if the node has already been expanded
        {
            currentNodes.push_back(cityNodes[nodeToTest->children[i].name]);
            currentNodes[currentNodes.size() - 1]->gCost = 0;
            currentNodes[currentNodes.size() - 1]->hCost = hTable[nodeToTest->children[i].name]->cost;
            currentNodes[currentNodes.size() - 1]->isQueued = true;
        }
    }

    // Sort Them -> First based upon cost, and if they are the same, then by name
    // Refer to functorUCS for the specific comparison used for std::sort()
    // Notice I do not need a temp list here, I am adding straight to currentNodes
    std::sort(currentNodes.begin(), currentNodes.end(), functorAStar);
}

void EnqueueAStar(std::map<std::string, Node*> &cityNodes, std::vector<Node*> &currentNodes, Node *nodeToTest, std::map<std::string, ConnectedNode*> &hTable)
{
    // For A* search, always sort the entire queue based upon total cost
    // of who enters, versus just a level of nodes. Refer to lecture 6 -> p.46
    isUCS = true;

    for (unsigned int i = 0; i < nodeToTest->children.size(); i++)
    {
        if (!cityNodes[nodeToTest->children[i].name]->isQueued) // Check to see if the node has already been expanded
        {
            currentNodes.push_back(cityNodes[nodeToTest->children[i].name]);
            currentNodes[currentNodes.size() - 1]->gCost = nodeToTest->gCost + nodeToTest->children[i].cost; // This is g(x), as in UCS
            currentNodes[currentNodes.size() - 1]->hCost = hTable[nodeToTest->children[i].name]->cost; // This is h(x) for A*
            currentNodes[currentNodes.size() - 1]->isQueued = true;
        }
        // Check where the cost for something to a node is less than another way, and overwrite the more expensive cost
        // Formula: nodeToTest g(x) + child g(x) + child h(x) < current inherited child g(x) + child h(x)
        // Which derives back to: nodeToTest g(x) + child g(x) < current inherited child g(x) -> child h(x) cancels out
        else if (nodeToTest->gCost + nodeToTest->children[i].cost < cityNodes[nodeToTest->children[i].name]->gCost)
        {
            // This is why I like pointers -> I do not need to loop again to find what I need to change
            cityNodes[nodeToTest->children[i].name]->gCost = nodeToTest->gCost + nodeToTest->children[i].cost;
        }
    }

    // Sort Them -> First based upon cost, and if they are the same, then by name
    // Refer to functorUCS for the specific comparison used for std::sort()
    // Notice I do not need a temp list here, I am adding straight to currentNodes
    std::sort(currentNodes.begin(), currentNodes.end(), functorAStar);
}

// Function for GoalTest -> Declared here versus inside GeneralSearch() to make things cleaner
bool GoalTest(Node *nodeToTest, Node *goalNode)
{
    if (!isUCS) // If the Test is for BFS or DFS
    {
        if (nodeToTest->name == goalNode->name)
        {
            std::cout << "Found GOAL!!!!! -> " << goalNode->name << std::endl;
            return true;
        }
    }
    else // The test is for UCS, and it is a little different
    {
        if (nodeToTest->name == goalNode->name) // Should I stop on first hit or not?
        {
            std::cout << "Found GOAL!!!!! -> " << goalNode->name << std::endl;
            std::cout << "Cost g(x) to get to GoalNode: " << goalNode->gCost << std::endl;
            return true;
        }
    }
    return false;
}
