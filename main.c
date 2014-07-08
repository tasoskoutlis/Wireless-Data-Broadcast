#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "types.h"
#include "dataParse.h"
#include "nodeOperations.h"
#include "algorithm.h"
#include "controlTable.h"

#define DEBUG 1
#define CHANNELS 4

int main( int argc, char *argv[] ){
	
	FILE *f;
	char **name;
	int countNodes = 0, countMergedNodes = 0;
	//double *C;
	
	treeNode *head;
	
	if ( argc != 2 ){
		printf("No input file \n");   
		exit( EXIT_FAILURE );
	}

	f = fopen ( argv[1], "r");	
	if ( f == NULL ){
		printf("Error file open \n");
		exit( EXIT_FAILURE );
	}
	
	head = ( treeNode* )malloc( sizeof( treeNode ));
	if ( head == NULL ){
		printf("Couldn't allocate memory \n");
		exit( EXIT_FAILURE );
	}
	
	initializeNode( head );
	head->name = strdup("-1");  //head name has value -1
	
	/*	READ INPUT FILE	 */
	
	countNodes = readInputFile( f, head );
	
	/*	START ALGORITHM	 */
	
	name = ( char** )malloc( 2 * sizeof ( char* ));  //holds the 2 names of nodes to be merged
	if ( name == NULL ){
		printf("Couldn't allocate memory \n");
		exit( EXIT_FAILURE );
	}
	
	/*	FIRST 10 STEPS OF ALGORITHM 1  */
	
	firstStageAlgo( head, name, countNodes);
	
#if 0
	treeNode *node;
	for(node = head->treeNxt; node != NULL ; node = node->treeNxt){
		printf("	name %s    and freq %lf \n", node->name, node->freq);
	}
	printf("\n");
#endif
		
	/*  FIND LEVEL  */	
	
	findLevel( head->treeNxt );
	
#if DEBUG		
 	printTree( head->treeNxt );
#endif
	
	freeTree( head );
	
	initTreeNxt( head );
	
#if 0	
	for(node = head->treeNxt; node != NULL ; node = node->treeNxt){
		printf("EDWWWW	name %s and freq %lf and level %d \n", node->name, node->freq, node->level);
	}
	printf("\n");
#endif	
	
	/*	REST OF THE STEPS OF ALGORITHM 1  */
	
	secondStageAlgo( head, name, countNodes, &countMergedNodes);
	
	printTree( head->treeNxt );
	
	/*  CONTROL TABLE  */
		
	createControlTable( head->treeNxt, countNodes, countMergedNodes);
	
	/*	ALGORITHM 2  */
	
	printf("Starting Second Algorithm \n");
	
	secondAlgorithm( head->nxt, CHANNELS, countNodes );
	
	printf("freeing memory allocation \n");
	
	freeTree( head );
	freeNodes( head );
	free( name );
	//free( C );
	
	printf("finished\n");
	
	return EXIT_SUCCESS;
}