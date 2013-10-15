/**
 * File: pathfinder-graph.cpp
 * --------------------------
 * Provides the (fairly obvious) implementation of
 * the PathfinderGraph class.
 */


template <typename NodeType,typename ArcType>
void PathfinderGraph <NodeType,ArcType>::setMapFile(const string& filename) {
    mapFile = filename;
    highlightedNode = NULL;
    highlightedArc  = NULL;
}

template <typename NodeType,typename ArcType>
const string& PathfinderGraph <NodeType,ArcType>::getMapFile() const {
    return mapFile;
}

template <typename NodeType,typename ArcType>
void PathfinderGraph <NodeType,ArcType>::setHighlightedNode(NodeType *node) {
    highlightedNode = node;
    
}

template <typename NodeType,typename ArcType>
NodeType *PathfinderGraph <NodeType,ArcType>::getHighlightedNode() const {
    return highlightedNode;
}

template <typename NodeType,typename ArcType>
void PathfinderGraph <NodeType,ArcType>::setHighlightedArc(ArcType *arc) {
    highlightedArc = arc;
    
}
