#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "algorithm.h"

#define DEBUG 1
#define SORT 0

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
		
		leftNode = searchNodes( head->treeNxt, name[0]);		//find and return the 2 nodes
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
	
	treeNode *mergedNode, *leftNode, *rightNode;
	char *merged;
	int i = 1;
	
	while ( i < countNodes ){
	
#if 0
	treeNode *node;
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
		
		findMaxLevels( head, name);			//find the 2 maximum level nodes to be merged
		
		leftNode = searchNodes( head, name[0]);		//find and return the 2 nodes
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
}

void secondAlgorithm( treeNode *head, int n, int countNodes ){
	
	treeNode *curr;
	int i = 0, j = 1, k = 0, l = 0;
	double data[countNodes], sum = 0.0, ave = 0.0, p = 0.0, thre = 0.0;
	double **C;
	
	C = (double **)calloc( n, sizeof(double *) );    
	if( C == NULL )
	{
	    printf("couldn't allocate memory \n");
	    exit(EXIT_FAILURE);
	}
    for (i = 0; i < countNodes; i++) {
        C[i] = (double *)calloc( n, sizeof(double) );
        if( C[i] == NULL )
        {
            printf("couldn't allocate memory \n");
            exit(EXIT_FAILURE);
        }	
    }
	
	for( curr = head, i = 0; curr != NULL; curr = curr->nxt, i++ ){
		data[i] = curr->freq;
	}
	
#if SORT	
	double temp = 0.0;	
	for(i = 0; i < countNodes; i++){
		for(k = 0; k < countNodes; k++){
			if( data[k] < data[i] ){
				temp = data[k];
				data[k] = data[i];
				data[i] = temp;
			}
		}
	}
#endif
		
	for(i = 0; i < countNodes; i++){		
		sum += data[i];
	}
	
	p = sum;
	thre = sum/n;
	k = 0;
	
	printf("Memory allocation\n");
	
	for(i = 0; i < countNodes; i++){
		if (ave <= thre ){
			ave += data[i];
			printf("In channel %d memory allocation data  %lf \n", k+1 , data[i] );
			C[k][l] = data[i];
			l++;
		}
		else{
			printf("\n");
			p -= ave;
			ave = 0;
			thre = p/(n - j);
			j++;
			i--;
			k++;
			l = 0;
		}
	}
	free( C ); 
}
