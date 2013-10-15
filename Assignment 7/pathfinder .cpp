/**
 * File: pathfinder.cpp
 * --------------------
 * This is the primary file where you'll place most of your code.
 */


#include "path.h"

using namespace std;


string image;          // global variable

// functions used in the program

static void quitAction();

static void giveInstructions();

static void createDifferentMap(PathfinderGraph<cityT, distanceT> & graphT);

void readDatafromFile(PathfinderGraph<cityT, distanceT> & graphT);
void createNodes(string line, PathfinderGraph<cityT, distanceT> & graphT );
void createArcs(string line,PathfinderGraph<cityT, distanceT> & graphT);
void makeArcs ( cityT *n1, cityT *n2, double distance, PathfinderGraph<cityT, distanceT> & graphT);
Path findShortestPath( cityT* start, cityT * finish,PathfinderGraph<cityT, distanceT> & graphT);

void implementDijkstraAlgorithim (PathfinderGraph<cityT, distanceT> & graphT);

void implementKruskalsAlgorithim(PathfinderGraph<cityT, distanceT> & graphT);

bool twoEndpointsAreInTheSameSet(cityT* start, cityT* finish,  Map <string,  Set <cityT *> > & connections, PathfinderGraph<cityT, distanceT> & graphT);
bool areAllNodesInASet (Map <string,  Set <cityT*> > & connections, PathfinderGraph<cityT, distanceT> & graphT);
bool doesSetContainAllNodes (Set <cityT*> sets, Vector<cityT*> allTheCities, int index);

void drawMap (PathfinderGraph<cityT, distanceT> & graphT, string color);

void createInitialMap ( PathfinderGraph<cityT, distanceT> & graphT);






/**
 * Function: main
 * --------------
 * Defines the entry point for the entire application.
 */
int main() {
    GWindow gw(kWindowWidth, kWindowHeight + kControlStripHeight);
    initPathfinderGraphics(gw);
    giveInstructions();
    PathfinderGraph<cityT, distanceT> graphT;
    

    addButton("Map", createDifferentMap, graphT);
    addButton("Dijkstra", implementDijkstraAlgorithim, graphT);
    addButton("Kruskal", implementKruskalsAlgorithim, graphT);
    addButton("Quit", quitAction);
    
    
    readDatafromFile(graphT);
    
    pathfinderEventLoop();
    
    return 0;
}

/**
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Describes the Pathfinder assignment on the console.  This text has
 * been retained in its original form to preserve the assignment history.
 */
static void giveInstructions() {
    cout << "This masterful piece of work is a graph extravaganza!" << endl;
    cout << "The main attractions include a lovely visual presentation" << endl;
    cout << "of the graph along with an implementation of Dijkstra's" << endl;
    cout << "shortest path algorithm and Kruskal's computation of" << endl;
    cout << "a minimal spanning tree.  Enjoy!" << endl << endl;
}


/**
 * Function: quitAction
 * Usage: quitAction(g);
 * ---------------------
 * Called when the user clicks the Quit button in the control strip.
 */
static void quitAction() {
   exitGraphics();
}

    
// This function reads data from a file using the ifstream object

void readDatafromFile( PathfinderGraph<cityT, distanceT> & graphT){
    
    bool readNodes = false;
    bool readArcs = false;
    ifstream fileReader;  
    string entry;

    
    while (true){
        cout << "Enter a file name: ";
         entry = getLine();
        fileReader.open(entry.c_str());
        if(fileReader.fail()){
            cout << "The file name is invalid" << endl;
            fileReader.clear();
           fileReader.close();
            continue;
        } else
            break;
        }
    
    string line;
    while (getline( fileReader, line)){
        
        
        if (line =="NODES")
            readNodes = true;
        if (line == "ARCS"){
            readArcs = true;
            readNodes = false;
        }
        if (readNodes && line != "NODES")
            createNodes(line, graphT);
        if (readArcs && line != "ARCS")
            createArcs(line, graphT);
        
    }
    
    
    if (entry == "Stanford2.txt")
        image = "Stanford.jpg";
    else if (entry == "USA2.txt")
        image = "USA.jpg";
    else if (entry == "MiddleEarth2.txt")
        image = "MiddleEarth.jpg";
    
    
    drawMap(graphT, "black");

    
        
}

 
// This function draws the graph in a specific color

void drawMap (PathfinderGraph<cityT, distanceT> & graphT, string color){
    
    
    drawPathfinderMap(image);
    
    foreach( cityT * node in graphT. getNodeSet()){
        
        drawPathfinderNode(node -> loc ,color,  node -> name);
    }
    
    foreach(distanceT * arc in graphT. getArcSet()){
        drawPathfinderArc(arc -> start -> loc, arc -> finish -> loc, color);
    }
    
    
}


// This function creates the nodes on the graph

void createNodes(string line, PathfinderGraph<cityT, distanceT> & graphT ){
    
    TokenScanner scanner;
    scanner.setInput(line);
    scanner.ignoreWhitespace();
    int  xValue;
    int  yValue;
    
    
    cityT *n = new cityT;
    
    string value = scanner.nextToken();
    
    n -> name = value;
    
    xValue = stringToReal(scanner.nextToken());
    
    yValue = stringToReal(scanner.nextToken());
    
    GPoint pt(xValue,yValue);
    
    n -> loc = pt;
    
    graphT.addNode(n);
    
    
    
}

// This function creates all the arcs on the graph

void createArcs(string line, PathfinderGraph<cityT, distanceT> & graphT ){
    
    TokenScanner scanner;
    scanner.setInput(line);
    scanner.ignoreWhitespace();
    double distance;
    
    
    cityT *n1 = graphT.getNode(scanner.nextToken());
    cityT *n2 = graphT.getNode(scanner.nextToken());
    
    distance = stringToReal(scanner.nextToken());
    
    makeArcs( n1, n2, distance, graphT);
    makeArcs( n2, n1, distance, graphT);
    
    
}

void makeArcs ( cityT *n1, cityT *n2, double distance, PathfinderGraph<cityT, distanceT> & graphT){
    
    distanceT *a = new distanceT;
    a -> start = n1;
    a -> finish = n2;
    a -> cost = distance;
    n1 -> arcs.add(a);
    graphT.addArc(a);
    
    
}


// callback function for the Map button
// called when the user clicks the Map button

static void createDifferentMap(PathfinderGraph<cityT, distanceT> & graphT){
    graphT.clear();
    readDatafromFile(graphT);
    

}

//This function finds the shortest path given a start and a end node.
// This is the implementation of the kruskal's algorithim using the path class that I created

Path findShortestPath( cityT* start, cityT * finish,PathfinderGraph<cityT, distanceT> & graphT ){
    
    Path  paths;

    PriorityQueue<Path > pqueues;

    Map <string, double> fixed;

    
    
    while (start != finish){
        if (!fixed.containsKey(start -> name)){
            fixed.put(start -> name, paths.getDistance());
            
            foreach (distanceT * dist in graphT.getArcSet(start)){
               if (!fixed.containsKey(dist -> finish -> name)){
                
                Path newPaths = paths;
                
                newPaths.addStructure(dist, dist -> cost);
                pqueues. enqueue(newPaths, newPaths.getDistance());
                     }
            }
        }
        
                    if (pqueues.isEmpty()) return Path ();
                    paths = pqueues.dequeue();
            start =  paths. endValue()-> finish;
                                
        
    }                    return paths;
                                

}

bool islocationPresent (GPoint point, Vector <GPoint> mine){
    for (int i = 0; i< mine .size(); i++){
        if (mine[i] == point)
            return true;
    }
    return false;
        

        }
                              
// Callback function for the Dijkstra button
// This function is called when the Dijkstra button is clicked on

void implementDijkstraAlgorithim (PathfinderGraph<cityT, distanceT> & graphT){
    cityT * start;
    cityT * finish;
    string color = "red";
    
    drawMap(graphT, "black");
        
    bool foundAMatchStartNode = false;
    bool foundAMatchFinishNode = false;
    
    Vector <GPoint> listOFNodeLocations;
    foreach( cityT * city in graphT. getNodeSet()){
        listOFNodeLocations.add(city -> loc);
    }
    
    // code to find the startign cityT
    
    while (true) {
    cout << "Click on starting location" << endl;
    GPoint click = getMouseClick();
        
            foreach(cityT * cityT in graphT. getNodeSet()){
                double radius = 3.5;
                double xc = cityT->loc.getX();
                double yc = cityT->loc.getY();
                
                double x = click.getX();
                double y = click.getY();
                
                if ((xc-x)*(xc-x) + (yc-y)*(yc-y) <= radius*radius ){
                    start = cityT;
                    drawPathfinderNode(start -> loc, color);
                     foundAMatchStartNode= true;
                    break;
                    
                } 
            
 
            }if (foundAMatchStartNode)
              break;
             else
                 cout << "Invalid starting location" << endl;

        
    }
        
            
    // code to get the finish cityT
    
    while (true) {
        cout << "Click on ending location" << endl;
        GPoint click = getMouseClick();
        foreach(cityT * cityT in graphT. getNodeSet()){
            double radius = 3.5;
            double xc = cityT->loc.getX();
            double yc = cityT->loc.getY();
            
            double x = click.getX();
            double y = click.getY();
            
            if ((xc-x)*(xc-x) + (yc-y)*(yc-y) <= radius*radius ){
                finish = cityT;
                drawPathfinderNode(finish -> loc, color);
                foundAMatchFinishNode = true;
                break;
                
        }
            
            }
        if (foundAMatchFinishNode)
            break;
        else
            cout << "Invalid starting location" << endl;
                                    
    }
        
 // Code for highlighting the final path
    
    Path mine =  findShortestPath( start, finish, graphT);
    Vector <distanceT *> good = mine.highLighthPath();
    string colors = "Red";
    
    for (int i = 0; i < good.size(); i++){
        drawPathfinderArc(good[i] -> start -> loc, good[i] -> finish -> loc, colors);
        
    }
    
    
}

// Callback function for the Kruskal button
// This function is called when the Kruskal button is clicked on

void implementKruskalsAlgorithim(PathfinderGraph<cityT, distanceT> & graphT){
    
    PriorityQueue<distanceT *> pqueue;
    Map <string, Set <cityT*> > connections;
    Vector<distanceT *> pathsToBeHIghlighted;
    
    
 // Initialize map with the initial node connections
    
    foreach( cityT * mine in graphT. getNodeSet()){
        Set< cityT * > nodes;
        nodes.add(mine);
        connections[mine -> name] = nodes;
    }
  // First, I add all the arcs to a priority queue
    
    foreach(distanceT * distanceT in graphT.getArcSet()){
        pqueue.enqueue(distanceT, distanceT -> cost);
    }

    while(!pqueue.isEmpty()){
        distanceT * minimalArc = pqueue. dequeue();
        cityT * firstNode = minimalArc -> start;
        cityT * endNode = minimalArc -> finish;
        
        if((!twoEndpointsAreInTheSameSet(firstNode, endNode, connections, graphT)) && !areAllNodesInASet(connections, graphT)){
            
            
            pathsToBeHIghlighted.add(minimalArc);
            
            Set<cityT *> valuesOfFirstNode = connections.get(firstNode -> name);
            Set <cityT *> nodesOfSecondNode = connections.get(endNode -> name);
            Set <cityT *> combinedSet = valuesOfFirstNode + nodesOfSecondNode;
            connections[firstNode -> name] = combinedSet;
            connections[endNode -> name] = combinedSet;
            
            
            foreach(cityT * city in combinedSet)
                connections[city -> name] = combinedSet;
            
            foreach(cityT * city in valuesOfFirstNode){
               Set <cityT*> mine = connections.get(city -> name);
                
            }
            
        } 
        
    }
        
    drawPathfinderMap(image);
    string color = "red";
    
    foreach( cityT * node in graphT. getNodeSet()){
        
        drawPathfinderNode(node -> loc ,color,  node -> name);
    }
    
    for(int i = 0; i < pathsToBeHIghlighted.size(); i++){
        drawPathfinderArc(pathsToBeHIghlighted[i] -> start -> loc, pathsToBeHIghlighted[i] -> finish -> loc, color);
        }
    
    
}

// This is to check if the given two endpoints can form a cycle

bool twoEndpointsAreInTheSameSet(cityT* start, cityT* finish,  Map <string,  Set <cityT *> >  &connections, PathfinderGraph<cityT, distanceT> & graphT){
    
    foreach(cityT* city in graphT.getNodeSet()){
        Set <cityT *> cities = connections.get(city -> name);
        if (cities.contains(start) && cities.contains(finish)){
            return true;
        }
        
    } return false;
}

// This is to check if any set contains all the nodes in the graph. If this is true, it also means that the kruskal's algorithim is done

bool areAllNodesInASet (Map <string,  Set <cityT *> > & connections, PathfinderGraph<cityT, distanceT> & graphT){
    
    Vector<cityT *> allTheCities;
    
// adding all the cities to one vector
    foreach(cityT* cityT in graphT.getNodeSet()){
        allTheCities.add(cityT);
    }

// checks if any one set has all the cities using the bool doesSetContainNodes
    
  foreach(cityT * city in graphT.getNodeSet()){
    Set <cityT *> cities = connections.get(city -> name);
    if (doesSetContainAllNodes(cities, allTheCities, 0))
        return true;

       }return false;
    }         


// This function checks if any set contains all the nodes in the graph.

bool doesSetContainAllNodes (Set <cityT*> sets, Vector<cityT*> allTheCities, int index){
    if (index == allTheCities.size() - 1)
        return true;
    
 if (sets.contains(allTheCities.get(index)))
     return doesSetContainAllNodes(sets, allTheCities, index + 1);
   else
       return false;
}










