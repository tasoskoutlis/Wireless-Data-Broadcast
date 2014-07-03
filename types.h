/*
 * types.h
 *
 *      Author: 
 *
 *      Description: Main data type declarations used throughout the code
 */

#ifndef TYPES_H_
#define TYPES_H_

/*****************************************************************
*             		     HUFFMAN 								 *
******************************************************************/

typedef struct _treeNode
{
    char *name;		/* node's name */

	int key;		/* key of every node */
	
    double freq;	/* node's frequency */
    
	int level; 		/* node's level */
		
 	int flag;		/* check if node processed */
	
	int flagMerged;		/* flag that node is merged */
	
	int indexNode;		/* jth index node of level i */
	
	struct _treeNode *parent;		/* parent */
	
	struct _treeNode *childLeft;	/* left children */
	
	struct _treeNode *childRight;	/* right children */
	
	struct _treeNode *treeNxt;		/* pointer to newly created node (merged nodes) tree */
	
	struct _treeNode *prv;
	
	struct _treeNode *nxt;
}
treeNode;

/*****************************************************************
*             		     CONTROL TABLE 							 *
******************************************************************/

typedef struct _controlTableElemnt
{	
	char *keyValue;
	
	struct controlTable *controlIndex; 
}
controlTableElemnt;

typedef struct _controlTable
{	
	struct treeNode *node;
	
	struct controlTableElemnt *element;
	
	int appear;
	
	struct _controlTable *nxt; 
	
	struct _controlTable *prv; 
}
controlTable;

#endif /* TYPES_H_ */
