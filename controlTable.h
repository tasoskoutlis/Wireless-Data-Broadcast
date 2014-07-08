#ifndef _CONTROLTABLE_INCLUDE_
#define _CONTROLTABLE_INCLUDE_

#include "types.h"
#include "dataParse.h"
#include "nodeOperations.h"

extern int getOnlyOnce;
extern controlTable *currTable;		//holds node of control table

/*
 *  Performs the second algorithm
 *  @param treeNode *head , n number of data channels and int countNodes
 *  @return C the data channels
 */
extern void createControlTable( treeNode *head, int countNodes, int countMergedNodes );

#endif