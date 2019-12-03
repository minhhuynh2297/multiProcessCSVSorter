/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/

//Suggestion: define a struct that mirrors a record (row) of the data set
int a, i, j, k;

typedef struct _node{
	char* dataType;	
	char* data;
	char* columnData;
	struct _node* next;
	struct _node* up;
	struct _node* down; 

}node;


//Suggestion: prototype a mergesort function


