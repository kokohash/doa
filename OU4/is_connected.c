#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "graph.h"
#include "queue.h"
/*
 * Implementation of a breadth first search algorithm
 * that finds a path in a airmap for the "Datastructures and
 * algorithms" courses at the Department of Computing Science, Umea
 * University.
 *
 *
 * Authors: Jaffar El-Tai (hed20jei)
 *          Robin Lundin Söderberg (hed20rlg)
 *      
 *
 * Version 2
 *   
 *   
 *   
 */
/*Function declaration*/
bool find_path(graph *g,node *src,node *dest);
void read_file(graph *g, FILE *fp);
void find_path_map(graph *g);
 
int main(int argc, const char *argv[])
{
 
    FILE *fp = fopen(argv[1], "r");
    graph *g; //declares graph variable.
    g = graph_empty(0); //Dont need max_node
 
    if(fp == NULL)
    {
        printf("No map file\n");
        return EXIT_FAILURE;
    }
    
    read_file(g, fp);
    find_path_map(g);

    graph_kill(g);
    return EXIT_SUCCESS;
}
 
/**
 * find_path() - Returns if there is a path or not.
 * @g: Graph storing the node.
 * @src: Source node.
 * @dest: Desitination node
 *
 * Returns: Returns if there is a path or not.
 */
bool find_path(graph *g,node *src,node *dest)
{   
    
    bool state;
    queue *q = queue_empty(NULL);
    
    g = graph_node_set_seen(g, src, true);
    q = queue_enqueue(q, src);
    
    while (!queue_is_empty(q))
    {
        
        node *temp = queue_front(q);
        q = queue_dequeue(q);
        dlist *neighbour = graph_neighbours(g, temp);
        dlist_pos pos = dlist_first(neighbour);

        while (!dlist_is_end(neighbour, pos))
        {
            node *temp2 = dlist_inspect(neighbour, pos);
            if (!graph_node_is_seen(g, temp2))
            {
                g = graph_node_set_seen(g, temp2, true);
                q = queue_enqueue(q, temp2);
            }
            state = nodes_are_equal(temp2, dest);
 
            if (state == true)
            {   
                dlist_kill(neighbour);
                g = graph_reset_seen(g);
                queue_kill(q);
                return true;
            }
 
            pos = dlist_next(neighbour, pos);
        }

        dlist_kill(neighbour);
    }
    
    g = graph_reset_seen(g);
    queue_kill(q);
    return false;
}

/**
 * read_file() - Reads the file and prints if there is any error.
 * @g: Graph storing the node.
 * @fp: file to read.
 *
 * 
 */ 
void read_file(graph *g, FILE *fp)
{
    char lines[255];
    char n1[40];
    char n2[40];
    int count = 0;
    int count1 = 0;

    while (fgets(lines, sizeof(lines), fp) != NULL)
    {   
        for(int i = 0; i<40; i++)
        {
            n1[i] = 0;
            n2[i] = 0;
        }

        if (lines[0] == '#' || lines[0] == '\n')
        {
            //do nothing, skips first line.
        }
        else
        {  
            sscanf(lines, "%40s %40s", n1, n2);

            if (isdigit(n1[0]))
            {
                count1 = 1;
                
                if (count != 0)
                {
                    printf("Map does not follow specification!\n");
                    printf("Forced Exit!\n");
                    
                    exit(EXIT_FAILURE);
                }  
            }
            else if(n2[0] == 0)
            {
                printf("Map does not follow specification!\n");
                printf("Forced Exit!\n");
                    
                exit(EXIT_FAILURE);
            }
            else if(count1 == 1)
            {   
                count++;
 
                if (graph_find_node(g, n1) == NULL) 
                {
                    g = graph_insert_node(g, n1); 
                }
                if (graph_find_node(g, n2) == NULL)
                {
                    g = graph_insert_node(g, n2);
                }
                
                node *nd1 = graph_find_node(g, n1);
                node *nd2 = graph_find_node(g, n2);
 
                g = graph_insert_edge(g, nd1, nd2); 
            }
            else
            {
                printf("Map does not follow specification!\n");
                printf("Forced Exit!\n");
                    
                exit(EXIT_FAILURE

                );
            }         
        }
    }
    
    fclose(fp);
}
/**
 * find_path_map() - Prints if there is a path or not (runs the program UI).
 * @g: Graph storing the node.
 *
 */  
void find_path_map(graph *g)
{
    char request[85];
    char n1[40];
    char n2[40];
    int count = 0;
 
    do
    {
        for(int i = 0; i<40; i++)
        {
            n1[i] = 0;
            n2[i] = 0;
        }

        printf("Enter origin and destination (quit to exit): ");
        count = 0;
        fgets(request, sizeof(request), stdin);
        sscanf(request, "%s %s", n1, n2);
        
        if (strcmp(n1, "quit") == 0)
        {
            fprintf(stdout,"Normal exit.\n\n");
            graph_kill(g);
            exit(EXIT_SUCCESS);
        }
        if (graph_find_node(g, n1) == NULL)
        {
            printf("There is no %s destination.\n\n", n1);
            count = 1;
        }
        if (graph_find_node(g, n2) == NULL)
        {
            printf("There is no %s destination.\n\n", n2);
            count = 1;
        }

        if(count == 0)
        {
            if ((graph_find_node(g, n1) != NULL) && (graph_find_node(g, n2) != NULL))
            {
                node *nd1 = graph_find_node(g, n1);
                node *nd2 = graph_find_node(g, n2);
                bool path = find_path(g, nd1, nd2);
                if (path == true)
                {
                    printf("There is a path from %s to %s.\n\n", n1, n2);
                }
                else
                {
                    printf("There is no path from %s to %s.\n\n", n1, n2);
                } 
            }
        }
    } while (1);
}