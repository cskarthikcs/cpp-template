#ifndef A_HPP
#define A_HPP

//---------------------------------------------------------------------------
// Graph handling and searching routines
// --------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <algorithm>


typedef unsigned long DataType;
typedef unsigned long IndexType;

class Edge
{
public:
    Edge(IndexType edgeEnd, DataType edgeCost=1):  m_edgeEnd(edgeEnd), m_edgeCost(edgeCost), m_edgeConverted(false)
	{}

    // General data
    IndexType m_edgeEnd; // Node to which the edge connects from the current node
    DataType m_edgeCost; // Cost of passing through edge, used by some shortest path finding algorithms

    // Scc data
    bool m_edgeConverted; // True if the node end was updated with updateNodeIdx()

};


typedef std::vector<Edge> Edges; // Edges data type


const unsigned long InitialEdgeNumber = 20;

enum ExploreDirection { Forward, Backward }; //  Flag marking node traversing direction

class Node
{
public:
    // General functions

    Node(): m_explored(false), m_edgesOut(), m_edgesIn(),
        m_leader(NULL), m_nodeDepth(0)
	{
        m_edgesIn.reserve(InitialEdgeNumber);
        m_edgesOut.reserve(InitialEdgeNumber);
	}

    void addEdgeOut(Edge edge) { m_edgesOut.push_back(edge); }
	void addEdgeIn(Edge edge) { m_edgesIn.push_back(edge); }

    void setExplored (bool explored) { m_explored = explored; }
    bool isExplored() {return m_explored;}

    bool isConnectedTo (IndexType otherNode)
    {
        for (Edges::const_iterator i = m_edgesOut.begin(); i != m_edgesOut.end(); ++i)
        {
            if ( i->m_edgeEnd == otherNode )
                return true;
        }

        return false;
    }

    long getEdgeCost(IndexType otherNode)
    {
        for (Edges::const_iterator i = m_edgesOut.begin(); i != m_edgesOut.end(); ++i)
        {
            if ( i->m_edgeEnd == otherNode )
                return i->m_edgeCost;
        }

        return -1; // No edge with given endNode
    }

    Edges& getEdges(ExploreDirection direction=Forward)
    {
        return (direction == Forward)? m_edgesOut: m_edgesIn;
    }

    void setLeader(Node* node) { m_leader = node;}
    Node* getLeader() { return m_leader;}

    void setNodeDepth(DataType deph) { m_nodeDepth = deph; }
    DataType getNodeDepth() { return m_nodeDepth; }


 private:

    // General data
    bool m_explored; // True if node was already explored by the running algorithm
    Edges m_edgesOut; // Edges outgoing from the node
    Edges m_edgesIn; // Edges incoming to the node


    Node* m_leader; // Leader of discovered group in a graph search
    DataType m_nodeDepth; // node depth in graph search from the leader



};

const unsigned long DefaultGraphSpace = 1000;
typedef std::vector<Node> GraphData;


class Graph
{
public:
    Graph(unsigned long initialGraphSize = 0, unsigned long predictedGraphSize = DefaultGraphSpace):
        m_graphData(initialGraphSize)
    {
        if (predictedGraphSize > initialGraphSize)
            m_graphData.reserve(predictedGraphSize);
    }


    unsigned long size() { return m_graphData.size(); }

    // Adds a new node to the graph and returns its index
    IndexType addNode()
    {
        m_graphData.push_back(Node());
        return m_graphData.size() - 1;
    }

    // Adds an edge between existing nodes
    void addEdge(IndexType startNode, IndexType endNode, DataType edgeCost=1)
    {
        assert( ! isNodeConnectedTo(startNode,endNode) );
        assert( ! isNodeConnectedTo(endNode,startNode) );

        m_graphData[startNode].addEdgeOut(Edge(endNode,edgeCost));
        m_graphData[endNode].addEdgeIn(Edge(startNode,edgeCost));
    }

    bool isNodeConnectedTo(IndexType startNode, IndexType endNode)
    {
        return m_graphData[startNode].isConnectedTo(endNode);
    }

    Node& operator [] (IndexType idx) { return m_graphData[idx];}


    // Breadth First Search for all nodes
    void totalBFS()
    {
        for (IndexType i = 1; i < m_graphData.size(); ++i)
        {
            if ( ! m_graphData[i].isExplored() )
            {
                std::cout << "Starting BFS with node: " << i << std::endl;
                singleBFS(m_graphData[i]);

            }
        }
   }

    // Breadth First Search starting from a single node
    void singleBFS(Node& startingNode)
    {
        std::queue<Node*> bfsQueue;
        startingNode.setExplored(true);
        startingNode.setLeader(&startingNode);
        startingNode.setNodeDepth(0);
        bfsQueue.push(&startingNode);

        std::cout << "Discovered: ";
        while ( ! bfsQueue.empty() )
        {
            Node* currNode = bfsQueue.front();
            const Edges& currNodeEdges = currNode->getEdges();
            for (Edges::const_iterator i = currNodeEdges.begin(); i != currNodeEdges.end(); ++i)
            {
                IndexType newNodeIndex = i->m_edgeEnd;
                Node& nextNode = m_graphData[newNodeIndex];
                if (! nextNode.isExplored() )
                {
                    nextNode.setExplored(true);
                    nextNode.setLeader(&startingNode);
                    nextNode.setNodeDepth(currNode->getNodeDepth() + 1);
                    bfsQueue.push(&nextNode);
                    std::cout << newNodeIndex << "(d:" << nextNode.getNodeDepth() << "),";
                }
            }
            bfsQueue.pop();
        }
        std::cout << std::endl;

    }


    // Depth First Search for all nodes
    void totalDFS()
    {
        for (IndexType i = 1; i < m_graphData.size(); ++i)
        {
            if ( ! m_graphData[i].isExplored() )
            {
                std::cout << "Starting DFS with node: " << i << std::endl;
                singleDFS(m_graphData[i]);
                std::cout << std::endl;

            }
        }
   }


    // Depth First Search for single node
    void singleDFS(Node& startingNode, Node* parentNode = NULL)
    {
        startingNode.setExplored(true);
        if (parentNode == NULL) // Current node is the top most parent (leader)
        {
            startingNode.setNodeDepth(0);
            startingNode.setLeader(&startingNode);
            std::cout << "Discovered: ";
        }
        else
        {
            startingNode.setNodeDepth(parentNode->getNodeDepth() + 1);
            startingNode.setLeader(parentNode);
        }

        const Edges& currNodeEdges = startingNode.getEdges();
        for (Edges::const_iterator i = currNodeEdges.begin(); i != currNodeEdges.end(); ++i)
        {
            IndexType newNodeIndex = i->m_edgeEnd;
            Node& nextNode = m_graphData[newNodeIndex];
            if (! nextNode.isExplored() )
            {
                std::cout << newNodeIndex << "(d:" << startingNode.getNodeDepth() + 1 << "),";
                singleDFS(nextNode, &startingNode);

            }
        }
    }

    // To make possible another unrelated search, may be not enough if edges were altered (like Scc)
    void resetSearchData()
    {
        for (GraphData::iterator i = m_graphData.begin(); i != m_graphData.end(); ++i)
        {
            i->setExplored(false);
            i->setLeader(NULL);
            i->setNodeDepth(0);
        }
    }


private:
    GraphData m_graphData; // Container of graph nodes

};


namespace Dijkstra
{

std::vector<DataType> distance;

void readGraphFromFile(const char* fileName, Graph& nodes)
{
    std::ifstream filestream;
    filestream.open(fileName);
    int lineNumber = 0;

     if (filestream.is_open())
     {
         while (filestream.good() && !filestream.eof())
         {
             IndexType startNode = 0;
             IndexType endNode = 0;
             DataType edgeCost = 0;

             lineNumber++;

             if (filestream >> startNode)
             {
                 if (filestream >> endNode)
                 {
                     if (filestream >> edgeCost)
                     {
                         nodes.addEdge(startNode,endNode,edgeCost);
                     }
                     else
                         std::cout << "Error reading edge cost at line "  << lineNumber << std::endl;
                 }
                else
                     std::cout << "Error reading end node at line "  << lineNumber<< std::endl;
             }
             else
             {
                 if (!filestream.eof())
                    std::cout << "Error reading start node at line "  << lineNumber<< std::endl;
             }


         }
     }

     std::cout << "Read " << lineNumber << " lines" << std::endl;
}


class PriorityComparer
{
public:
    bool operator () (IndexType elem1,IndexType elem2) const 
    { 
	    return distance[elem1] > distance[elem2]; // Bigger distance value gets smaller priority (default comparer is std::less)
	}
};

// Dijkstra shortest path algorithm using pririty queue, mostly based on the Wikipedia example
long findShortestPath(Graph& nodes, IndexType startNode, IndexType endNode)
{
    const DataType Infinity = 99999;
    const DataType Unknown = 0;

    distance.resize(nodes.size());
    std::vector<DataType> previous(nodes.size());

    for (IndexType i=1; i < distance.size(); ++i)
    {
        distance[i] = Infinity;
        previous[i] = Unknown;
    }

    distance[startNode] = 0;

    std::priority_queue<IndexType, std::vector<IndexType>, PriorityComparer> priorityQueue;

    priorityQueue.push(startNode);

    while (!priorityQueue.empty())
    {
        // Pick the closest node (first in priority queue)
	    IndexType nextNode = priorityQueue.top();
        priorityQueue.pop();
        nodes[nextNode].setExplored(true);
        
        if (nextNode == endNode) // Final node found
        {
            DataType pathLength = distance[nextNode];
	        std::cout << "ShortestPath (length:" << pathLength << "): ";
            std::cout << nextNode;
            IndexType lastNode = nextNode;
            while ( (nextNode = previous[nextNode]) != Unknown)
            {
                std::cout << "-" << nextNode << "(d:" << nodes[nextNode].getEdgeCost(lastNode) << ")";
                lastNode = nextNode;
            }
            std::cout << std::endl;    

            return pathLength;
        }
        else
        {
	        // Handle nodes in the neighbourhood, connected through direct edges
	        Edges& edgesOut = nodes[nextNode].getEdges();
	    	for (Edges::iterator i = edgesOut.begin(); i != edgesOut.end(); i++)
        	{
	        	DataType nodeDistance = distance[nextNode] + nodes[nextNode].getEdgeCost(i->m_edgeEnd);
	        	
	        	if ( distance[i->m_edgeEnd] == Infinity) // Node not in the queue yet, add it
	        	{
	        		distance[i->m_edgeEnd] = nodeDistance;
		        	priorityQueue.push(i->m_edgeEnd);
		        	previous[i->m_edgeEnd] = nextNode;
        		}
        		else if ( ! nodes[i->m_edgeEnd].isExplored() ) // Node still in the queue, update its distance if needed
        		{
	        		if ( nodeDistance < distance[i->m_edgeEnd] )
	        		{
	        			distance[i->m_edgeEnd] = nodeDistance;
        				previous[i->m_edgeEnd] = nextNode;
	        		}
	        				
	        	}
	        }
	    }
    }

	return -1; // No path found
}

} // End of namespace Dijkstra


namespace Scc
{

    typedef std::map<IndexType,IndexType> IndexMap;


    // Scc data types
    typedef std::vector<IndexType> Results;

    // Scc globals
    DataType t = 0;
    Node* currentLeader = NULL;
    IndexMap imap; // Index map
    IndexType nodeCounter = 0;


    // Scc functions

    Node& getRemappedNode(Graph& nodes, IndexType idx)
    {
        return nodes[imap[idx]];
    }

    void initIndexMap(unsigned long size)
    {
        for (IndexType i=1; i<size; i++)
            imap[i] = i;
    }


    void updateNodeIdx(Node& node, IndexType idx, IndexType newNodeId)
    {
        Edges& edgesOut = node.getEdges();

        for (Edges::iterator i = edgesOut.begin(); i != edgesOut.end(); i++)
        {
            if ( (i->m_edgeEnd == idx) && !i->m_edgeConverted )
            {
                i->m_edgeEnd = newNodeId;
                i->m_edgeConverted = true;
            }
        }

    }


    void translateNodes(Graph& nodes)
    {
        //std::cout << "Translated nodes: ";
        for (IndexType i=1; i<nodes.size(); i++)
        {
            Node& node = nodes[i];
            IndexType newNodeId = node.getNodeDepth();
            if ( node.isExplored() ) // node is valid
            {
                imap[newNodeId] = i;
                //std::cout << newNodeId << "(" << i << ") ";

                const Edges& edges = node.getEdges(Backward);
                for (Edges::const_iterator it = edges.begin(); it != edges.end(); it++)
                {
                    updateNodeIdx(nodes[it->m_edgeEnd],i, newNodeId);
                }
                node.setExplored(false);
            }

        }

        std::cout << std::endl;
    }



    void explore(Graph& nodes, IndexType startNode, ExploreDirection direction = Forward)
    {
        assert (startNode > 0);
        Node& node = getRemappedNode(nodes, startNode);
        const Edges& edges = node.getEdges(direction);

        if ( node.getLeader() == NULL )
            node.setLeader(currentLeader);
        else
        {
            if ( (node.getLeader() != currentLeader) )
                return;
        }

        node.setExplored(true);

        //std::cout << startNode << " ";
        nodeCounter++;
        for (Edges::const_iterator i = edges.begin(); i != edges.end(); i++)
        {
            if ( ! getRemappedNode(nodes, i->m_edgeEnd).isExplored() )
                explore(nodes, i->m_edgeEnd, direction);
        }
        t++;
        node.setNodeDepth(t);

    }

    void DFS(Graph& nodes, Results& results, ExploreDirection direction = Forward)
    {

        for (IndexType i=nodes.size()-1; i>0; i--)
        {
            Node& node = getRemappedNode(nodes, i);

            if  ( ! node.isExplored() )
            {
                if (node.getLeader() != NULL)
                    currentLeader = node.getLeader();
                else
                    currentLeader = &node;
                //std::cout << "Explored nodes: ";
                nodeCounter = 0;
                explore(nodes, i, direction);
                if (direction == Forward)
                    results.push_back(nodeCounter);
                //std::cout << "total: " << nodeCounter << std::endl;

            }
        }

    }


    void readGraphFromFile(const char* fileName, Graph& nodes)
    {
        FILE* file = fopen (fileName, "r" );
        char buff[100] = {0};
        char* textNumber = NULL;
        IndexType nodeIdx;
        assert (file != NULL);

        while (fgets (buff , 100 , file) != NULL)
        {
            textNumber = strtok(buff," \t\r\n");
            assert (textNumber != NULL);
            nodeIdx = atoi(textNumber);
            while ( (textNumber = strtok(NULL," \t\r\n")) != NULL )
            {
                int endEdge = atoi(textNumber);
                assert (endEdge > 0);
                nodes.addEdge(nodeIdx,endEdge);

            }
        }

        fclose(file);

    }

    bool mySortPred (IndexType i,IndexType j) { return (i>j); }

} // End of namespace SCC

#endif
