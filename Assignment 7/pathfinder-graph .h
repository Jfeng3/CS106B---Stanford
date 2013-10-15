/**
 * Exports a strongly typed subclass of the Graph template
 * that's Pathfinder-specific.
 */

#ifndef _pathfinder_graph_
#define _pathfinder_graph_

#include <string>
#include "graph.h"      // for template Graph class
#include "graphtypes.h" // for struct Node


/**
 * Class: PathfinderGraph
 * ----------------------
 * This class extends the standard Graph class so that the new
 * class incorporates the Node and Arc type parameters.  The
 * extended data structure also includes an image file name for
 * the map and the ability to designate a particular node as
 * highlighted.
 */
template <typename NodeType,typename ArcType>
class PathfinderGraph : public Graph<NodeType,ArcType> {
    
public:
    void setMapFile(const std::string& filename);
    const std::string& getMapFile() const;
    void setHighlightedNode(NodeType *node);
    NodeType *getHighlightedNode() const;
    void setHighlightedArc(ArcType *arc);
    
private:
    std::string mapFile;
    NodeType *highlightedNode;
    ArcType *highlightedArc;
};
#include "pathfinder-graph-implementation.h"

#endif
