#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nodeOperations.h"
#include "dataParse.h"

int readInputFile( FILE *f, treeNode *head ){
	
	char line[1024], *tok;
	treeNode *node, *curr;
	int countNodes = 0, key = 1;
	
	while ( fgets( line, 1024, f) ) {

		// Skip empty lines
		if (line[0] == '\n') {
			continue;
		}
		
		node = ( treeNode* )malloc( sizeof( treeNode ));		//memory allocation for every node
		if ( node == NULL ){
			printf("Couldn't allocate memory \n");
			exit( EXIT_FAILURE );
		}
		
		initializeNode( node );
		
		tok = strtok( line, " \n");		//get name of node
			
		node->name = strdup(tok);
		
		tok = strtok( NULL, " \n");		//get frequency
			
		node->freq = strtod( tok, 0);
		
		node->key = key;
		
		countNodes++;	//hold number of nodes
		key++;
		
		for( curr = head ; curr->nxt != NULL; curr = curr->nxt );
		
		node->prv = curr;
		curr->nxt = node;
		curr->treeNxt = node;
	}
	return countNodes;
}