#ifndef _ALGORITHM_INCLUDE_
#define _ALGORITHM_INCLUDE_

#include "types.h"
#include "dataParse.h"
#include "nodeOperations.h"

/*
 *  Performs the first 10 steps of the first algorithm
 *  @param treeNode *head , char **name and int countNodes
 *  creates a new node (merging 2 nodes) and its placed in the correct spot in head
 */
extern void firstStageAlgo( treeNode *head, char **name, int countNodes);

/*
 *  Performs the rest of the steps of the first algorithm
 *  @param treeNode *head , char **name and int countNodes
 *  creates a new node (merging 2 nodes based on the level of each node) and it's saved in the correct place in head
 */
extern void secondStageAlgo( treeNode *head, char **name, int countNodes, int *countMergedNodes );

/*
 *  Performs the second algorithm
 *  @param treeNode *head , n number of data channels and int countNodes
 *  @return C the data channels
 */
extern void secondAlgorithm( treeNode *head, int n, int countNodes );

#endif