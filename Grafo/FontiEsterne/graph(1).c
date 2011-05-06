/* Written by Alan Finlay, Computer Science Dept., Monash University, 1995. */

/*
 This software, both source and executables, is copyright Monash
 University Computer Science Department, 1994.  All rights reserved.
 Permission is granted for use of the software for non-commercial purposes
 only provided all copyright notices are preserved intact.  This permission
 is granted on an AS IS basis.  Monash University makes no claims about the
 suitability of this software for any purpose and accepts no responsibility
 for the consequences of its use.
*/

static char sccs_ident[] = "@(#)graph.c	1.17";

#include <stdio.h>
#include <sys/types.h>
#include <malloc.h>
#include <limits.h>
#include <string.h>
#include "image.h"
#include "mmltools.h"
#include "strings.h"
#include "align.h"
#include "graph.h"
#include "edge.h"

	/* for assigning node numbers (unique for each run) */
static int next_node = 1;

static int int_pow2(n)
{
    int i = 1;

    while (n>1) {
	i <<= 1;
	n >>= 1;
	}
    return i;
}

void StochasticAlign2(tree *node, edge e)
	/* Construct a 2-way alignment for the selected edge of a node. */
{
    direction dir;
    edge_data *edata;
    tree *other_node, *from_node, *to_node;
    float mml;

#ifdef DEBUG2
    printf("chose edge %x\n",e);
#endif
	/* find the edge data and (from_node, to_node) it corresponds to */
    switch (e) {
	case Left:
		other_node = node->left;
		dir = node->ed.left_dir;
		edata = node->ed.left_edge;
		break;
	case Right:
		other_node = node->right;
		dir = node->ed.right_dir;
		edata = node->ed.right_edge;
		break;
	case Parent:
		other_node = node->parent;
		dir = node->ed.parent_dir;
		edata = node->ed.parent_edge;
		break;
	}
    if (dir==From) {
	from_node = node;
	to_node = other_node;
	}
    else {
	from_node = other_node;
	to_node = node;
	}

	/* update osm and weight using the weighted sums of previous values */
    edata->weight.PM = edata->weight.PM*WFACTOR + edata->osm.PM;
    edata->weight.PC = edata->weight.PC*WFACTOR + edata->osm.PC;
    edata->weight.PI = edata->weight.PI*WFACTOR + edata->osm.PI;
    edata->weight.PD = edata->weight.PD*WFACTOR + edata->osm.PD;
    OS_Normalize(&edata->weight);

	/* choose a "random" alignment from the posterior prob dist */
    mml = ChooseAlign(&from_node->string,&to_node->string,
				&edata->weight,&edata->alignment);
    edata->mml = mml;
    if (mml < edata->min_mml) edata->min_mml = mml;
}


static void PrintContent(tree *t)
{
    if (t==NULL) return;
    if (t->left == NULL && t->right == NULL) { /* a leaf node */
	StringPrint(&t->string);
#ifdef DEBUG
	if (t->count != 0)
	    printf("Average length for %d variants is %.2f\n",
					t->count, t->avelength/t->count);
#endif
    } else {
	PrintContent(t->left);
	StringPrint(&t->string);
	if (t->count != 0)
	    printf("Average length for %d inferences is %.2f\n",
					t->count, t->avelength/t->count);
	PrintContent(t->right);
    }
}

#define EMPTY_ID "EMPTY_NODE"

static void TreeShapeWrite(FILE *fp, tree *t)
{
    if (t==NULL) fprintf(fp,EMPTY_ID);
    else if (t->left == NULL && t->right == NULL) /* a leaf node */
	fprintf(fp,"%s",t->string.identifier);
    else {
	fputs("( ",fp);
	TreeShapeWrite(fp,t->left);
	fprintf(fp," <- %s -> ",t->string.identifier);
	TreeShapeWrite(fp,t->right);
	fputs(" )",fp);
    }
}

void UTreeShapeWrite(FILE *fp, tree *root)
{
	/* root->left and root->right should be valid, but check anyway */
    if (root->left!=NULL) TreeShapeWrite(fp,root->left);
    fprintf(fp, " <-> ");
    if (root->right!=NULL) TreeShapeWrite(fp,root->right);
    fprintf(fp, "\n");
}

static tree *TreeShapeRead(FILE *fp, tree **t, tree *parent)
	/* Read a subtree structure into an array starting from *t and */
	/* advancing the node pointer *t to the next free slot. */
	/* The parent node is required, the subtree is returned. */
{
    tree *this;

    if (match(fp,"(")) {
	this = (*t)++;
	this->left = TreeShapeRead(fp,t,this);
	if (!match(fp,"<-")) i_error(I_FATAL,"\'<-\' expected");
	if (fscanf(fp,"%s",this->string.identifier) != 1)
	    i_error(I_FATAL, "\'identifier\' expected");
	if (strcmp(this->string.identifier,EMPTY_ID)==0)
	    i_error(I_FATAL,"empty internal nodes are not allowed");
	if (!match(fp,"->")) i_error(I_FATAL,"\'->\' expected");
	this->right = TreeShapeRead(fp,t,this);
	if (!match(fp,")")) i_error(I_FATAL,"\')\' expected");
	}
    else {
	if (fscanf(fp,"%s",(*t)->string.identifier) != 1)
	    i_error(I_FATAL, "\'identifier\' expected");
	if (strcmp((*t)->string.identifier,EMPTY_ID)==0) return NULL;
	this = (*t)++;
	this->left = NULL;
	this->right = NULL;
	}
    this->parent = parent;
    return this;
}

tree *UTreeShapeRead(FILE *fp, int n)
	/* Read an unrooted tree structure with n nodes (not counting */
	/* the access node). */
{
    tree *nodes,*t;
    int i;

    i_malloc(nodes,tree,n+1);
    for (i=0; i<=n; i++) {
	StringInitialize(&(nodes[i].string),ATABLE);
	nodes[i].number = i; /* default numbers which may be altered later */
	}

	/* Build tree structure for traversing graph */
    t = nodes+1;		/* first node is dummy */
    nodes[0].left = TreeShapeRead(fp,&t,NULL);
    if (!match(fp,"<->")) i_error(I_FATAL,"\'<->\' expected");
    nodes[0].right = TreeShapeRead(fp,&t,nodes[0].left);
    if (nodes[0].left==NULL || nodes[0].right==NULL) i_error(I_FATAL,
	"rebalance the input tree so there are valid nodes each side of <->");
    (nodes[0].left)->parent = nodes[0].right;
    if (t != nodes+n+1) i_error(I_FATAL,
		"incorrect number of nodes in tree structure specification");
    return nodes;
}

void UTreePrint(tree *t) /* print tree as unrooted tree */
{
    if (t!=NULL) {
	UTreeShapeWrite(stdout,t);
	if (t->left!=NULL) PrintContent(t->left);
	if (t->right!=NULL) PrintContent(t->right);
	}
}

tree *TreeBuild(FILE *fp, tree *parent, int n)
	/* Build a binary tree using n GenBank strings from indicated file */
{
    int split;
    Boolean first = True;
    tree *newnode;

    switch (n) {
	case 0: i_error(I_FATAL,"invalid number of nodes: 0");
	case 1:
	    i_malloc(newnode,tree,1);
	    StringInitialize(&newnode->string,ATABLE);
	    StringReadGenbank(fp,&newnode->string);
	    newnode->number = next_node++;
	    newnode->left = NULL;
	    newnode->right = NULL;
	    newnode->parent = parent;
	    break;
	case 2:
	    if (first)
		i_error(I_INFORM,"tree has at least one irregular node");
	    first = False;
	    newnode = TreeBuild(fp,parent,1);
	    newnode->left = TreeBuild(fp,newnode,1);
	    newnode->right = NULL;
	    break;
	default:
	    newnode = TreeBuild(fp,parent,1);
	    split = int_pow2(n)-1;
	    newnode->left = TreeBuild(fp,newnode,split);
	    newnode->right = TreeBuild(fp,newnode,n-split-1);
	    break;
	}
    return newnode;
}

tree *UTreeBuild(FILE *fp, int n)
	/* build an unrooted tertiary graph by reading n Genbank strings */
	/* from file fp.  The graph can be treated as a binary tree with a */
	/* dummy root node, which this function returns. */
{
    int split;
    tree *root;

    if (n<2) i_error(I_FATAL,"at least 2 nodes are required");
    root = malloc(sizeof(tree));
    split = int_pow2(n)-1;
    root->left = TreeBuild(fp,root,split);
    root->right = TreeBuild(fp,root,n-split);
    root->parent = NULL;
	/* remove the root from the graph considered as an unrooted tree. */
	/* i.e. no node has a parent pointer to the dummy root node. */
    (root->left)->parent = root->right;
    (root->right)->parent = root->left;
    return root;
}

int CountNodes(tree *t)
        /* count number of nodes from tree root t */
	/* Will count dummy node if applied to unrooted tree. */
{
    if (t==NULL) return 0;
    else return (1 + CountNodes(t->left) + CountNodes(t->right));
}

static int CountEdges(tree *t)
        /* count number of nodes from sub tree t */
	/* Do not apply to unrooted tree, dummy node will cause problems. */
{
    int count = 0;

    if (t==NULL) return 0;
    if (t->ed.parent_dir == From) count++;
    if (t->ed.left_dir == From) count++;
    if (t->ed.right_dir == From) count++;
    return (count + CountEdges(t->left) + CountEdges(t->right));
}

static int CountInternal(tree *t)
        /* count number of internal nodes from tree root t */
	/* Will count dummy node if applied to unrooted tree. */
{
    if (t->left==NULL || t->right==NULL) return 0;
    else return (1 + CountInternal(t->left) + CountInternal(t->right));
}

static CI(tree *t, tree **internal, int *nodes_counter)
	/* subsidiary function of CollectInternal */
{
    if (t->left!=NULL && t->right!=NULL) {
	internal[(*nodes_counter)++] = t;
	CI(t->left, internal, nodes_counter);
	CI(t->right, internal, nodes_counter);
	}
}

tree **CollectInternal(tree *root, int *n)
	/* build array of internal nodes, returns the number of them via n */
{
    tree **internal;

    i_malloc(internal, tree *, CountInternal(root)-1);
	/* N.B. CountInternal counts the dummy root node so alloc one less */
    *n = 0;
    CI(root->left, internal, n);
    CI(root->right, internal, n);
    return internal;
}

void *UpdateNode(tree *t, align *n)
	/* update the node according to the new 4-way alignment produced */
	/* after resampling one of the edges 2-way alignment's. */
{
    int p,q;		/* string and alignment indices */
    symbol s;
    table lookup;

	/* Create a lookup table of the probabilities of ancestor symbols */
	/* for 3-tuples of descendant symbols for the indicated node. */
    lookup = CalcTupleProbs(t);

	/* Apply the lookup table to replace the first component of the */
	/* 4-way alignment using the other components as a sequence of */
	/* descendant 3-tuples. */
    CreateNewP(lookup,n);

	/* update the node string */
    q = 0;
    for (p=0; p<n->length; p++) {
	s = n->sequence[0][p];
	if (s!=0) t->string.sequence[q++] = s;
	}
    t->string.length = q;
    t->avelength += q;
    t->count++; 
#ifdef DEBUG2
    StringPrint(&t->string);
#endif
	/* update the edge_data for this node from the 4 way alignment */
    UpdateEdge(t->ed.left_edge,t->ed.left_dir,n,1);
    UpdateEdge(t->ed.right_edge,t->ed.right_dir,n,2);
    UpdateEdge(t->ed.parent_edge,t->ed.parent_dir,n,3);
}

#define NODE_FORMAT "Node number %d:\n"
#define AVE_LEN_FORMAT "Average length is %f/%d\n" 

static void ListNodes(FILE *fp, tree *t)
{
    if (t!=NULL) {
	ListNodes(fp,t->left);
	fprintf(fp,NODE_FORMAT,t->number);
	fprintf(fp,AVE_LEN_FORMAT,t->avelength,t->count);
	StringWrite(fp,&t->string);
		/* this next is needed to stop GenbankReadSequence */
	putc('\n',fp); putc(GENBANKDELIMITER,fp); putc('\n',fp);
	ListNodes(fp,t->right);
	}
}

void UListNodes(FILE *fp, tree *root)
{
    ListNodes(fp,root->left);
    ListNodes(fp,root->right);
}

static void ScanNodes(FILE *fp, tree *t)
{
    int c;
    char id[IDLength];

    if (t->left != NULL) ScanNodes(fp,t->left);
    if (strcmp(t->string.identifier,UNKNOWN_ID)==0) t->number = next_node++;
    else  {
	c = skipblanks(fp);
	if (c!=EOF) ungetc(c,fp);
	if (fscanf(fp,NODE_FORMAT,&t->number) != 1)
	    i_error(I_FATAL, "invalid node header (starts with %c)",c);
	if (fscanf(fp,AVE_LEN_FORMAT,&t->avelength,&t->count) != 2)
	    i_error(I_FATAL, "invalid ave length field (starts with %c)",c);
	if (t->number>=next_node) next_node = t->number + 1;
	strcpy(id,t->string.identifier);
	StringReadGenbank(fp,&t->string);
	if (strcmp(id,t->string.identifier)!=0)
	    i_error(I_FATAL,"%s was expected at node number %d",id,t->number);
	c = skipblanks(fp);
	if (c!=GENBANKDELIMITER) i_error(I_FATAL,"node format error");
	}
    if (t->right != NULL) ScanNodes(fp,t->right);
}

static void WriteNodes(FILE *fp, tree *t)
{
    if (t->left != NULL) WriteNodes(fp,t->left);
    StringWrite(fp,&t->string);
    if (t->right != NULL) WriteNodes(fp,t->right);
}

void UWriteNodes(FILE *fp, tree *root)
{
    WriteNodes(fp,root->left);
    WriteNodes(fp,root->right);
}

static void ReadNodes(FILE *fp, tree *t)
{
    char id[IDLength];

    if (t->left != NULL) ReadNodes(fp,t->left);
    t->number = next_node++;
    if (strcmp(t->string.identifier,UNKNOWN_ID)!=0) {
	strcpy(id,t->string.identifier);
	StringReadGenbank(fp,&t->string);
	if (strcmp(id,t->string.identifier)!=0)
	    i_error(I_FATAL,"%s was expected at node number %d",id,t->number);
	}
    if (t->right != NULL) ReadNodes(fp,t->right);
}

void UTreeWrite(FILE *fp, tree *t)
{
	/* First write a list of nodes */
    fprintf(fp,TREE_FORMAT, CountNodes(t)-1,
		CountEdges(t->left)+CountEdges(t->right));
	/* N.B. dummy root node is counted by CountNodes and */
	/* CountEdges must not be applied to unrooted tree (dummy node). */

	/* Write a description of the tree structure */
    UTreeShapeWrite(fp,t);
    fprintf(fp,"\n");

	/* Write a list of node strings */
    UListNodes(fp,t);

	/* Now write a list of edges */
    ListEdges(fp,t->left);
    ListEdges(fp,t->right);
}

tree *UTreeRead(FILE *fp)
{
    int n_nodes, n_edges, i;
    tree *nodes;
    edge_data *edge_tbl;

    if (fscanf(fp,TREE_FORMAT, &n_nodes, &n_edges) != 2)
	i_error(I_FATAL,"invalid tree (graph) header");
    if (n_nodes<2) i_error(I_FATAL,"not enough nodes specified: %d",n_nodes);

	/* allocate the edges structs */
    i_malloc(edge_tbl,edge_data,n_edges);
    for (i=0; i<n_edges; i++)
	AlignInitialize(&(edge_tbl[i].alignment),2,ATABLE);

	/* allocate and read the tree nodes (strucure only) */
    nodes = UTreeShapeRead(fp, n_nodes);

	/* read list of nodes */
    ScanNodes(fp,nodes->left);
    ScanNodes(fp,nodes->right);

    ScanEdges(fp, nodes, n_nodes, edge_tbl, n_edges);
    return nodes;
}

static void InterpNodes(tree *t)
	/* interpolate strings for any nodes with "unknown" strings */
{
    static first = True;
    static align ali2;
    OneStateMachine osm;

    if (first) {
	AlignInitialize(&ali2,2,ATABLE);
	first = False;
	}
    if (t->left != NULL) InterpNodes(t->left);
    if (t->right != NULL) InterpNodes(t->right);
    if (strcmp(t->string.identifier,UNKNOWN_ID)==0) {
	if (t->left==NULL || t->right==NULL)
	    i_error(I_FATAL,"can only interpolate proper internal nodes");
	OptMachine(&(t->left)->string,&(t->right)->string,&osm);
	(void) OptAlign(&(t->left)->string,&(t->right)->string,&osm,&ali2);
	CreateOptInt(&ali2,&t->string);
	sprintf(t->string.identifier,"%s%d",INTERP_ID,t->number);
	}
    t->avelength = 0.0;
    t->count = 0;
}

tree *UIntTreeRead(FILE *fp)
{
    int n_nodes;
    tree *nodes;

    if (fscanf(fp,INT_TREE_FORMAT, &n_nodes) != 1)
	i_error(I_FATAL,"invalid tree (graph) header");
    if (n_nodes<2) i_error(I_FATAL,"not enough nodes specified: %d",n_nodes);

	/* allocate and read the tree nodes (strucure only) */
    nodes = UTreeShapeRead(fp, n_nodes);

	/* read list of nodes */
    ReadNodes(fp,nodes->left);
    ReadNodes(fp,nodes->right);

    InterpNodes(nodes);
    UCreateEdges(nodes);
    return nodes;
}
