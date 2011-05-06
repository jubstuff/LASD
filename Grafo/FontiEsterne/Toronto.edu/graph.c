/*
 * graph.c - "Graph" abstract data type.
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "emalloc.h"

struct graph {
    int maxnodes;  /* original maxnodes value passed to new_graph() */
    int nnodes;  /* how many stored so far */
    char **node_name;
    int *colour;
    int *adjacency_matrix;
    int *indegree, *outdegree;
};


/* Create a new empty graph. */
GRAPH new_graph(int maxnodes)
{
    int i;
    struct graph *g = (struct graph *)emalloc(sizeof(struct graph));
    g->maxnodes = maxnodes;
    g->nnodes = 0;
    g->node_name = (char **)emalloc(maxnodes * sizeof(char *));
    g->colour = (int *)emalloc(maxnodes * sizeof(int));
    g->adjacency_matrix = (int *)emalloc(maxnodes * maxnodes * sizeof(int));
    for (i = maxnodes * maxnodes - 1; i >= 0; i--)
        g->adjacency_matrix[i] = 0;
    g->indegree = (int *)emalloc(maxnodes * sizeof(int));
    g->outdegree = (int *)emalloc(maxnodes * sizeof(int));
    for (i = 0; i < maxnodes; i++)
        g->indegree[i] = g->outdegree[i] = 0;
    return g;
}


/* Delete a graph. */
void free_graph(GRAPH g)
{
    free(g->node_name);
    free(g->colour);
    free(g->adjacency_matrix);
    free(g->indegree);
    free(g->outdegree);
    free(g);
}


/* Add a vertex. */
int add_vertex(GRAPH g, char *name)
{
    g->node_name[g->nnodes] = name;
    g->colour[g->nnodes] = -1;
    /* adjacency_matrix already initialized in new_graph */
    return g->nnodes++;
}


/* Add a directed edge. */
void add_edge(GRAPH g, int from, int to)
{
    g->adjacency_matrix[from * g->maxnodes + to] = 1;
    g->indegree[to]++;
    g->outdegree[from]++;
}


int get_graph_nodes(GRAPH g)
{
    return g->nnodes;
}

int is_adjacent(GRAPH g, int from, int to)
{
    return g->adjacency_matrix[from * g->maxnodes + to];
}

char *get_vertex_name(GRAPH g, int i)
{
    return g->node_name[i];
}

int get_vertex_colour(GRAPH g, int i)
{
    return g->colour[i];
}


/*
 * Colour the graph.  See a2 handout for algorithm description.
 * This only works on an undirected graph, i.e. edges are always symmetric.
 */
void colour_graph(GRAPH g)
{
    int i, j, t, maxDegree, colour, numberColoured, *degreeOrder;
    int nextColourlessVertex = 0;

    /* auxiliary array to hold node indices to be sorted into degree order */
    degreeOrder = (int *)emalloc(g->nnodes * sizeof(int));

    for (i = 0; i < g->nnodes; i++) {
        g->colour[i] = -1;
	degreeOrder[i] = i;
    }

    /* sort */
    for (i = 0; i < g->maxnodes - 1; i++) {
        maxDegree = i;
        for (j = i + 1; j < g->maxnodes; j++)
	    /* indegree and outdegree are the same, since it is undirected */
            if (g->indegree[degreeOrder[maxDegree]]
			< g->indegree[degreeOrder[j]])
                maxDegree = j;
	t = degreeOrder[i];
	degreeOrder[i] = degreeOrder[maxDegree];
	degreeOrder[maxDegree] = t;
    }

    /* colour */
    for (colour = numberColoured = 0; numberColoured < g->nnodes; colour++) {

        while (g->colour[degreeOrder[nextColourlessVertex]] != -1)
            nextColourlessVertex++;

        g->colour[degreeOrder[nextColourlessVertex]] = colour;
        numberColoured++;

        for (i = nextColourlessVertex + 1; i < g->nnodes; i++) {
            /* if i is not coloured, then see if it can be coloured */
            if (g->colour[degreeOrder[i]] == -1) {
                int canBeColoured = 1;
                for (j = nextColourlessVertex; canBeColoured && j < i; j++)
                    if (g->colour[degreeOrder[j]] == colour
			    && is_adjacent(g, degreeOrder[j], degreeOrder[i]))
                        canBeColoured = 0;

                if (canBeColoured) {
                    g->colour[degreeOrder[i]] = colour;
                    numberColoured++;
                }
            }
        }
    }
}


/* dump data for testing */
void print_graph(GRAPH g)
{
    int row, col;

    printf("name col |  ");
    for (col = 0; col < g->nnodes; col++)
        printf("%-3.3s", g->node_name[col]);
    printf("\n");
    printf("---------+--");
    for (col = 0; col < g->nnodes; col++)
        printf("---");
    printf("\n");
    for (row = 0; row < g->nnodes; row++) {
        printf("%-4s %3d | ", g->node_name[row], g->colour[row]);
        for (col = 0; col < g->nnodes; col++)
            printf("%-3d", is_adjacent(g, row, col));
        printf("\n");
    }
}
