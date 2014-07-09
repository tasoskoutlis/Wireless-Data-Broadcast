#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "controlTable.h"

#define DEBUG 1

int getOnlyOnce = 0;
controlTable *currTable;

/*
 *  @param treeNode *root
 *  @return biggest node of sub tree
 */
char *maxKeyOfSubTree( treeNode *root );

/*
 *  searches the tree recursively
 *  @param treeNode *head , controlTable *controlTableHead
 */
void searchTree( treeNode *head, controlTable *controlTableHead );

/*
 *  initializes every node of Control Table
 *  @param treeNode *curr , controlTable *controlTableHead
 */
controlTable *initializeControlTable( treeNode *curr, controlTable *table );

/*
 * Fills Control Tables elements
 *  @param treeNode *head , controlTable *controlTableHead
 */
void searchTreeForElements( treeNode *curr, controlTable *controlTableHead );

/*
 *  Free Control Tables memory 
 *  @param controlTable *controlTableHead
 */
void freeControlTable( controlTable *controlTableHead );


void createControlTable( treeNode *head, int countNodes, int countMergedNodes ){
	
	head->flagRoot = -1;
	
	treeNode *curr = head;
	controlTable *controlTableHead, *temp;
	int i = 0;
	
	printf("Creating Control Table\n");
	
	//Initialize Head of Control Table
	controlTableHead = ( controlTable* )malloc( sizeof( controlTable ) );
    if( controlTableHead == NULL )
	{
	    printf("couldn't allocate memory \n");
	    exit(EXIT_FAILURE);
	}

	controlTableHead->element = ( controlTableElemnt* )malloc( sizeof( controlTableElemnt ) );
    if( controlTableHead->element == NULL )
	{
	    printf("couldn't allocate memory \n");
	    exit(EXIT_FAILURE);
	}
	controlTableHead->element->keyValue = strdup("no");
	controlTableHead->element->controlIndex = NULL;
	controlTableHead->appear = 1;
	controlTableHead->prv = NULL;
	controlTableHead->nxt = NULL;
	
	//Initialize the Control Table by searching the tree
	searchTree( head, controlTableHead );
	
	//Fill the Control Table by searching the tree
	searchTreeForElements( curr, controlTableHead );
	
#if DEBUG
	for( temp = controlTableHead; temp != NULL; temp = temp->nxt ){
		for( i = 0; i < temp->node->level; i++){
			printf("node %s with appearance %d , position %d and key %s \n", temp->node->name, temp->appear, i, temp->element[i].keyValue);
		}
		printf("\n");
	}
#endif
	
	//Free Control Table Memory
	freeControlTable( controlTableHead );
	
	printf("Finished Control Table\n");
}

void searchTree( treeNode *head, controlTable *controlTableHead ){
	
	treeNode *curr;
	currTable = controlTableHead;
	
	curr = head;
	
	if( curr != NULL ){
		if( curr->flagMerged ){	
			currTable = initializeControlTable( curr, currTable );			
			searchTree( curr->childLeft, currTable );
			currTable = initializeControlTable( curr, currTable );
			searchTree( curr->childRight, currTable );
		}
	}
}

controlTable *initializeControlTable( treeNode *curr, controlTable *table ){

	controlTable *temp;
	int i = 0;
	
	if( !getOnlyOnce ){		//get in the first time ( head )
		table->node = curr;
		getOnlyOnce = 1;
		
		return table;
	}
	else{
		currTable = ( controlTable* )malloc( sizeof( controlTable ) );
		if( currTable == NULL )
		{
			printf("couldn't allocate memory \n");
			exit(EXIT_FAILURE);
		}
		
		currTable->node = curr;
		currTable->element = ( controlTableElemnt* )malloc( currTable->node->level * sizeof( controlTableElemnt ) );
    	if( currTable->element == NULL )
		{
			printf("couldn't allocate memory \n");
	    	exit(EXIT_FAILURE);
		}
		for(i = 0; i < currTable->node->level; i++){
			currTable->element[i].keyValue = strdup("no");
			currTable->element[i].controlIndex = NULL;
		}	
		currTable->appear = 1;
		
		for( temp = table; temp != NULL; temp = temp->prv ){
			if( !strcmp(currTable->node->name, temp->node->name) ){ //if node appeared again
				currTable->appear++;
				break;
			}
		}
		currTable->prv = table;
		currTable->nxt = NULL;
		table->nxt = currTable;
		
		return currTable;
	}
}

void searchTreeForElements( treeNode *curr, controlTable *controlTableHead ){
	
	controlTable *searchTable, *temp;
	int j = 0;
	char *name;
	
	for( currTable = controlTableHead; currTable != NULL; currTable = currTable->nxt ){
		temp = currTable->prv;
											
		if( !currTable->node->flagRoot ){  //if not head
				
			if( currTable->appear == 1 ){					
				for( j = 0; j < currTable->node->level-1; j++){
					currTable->element[j].keyValue = strdup(temp->element[j].keyValue);
					currTable->element[j].controlIndex = temp->element[j].controlIndex;
				}
				if( temp->appear == 1){						
					for( searchTable = currTable; searchTable != NULL; searchTable = searchTable->nxt ){
						if( !strcmp(searchTable->node->name, temp->node->name) && searchTable->appear == 2 ){
							break;
						}
					}
					currTable->element[j].controlIndex = searchTable;
				}
				else{
					if( temp->node->flagRoot == -1 && temp->appear == 2){
						currTable->element[j].controlIndex = NULL;
					}
					else{
						for( searchTable = currTable; searchTable != NULL; searchTable = searchTable->nxt ){
							if( !strcmp(searchTable->node->name, temp->node->parent->name) && searchTable->appear == 2 ){
								break;
							}
						}
						currTable->element[j].controlIndex = searchTable;
					}
				}
				name = maxKeyOfSubTree( currTable->node );
				currTable->element[j].keyValue = strdup(name);	
			}
			else if( currTable->appear == 2 ){
				if( !strcmp(currTable->node->name, temp->node->name) ){
					
					for( j = currTable->node->level-1; j > 0; j--){
						currTable->element[j].keyValue = strdup(temp->element[j].keyValue);
						currTable->element[j].controlIndex = temp->element[j].controlIndex;
					}
					name = maxKeyOfSubTree( currTable->node->childLeft );
					currTable->element[0].keyValue = strdup(name);
					currTable->element[0].controlIndex = controlTableHead;
				}
				else{						
					name = maxKeyOfSubTree( currTable->node->childLeft );
					currTable->element[0].keyValue = strdup( name );
					currTable->element[0].controlIndex = controlTableHead;
					for( j = 1; j < currTable->node->level; j++){
						currTable->element[j].keyValue = strdup(temp->element[j].keyValue);
						currTable->element[j].controlIndex = temp->element[j].controlIndex;
					}
				}
			}
		}
		else{
			if( currTable->appear == 2 ){
				name = maxKeyOfSubTree( currTable->node->childLeft );
				currTable->element[0].keyValue = strdup(name);
				currTable->element[0].controlIndex = controlTableHead;
			}
			else{			
				currTable->element[0].keyValue = strdup("no");
			}		
		}
	}
}

char *maxKeyOfSubTree( treeNode *root ){
	
	treeNode *curr;
	char *name;
	
	if( root->flagRoot == -1 ){		//case of head of control table
		name = strdup( "no" );
		return name;
	}
	else if( root->childLeft == NULL ){		//case of leaf
		name = strdup( root->name );
		return name;
	}

	for( curr = root->childRight; curr != NULL; curr = curr->childRight ){
		name = strdup(curr->name);
	}
	return name;
}

void freeControlTable( controlTable *controlTableHead ){
	
	controlTable *curr;
	int i = 0;
	curr = controlTableHead;
  
	while( curr != NULL )
    {
    	curr = controlTableHead->nxt;
		for( i = 0; i < controlTableHead->node->level; i++){
			free( controlTableHead->element[i].keyValue );
		}
		free( controlTableHead->element );
		free( controlTableHead );
		controlTableHead = curr;
	}
}