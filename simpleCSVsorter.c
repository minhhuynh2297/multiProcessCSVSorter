#include "sorter.h"

int main(int argc, char* argv[]){

	if(argc < 2)
		exit(-1);
	

	int countLL=-1;	

	char *line; //holds line by line 

	line = malloc(10000 * sizeof(char));

	
	FILE *fp = fopen(argv[1], "r"); //reads in the file; 

	if(fp == NULL){
		printf("File not found\n");
		exit(-1);
	}
	node* head=NULL;
	node** ptr=&head;

	fgets(line, 10000, fp);

	writeFirstRow(ptr, line); //first row;

	node** oldRow = &head;

//creates the "box"
	while(!feof(fp)){
		if(feof(fp)){
			break;
		}
		fgets(line, 10000, fp);
		node* newHead=NULL;
		node** newRow=&newHead;
		writeLL(newRow,line);
			
		countLL++;
		connectLL(oldRow, newRow);
		
		oldRow=&((*oldRow)->down);
		

	} 
	free(line);
	//printf("%s\n", argv[2]);
/*	while((*ptr)->next!=NULL){ // we tried to do it, it breaks. color,duration / color works, duration doesn't
		i=strcmp((*ptr)->dataType, argv[2]);
		if(i==0){
			break;
		}
		else{
			printf("Column not found!!!!\n");
			exit(-1);
		}
	
	}
*/

	node* sortedLL=NULL;
	node** headLL=&sortedLL;
	makeSortLL(headLL, ptr, argv[2]);
	mergeSort(headLL);
	printBox(headLL, ptr, argv[2]);
	return 0;
}




















