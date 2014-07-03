#ifndef _DATAPARSE_INCLUDE_
#define _DATAPARSE_INCLUDE_

#include "types.h"
#include "nodeOperations.h"

/*
 *  Reads data from input file
 *  @param file and treeNode *head 
 *  @return number of nodes
 */
extern int readInputFile( FILE *f, treeNode *head );

#endif