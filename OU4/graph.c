#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
 
/*
 * Definition of a generic graph for the "Datastructures and
 * algorithms" courses at the Department of Computing Science, Umea
 * University. The graph stores nodes and edges of a directed or
 * undirected graph. After use, the function graph_kill() must
 * be called to de-allocate the dynamic memory used by the graph
 * itself. The de-allocation of any dynamic memory allocated for the
 * node names is the responsibility of the user of the graph.
 *
 * Authors: Jaffar El-Tai (hed20jei)
 *          Robin Lundin Söderberg (hed20rlg)
 *
 * Version 2
 */
 
// ====================== PUBLIC DATA TYPES ==========================
struct node
{
    char *dest_label;
    bool dest_seen;
    struct dlist *neighbour;
};
 
struct graph
{
    int max_nodes;
    struct dlist *node;
};
// =================== GRAPH STRUCTURE INTERFACE ======================
 
/**
 * graph_empty() - Create an empty graph.
 * @max_nodes: The maximum number of nodes the graph can hold.
 *
 * Returns: A pointer to the new graph.
 */
graph *graph_empty(int max_nodes)
{
    graph *g = malloc(sizeof(*g));
 
    g->node = dlist_empty(NULL);
 
    g->max_nodes = max_nodes;
    
    return g;
 
}
 
/**
 * graph_is_empty() - Check if a graph is empty, i.e. has no nodes.
 * @g: Graph to check.
 *
 * Returns: True if graph is empty, otherwise false.
 */
bool graph_is_empty(const graph *g)
{
    return(g->node == NULL);
}
 
/**
 * graph_insert_node() - Inserts a node with the given name into the graph.
 * @g: Graph to manipulate.
 * @s: Node name.
 *
 * Creates a new node with a copy of the given name and puts it into
 * the graph.
 *
 * Returns: The modified graph.
 */
graph *graph_insert_node(graph *g, const char *s)
{
    node *temp = malloc(sizeof(*temp));
    temp->dest_label = calloc((strlen(s)+1), sizeof(*s));
    strcpy(temp->dest_label, s);
    temp->dest_seen = false;
    temp->neighbour = dlist_empty(NULL);
    dlist_insert(g->node, temp, dlist_first(g->node));
 
    return g;
}
 
/**
 * graph_insert_edge() - Insert an edge into the graph.
 * @g: Graph to manipulate.
 * @n1: Source node (pointer) for the edge.
 * @n2: Destination node (pointer) for the edge.
 *
 * NOTE: Undefined unless both nodes are already in the graph.
 *
 * Returns: The modified graph.
 */
graph *graph_insert_edge(graph *g, node *n1, node *n2)
{
    dlist_insert(n1->neighbour, n2, dlist_first(n1->neighbour));
 
    return g;
}
 
/**
 * graph_find_node() - Find a node stored in the graph.
 * @g: Graph to manipulate.
 * @s: Node identifier, e.g. a char *.
 *
 * Returns: A pointer to the found node, or NULL.
 */
node *graph_find_node(const graph *g, const char *s)
{
    dlist_pos pos = dlist_first(g->node);
 
    while (!dlist_is_end(g->node, pos))
    {
        node *temp = dlist_inspect(g->node, pos);

        if (strcmp(temp->dest_label, s) == 0)
        {
            return temp;
        }
 
        pos = dlist_next(g->node, pos); 
    }
 
    return NULL; 
}
 
/**
 * nodes_are_equal() - Check whether two nodes are equal.
 * @n1: Pointer to node 1.
 * @n2: Pointer to node 2.
 *
 * Returns: true if the nodes are considered equal, otherwise false.
 *
 */
bool nodes_are_equal(const node *n1,const node *n2)
{
    if (strcmp(n1->dest_label, n2->dest_label) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}
 
/**
 * graph_node_is_seen() - Return the seen status for a node.
 * @g: Graph storing the node.
 * @n: Node in the graph to return seen status for.
 *
 * Returns: The seen status for the node.
 */
bool graph_node_is_seen(const graph *g, const node *n)
{
    dlist_pos pos = dlist_first(g->node);
 
    while (!dlist_is_end(g->node, pos))
    {
        node *temp = dlist_inspect(g->node, pos);
 
        if (strcmp(temp->dest_label, n->dest_label) == 0)
        {
            
            return n->dest_seen;
            
        }
 
        pos = dlist_next(g->node, pos); 
    }
 
    return false; 
}
 
/**
 * graph_node_set_seen() - Set the seen status for a node.
 * @g: Graph storing the node.
 * @n: Node in the graph to set seen status for.
 * @s: Status to set.
 *
 * Returns: The modified graph.
 */
graph *graph_node_set_seen(graph *g, node *n, bool seen)
{
    dlist_pos pos = dlist_first(g->node);
 
    while (!dlist_is_end(g->node, pos))
    {
        node *temp = dlist_inspect(g->node, pos);
 
        if (strcmp(temp->dest_label, n->dest_label) == 0)
        {
            n->dest_seen = seen;
        }
 
        pos = dlist_next(g->node, pos); 
    }
 
    return g; 
}
 
/**
 * graph_reset_seen() - Reset the seen status on all nodes in the graph.
 * @g: Graph to modify.
 *
 * Returns: The modified graph.
 */
graph *graph_reset_seen(graph *g)
{
    dlist_pos pos = dlist_first(g->node);
 
    while (!dlist_is_end(g->node, pos))
    {
        node *temp = dlist_inspect(g->node, pos);
        temp->dest_seen = false;
        pos = dlist_next(g->node, pos); 
    }
 
    return g; 
}
 
/**
 * graph_kill() - Destroy a given graph.
 * @g: Graph to destroy.
 *
 * Return all dynamic memory used by the graph.
 *
 * Returns: Nothing.
 */
void graph_kill(graph *g)
{
    dlist_pos pos = dlist_first(g->node);
 
    while (!dlist_is_end(g->node, pos))
    {
        node *temp = dlist_inspect(g->node, pos);
        dlist_kill(temp->neighbour);
        free(temp->dest_label);
        free(temp);
    
        pos = dlist_next(g->node, pos); 
    }
 
    dlist_kill(g->node);
    free(g);
}
 
/**
 * graph_neighbours() - Return a list of neighbour nodes.
 * @g: Graph to inspect.
 * @n: Node to get neighbours for.
 *
 * Returns: A pointer to a list of nodes. Note: The list must be
 * dlist_kill()-ed after use.
 */
dlist *graph_neighbours(const graph *g,const node *n)
{
    dlist_pos pos = dlist_first(n->neighbour);
    dlist *test = dlist_empty(NULL);
 
    while (!dlist_is_end(n->neighbour, pos))
    {
        
        dlist_insert(test, dlist_inspect(n->neighbour, pos), dlist_first(test));
        
        pos = dlist_next(n->neighbour, pos); 
    }
 
 
    return test;
}