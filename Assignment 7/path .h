/*
 * File: path.h
 * ------------
 * This file is the interface for a Path class, which consists of a
 * sequence of arcs.
 */

#ifndef _path_h
#define _path_h



#include "vector.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "pathfinder-graph.h"
#include "pathfinder-graphics.h"
#include "error.h"
#include "gwindow.h"
#include "map.h"
#include "pqueue.h"
#include "point.h"
#include "tokenscanner.h"
#include "set.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include "graph.h"
#include "pqueue.h"

using namespace std;
/*
   Class : Path <ValueType>
 
 */
struct distanceT;  // forward declaration

struct cityT {
    string name;
    Set <distanceT *> arcs;
    GPoint loc;
};

struct distanceT {
    cityT *start;
    cityT *finish;
    double cost;
    
};


class Path{
    
    
public:
    //Constructor
    Path();
    
    
    //Destructor
    ~Path();
    
    // Copy Constructor
    Path(const Path& path);
    
    // Equals Constructor
    Path& operator=(const Path& path);
    
    void addStructure(distanceT *  & mine, int number);
    
    int getDistance();
    
    distanceT* endValue();
    
    Vector<distanceT *> highLighthPath();
    
private:
    
    struct Entry{
        distanceT * value;
       Entry *next;
    };
    int totalDistance;
    Entry *list, *end;
    void Deallocate(Entry *  good);

    
};



#endif

