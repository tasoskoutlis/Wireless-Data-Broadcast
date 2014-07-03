#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "controlTable.h"

#define DEBUG 1

void initializeControlTable( treeNode *curr, controlTable *controlTableHead, controlTable *table );

void createControlTable( treeNode *head, int countNodes, int countMergedNodes ){
	
	treeNode *curr = head;
	char *name;
	controlTable *controlTableHead;
	int i = 0;
	
	//Initialize Head of Control Table
	controlTableHead = ( controlTable* )malloc( sizeof( controlTable ) );
    if( controlTableHead == NULL )
	{
	    printf("couldn't allocate memory \n");
	    exit(EXIT_FAILURE);
	}
	
	controlTableHead->node = head;
	controlTableHead->element = ( controlTableElemnt* )malloc( sizeof( controlTableElemnt ) );
    if( controlTableHead->element == NULL )
	{
	    printf("couldn't allocate memory \n");
	    exit(EXIT_FAILURE);
	}
	controlTableHead->element->keyValue = NULL;
	controlTableHead->element->controlIndex = NULL;
	controlTableHead->appear = 1;
	controlTableHead->prv = NULL;
	controlTableHead->nxt = NULL;
	
	//Fill the Control Table by searching the tree
	searchTree( head, controlTableHead );
		
	name = maxKeyOfSubTree( head );
	
	printf("NAME gia to curr->name %s \n", name);
	
	for(i = 0; i < 30; i++){
		printf("char name : %s, appear1 = %d \n", table[i].key, table[i].appear);
	}

	free(name);
}

void searchTree( treeNode *head, controlTable *controlTableHead ){
	
	treeNode *curr;
	controlTable *currTable;
	
	curr = head;
	
	if( curr != NULL ){		
		
		currTable = ( controlTable* )malloc( sizeof( controlTable ) );
	    if( currTable == NULL )
		{
		    printf("couldn't allocate memory \n");
		    exit(EXIT_FAILURE);
		}
		
		initializeControlTable( curr, controlTableHead, currTable );
			
		searchTree( curr->childLeft );
		searchTree( curr->childRight );
	}
}

void initializeControlTable( treeNode *curr, controlTable *controlTableHead, controlTable *table ){

	controlTable *currTable = table;

	currTable->element = ( controlTableElemnt* )malloc( sizeof( controlTableElemnt ) );
    if( currTable->element == NULL )
	{
	    printf("couldn't allocate memory \n");
	    exit(EXIT_FAILURE);
	}
	
	currTable->node = curr;
	currTable->element->keyValue = strdup(curr->name);
	currTable->element->controlIndex =// kati me to currTable; //pou tha deiksei
	currTable->appear = 1; //edw me to appear
	currTable->nxt = NULL;	
	currTable->prv = controlTableHead;
}

char *maxKeyOfSubTree( treeNode *root ){
	
	treeNode *curr;
	char *name;

	for( curr = root->childRight; curr != NULL; curr = curr->childRight ){
		name = strdup(curr->name);
	}
	return name;
}
