/*
 * "Graph" abstract data type.
 */

typedef struct graph *GRAPH;

/* Create a new empty graph. */
extern GRAPH new_graph(int maxnodes);

/* Delete a graph. */
extern void free_graph(GRAPH g);


/*
 * Add a vertex.  Must not exceed original maxnodes as passed to new_graph().
 * Returned value is index number for future reference to that node.
 */
extern int add_vertex(GRAPH g, char *name);

/*
 * Add a directed edge.  If you want to use this as an undirected graph,
 * always call this function twice, with 'from' and 'to' reversed.
 */
extern void add_edge(GRAPH g, int from, int to);

/* Get graph data. */
extern int get_graph_nodes(GRAPH g);  /* how many currently in the graph */
extern int is_adjacent(GRAPH g, int from, int to);
extern char *get_vertex_name(GRAPH g, int i);
extern int get_vertex_colour(GRAPH g, int i);  /* if coloured */


/* Colour the graph. */
extern void colour_graph(GRAPH g);


/* Print the graph data for testing purposes. */
extern void print_graph(GRAPH g);
