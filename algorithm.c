
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "algorithm.h"

#define DEBUG 1

void firstStageAlgo( treeNode *head, char **name, int countNodes){
	
	treeNode *node, *mergedNode, *leftNode, *rightNode;
	char *merged;
	int i = 1;
	
	while ( i < countNodes ){
	
#if DEBUG
		//print list
		for(node = head->treeNxt; node != NULL; node = node->treeNxt){
			printf("name %s and freq %lf \n", node->name, node->freq);
		}
		printf("\n");	
#endif							
		mergedNode = ( treeNode* )malloc( sizeof( treeNode ));
		if ( mergedNode == NULL ){
			printf("Couldn't allocate memory \n");
			exit( EXIT_FAILURE );
		}
		initializeNode( mergedNode );
		
		findMinFreqs( head->treeNxt, name );	//find the 2 minimum nodes to be merged
		
		leftNode = searchNodes( head->treeNxt, name[0]);
		rightNode = searchNodes( head->treeNxt, name[1]);
		
		/*	begin merging	*/
		
		merged = strndup(name[0], ( strlen(name[0]) + strlen(name[1]) ));
		strcat(merged, name[1]);
				
		mergedNode->name = merged;		
		mergedNode->freq = leftNode->freq + rightNode->freq;
		mergedNode->childLeft = leftNode;
		mergedNode->childRight = rightNode;		
		leftNode->parent = mergedNode;
		rightNode->parent = mergedNode;

		if ( !rightNode->flagMerged ){
			if( rightNode->treeNxt == NULL ){
				mergedNode->nxt = NULL;
				mergedNode->treeNxt = NULL;
			}
			else{
				mergedNode->nxt = rightNode->treeNxt;
				mergedNode->treeNxt = rightNode->treeNxt;
				rightNode->treeNxt->prv = mergedNode;
			}
			leftNode->prv->treeNxt = mergedNode;
			mergedNode->prv = leftNode->prv;
		}
		else{
			if( rightNode->treeNxt == NULL ){
				if( !strcmp(leftNode->treeNxt->name,rightNode->name) ){
					mergedNode->nxt = NULL;
					mergedNode->treeNxt = NULL;
					rightNode->prv->nxt = rightNode->nxt;
					rightNode->prv->treeNxt = rightNode->treeNxt;
				}
				else{					
					mergedNode->nxt = leftNode->treeNxt;
					mergedNode->treeNxt = leftNode->treeNxt;
					rightNode->prv->nxt = rightNode->nxt;
					rightNode->prv->treeNxt = rightNode->treeNxt;
					rightNode->prv->prv = mergedNode; 
					leftNode->treeNxt->prv = mergedNode;
					leftNode->nxt->prv = mergedNode;
				}	
			}
			else{
				mergedNode->nxt = leftNode->treeNxt;
				mergedNode->treeNxt = leftNode->treeNxt;
				rightNode->prv->nxt = rightNode->nxt;
				rightNode->prv->treeNxt = rightNode->treeNxt;
			}
			mergedNode->prv = leftNode->prv;
			leftNode->prv->treeNxt = mergedNode;
		}
		mergedNode->flagMerged = 1;
		printf("merged node name %s and freq %lf \n", mergedNode->name, mergedNode->freq);
		printf("\n");
		i++;
	}
}

void secondStageAlgo( treeNode *head, char **name, int countNodes, int *countMergedNodes ){
	
	treeNode *node, *mergedNode, *leftNode, *rightNode;
	char *merged;
	int i = 1;
	
	while ( i < countNodes ){
	
#if 0
	//print list
	for(node = head; node != NULL; node = node->treeNxt){
		printf("name %s and freq %d \n", node->name, node->level);
	}
	printf("\n");	
#endif							
		mergedNode = ( treeNode* )malloc( sizeof( treeNode ));
		if ( mergedNode == NULL ){
			printf("Couldn't allocate memory \n");
			exit( EXIT_FAILURE );
		}
		initializeNode( mergedNode );
		
		findMaxLevels( head, name);
		
		leftNode = searchNodes( head, name[0]);
		rightNode = searchNodes( head, name[1]);
		
		/*	begin merging	*/
		
		merged = strndup(name[0], ( strlen(name[0]) + strlen(name[1]) ));
		strcat(merged, name[1]);
				
		mergedNode->name = merged;		
		mergedNode->level = leftNode->level - 1;
		mergedNode->childLeft = leftNode;
		mergedNode->childRight = rightNode;		
		leftNode->parent = mergedNode;
		rightNode->parent = mergedNode;

		if( rightNode->treeNxt == NULL ){
			mergedNode->nxt = NULL;
			mergedNode->treeNxt = NULL;
		}
		else{
			mergedNode->nxt = rightNode->treeNxt;
			mergedNode->treeNxt = rightNode->treeNxt;
			rightNode->treeNxt->prv = mergedNode;
		}
		leftNode->prv->treeNxt = mergedNode;
		mergedNode->prv = leftNode->prv;
		
		mergedNode->flagMerged = 1;
		(*countMergedNodes)++;
		i++;
	}
	printf("\n");
}

void createControlTable( treeNode *head, int countNodes, int countMergedNodes ){
	
	treeNode *curr = head;
	char *name;
	controlTable *table;
	int i = 0;
	
	tableHead = ( controlTable* )malloc( sizeof( controlTable ) );
    if( tableHead == NULL )
	{
	    printf("couldn't allocate memory \n");
	    exit(EXIT_FAILURE);
	}
	
	tableHead->node = head;
	tableHead->element = ( controlTableElemnt* )malloc( sizeof( controlTableElemnt ) );
	
	tableHead->element->keyValue = NULL;
	tableHead->element->controlIndex = NULL;
	tableHead->appear = 1;
	tableHead->prv = NULL;
	tableHead->nxt = NULL;
	
	searchTree( head, tableHead );
		
	name = maxKeyOfSubTree( head );
	
	printf("NAME gia to curr->name %s \n", name);
	

	for(i = 0; i < 30; i++){
		printf("char name : %s, appear1 = %d \n", table[i].key, table[i].appear);
		
	}


	free(name);
}

void secondAlgorithm( treeNode *head, int n, int countNodes ){
	
	treeNode *curr;
	int i = 0, j = 1, k = 0;
	double data[countNodes], sum = 0.0, temp = 0.0, ave = 0.0, p = 0.0, thre = 0.0;
	double **C;
	
	C = (double **)calloc( n, sizeof(double *) );    
	    if( C == NULL )
		{
		    printf("couldn't allocate memory \n");
		    exit(EXIT_FAILURE);
		}
    
	    for (i = 0; i < n; i++) {
	        C[i] = (double *)calloc( n, sizeof(double) );
	        if( C[i] == NULL )
	        {
	            printf("couldn't allocate memory \n");
	            exit(EXIT_FAILURE);
	        }
	    }
	
	for( curr = head, i = 0 ; curr->nxt != NULL; curr = curr->nxt, i++ ){
		data[i] = curr->freq;
	}
	
	for(i = 0; i < countNodes; i++){
		for(k = 1; k < countNodes; k++){
			if( data[k] < data[i] ){
				temp = data[k];
				data[k] = data[i];
				data[i] = temp;
			}
		}
	}
	
	for(i = 0; i < countNodes; i++){
		sum += data[i];
	}
	
	p = sum;
	thre = sum/n;
	
	for(i = 0; i < countNodes; i++){
		if (ave <= thre ){
			ave += data[i];
			
		}
		else{
			p -= ave;
			ave = 0;
			thre = p/(n - j);
			j++;
			i--;
		}
	}
}
