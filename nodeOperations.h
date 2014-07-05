#ifndef _NODEOPERATIONS_INCLUDE_
#define _NODEOPERATIONS_INCLUDE_

#include "types.h"
#include "dataParse.h"

extern unsigned int level; //global counter holds level of each node

/*
 *  Find Minimum Frequences
 *  @param treeNode *head , char **name
 *  saves in @param name the names of the 2 nodes to be merged
 */
extern void findMinFreqs( treeNode *head, char **name );

/*
 *  Find Maximum Levels
 *  @param treeNode *head 
 *  saves in @param name the names of the 2 nodes to be merged
 */
extern void findMaxLevels( treeNode *head, char **name );

/*
 *  Initialize node
 *  @param treeNode *head 
 */
extern void initializeNode( treeNode *head );

/*
 *  Find node from searching nodes names
 *  @param treeNode *head and name
 *  @return node
 */
extern treeNode *searchNodes( treeNode *head, char *name );

/*
 *  Find level of each node
 *  @param treeNode *head
 *  
 */
extern void findLevel( treeNode *head );

/*
 *  Print Nodes
 *  @param treeNode *head
 */
extern void printTree( treeNode *head );

/*
 *  Initialize tree Nodes
 *  @param treeNode *head 
 */
extern void initTreeNxt( treeNode *head );

/*
 *  Free nodes
 *  @param treeNode *head
 */
extern void freeNodes( treeNode *head );

/*
 *  Free tree Nodes
 *  @param treeNode *head
 */
extern void freeTree( treeNode *head );


#endif