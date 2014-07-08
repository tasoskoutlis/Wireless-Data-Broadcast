#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nodeOperations.h"

unsigned int level = 0;

void findMinFreqs( treeNode *head, char **name ){
	
	treeNode *curr1 = head, *curr2 = head->treeNxt, *temp = curr2;
	double minFreq = curr1->freq + curr2->freq, tempFreq = 0.0;
	
	name[0] = curr1->name;
	name[1] = curr2->name;
	
	for(curr1 = head, curr2 = head->treeNxt; curr2 != NULL; curr1 = curr1->treeNxt, curr2 = curr2->treeNxt){
		if( !curr2->flagMerged ){			
			tempFreq = curr1->freq + curr2->freq;
			if( tempFreq < minFreq ){
				minFreq = tempFreq;
				name[0] = curr1->name;
				name[1] = curr2->name;				
			}
		}
		else{  //if second node isn't leaf 
			temp = curr2;
			while( temp->flagMerged == 1 && temp->treeNxt != NULL ){				
				tempFreq = curr1->freq + temp->freq;
				if( tempFreq < minFreq ){					
					minFreq = tempFreq;
					name[0] = curr1->name;
					name[1] = temp->name;
				}
				temp = temp->treeNxt;				
			}			
			if( temp != NULL ){								
				tempFreq = curr1->freq + temp->freq;
				if( tempFreq < minFreq ){
					minFreq = tempFreq;
					name[0] = curr1->name;
					name[1] = temp->name;
				}				
			}
		}
	}	
}

void findMaxLevels( treeNode *head, char **name ){
	
	treeNode *curr1 = head, *curr2 = head->treeNxt;
	double maxLevel = curr1->level + curr2->level, tempLevel = 0.0;
	
	name[0] = curr1->name;
	name[1] = curr2->name;

	for(curr1 = head, curr2 = head->treeNxt; curr2 != NULL; curr1 = curr1->treeNxt, curr2 = curr2->treeNxt){
		tempLevel = curr1->level + curr2->level;
		if( tempLevel > maxLevel ){
			maxLevel = tempLevel;
			name[0] = curr1->name;
			name[1] = curr2->name;
		}
	}
}

void initTreeNxt( treeNode *head ){
	
	treeNode *curr1 = head, *curr2 = head->nxt;

	while( curr2 != NULL ){
    	curr1->treeNxt = curr1->nxt;
		curr2->prv = curr1;
		curr1 = curr1->nxt;
		curr2 = curr2->nxt;
	}
	curr1->treeNxt = curr1->nxt;
}

treeNode *searchNodes( treeNode *head, char *name ){
	
	treeNode *curr;
	curr = head;
  
    while( strcmp( curr->name, name ) ){
    	curr = curr->treeNxt;
    }
	return curr;
}

void findLevel( treeNode *head ){
	
	treeNode *curr;
	curr = head;
		
	if( curr != NULL ){		
		level++;
		findLevel( curr->childLeft );
		curr->level = level;
		findLevel( curr->childRight );
		level--;
	}
}

void initializeNode( treeNode *head ){
	
	head->name = NULL;
	head->freq = 0.0;
	head->level = 0;
	head->flagRoot = 0;
	head->flagMerged = 0;
	head->parent = NULL;
	head->childLeft = NULL;
	head->childRight = NULL;
	head->treeNxt = NULL;
	head->prv = NULL;
	head->nxt = NULL;
}

void printTree( treeNode *head ){
	
	treeNode *curr;
	curr = head;
		
	if( curr != NULL ){		
		printTree( curr->childLeft );
		printf("node's name %s and node's level %d \n", curr->name, curr->level);
		printTree( curr->childRight );
	}
}

void freeNodes( treeNode *head ){
	
	treeNode *curr;
	curr = head;
  
	while( curr != NULL )
    {
    	curr = head->nxt;
		free( head->name );
		free( head->childLeft );
		free( head->childRight );
		free( head );
		head = curr;
	}
}

void freeTree( treeNode *head ){
	
	treeNode *curr;
	curr = head->treeNxt;
  
	while( curr->treeNxt != NULL )
    {
    	curr = head->treeNxt;
		free( head->name );
		free( head->childLeft );
		free( head->childRight );
		free( head );
		head = curr;
	}
}
