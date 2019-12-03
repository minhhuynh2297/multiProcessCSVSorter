#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.c" 
#include <ctype.h>

node* curr;
node** temp1;
node** temp2;
node** temp3;
node** temp4;

char* deleteQ(char* word){ //this works, but I don't know why it doesn't work in the cod
	char* newWord=(char*)malloc(sizeof((char)100));
	int start=0;
	int finish=strlen(word)-1;
	while(ispunct((unsigned char)word[start])){
		start++;
	}
	while(ispunct((unsigned char)word[finish]) && (finish >= start)){
		finish--;
	}
	for(i = start; i<=finish; i++){
		newWord[i-start]=word[i];
	}
	newWord[i-start] ='\0';

	return newWord;
}

char* deleteSpace(char* word){ //implement this in later
	char* newWord=(char*)malloc(sizeof((char)100));
	int start=0;
	int finish=strlen(word)-1;
	while(isspace((unsigned char)word[start])){
		start++;
	}
	while(isspace((unsigned char)word[finish]) && (finish >= start)){
		finish--;
	}
	for(i = start; i<=finish; i++){
		newWord[i-start]=word[i];
	}
	newWord[i-start] ='\0';

	return newWord;
}





			



void appendDataType(node** ptr, char* data){ //creates nodes in the first row of our "array" that only has dataType (food, calories)

	if((*ptr)==NULL){
		(*ptr)=(node*)malloc(sizeof(node));
		(*ptr)->dataType=data;
		(*ptr)->next=NULL;	

	}
	else{
	
		temp1 = ptr;

		while((*temp1)->next!=NULL){

			temp1=&((*temp1)->next);

		}
		(*temp1)->next=(node*)malloc(sizeof(node));
		(*temp1)->next->dataType=data;
		(*temp1)->next->next=NULL;
	}
}

void appendData(node** ptr, char* data){ //creates the rest of our our box, making nodes that has data, like celery, 200, etc.

	if((*ptr)==NULL){
		(*ptr)=(node*)malloc(sizeof(node));
		(*ptr)->data=data;
		(*ptr)->next=NULL;	

	}
	else{
	
		temp1 = ptr;

		while((*temp1)->next!=NULL){

			temp1=&((*temp1)->next);

		}

		(*temp1)->next=(node*)malloc(sizeof(node));
		(*temp1)->next->data=data;
		(*temp1)->next->next=NULL;



	}
}

void appendSort(node** ptr, char* colData, char* data){ //creates nodes for LL to be sorted
	if((*ptr)==NULL){
		(*ptr)=(node*)malloc(sizeof(node));
		(*ptr)->data=data;
		(*ptr)->columnData=colData;
		(*ptr)->next=NULL;	

	}
	else{
	

		while((*ptr)->next!=NULL){
			ptr=&((*ptr)->next);

		}

		(*ptr)->next=(node*)malloc(sizeof(node));
		(*ptr)->next->data=data;
		(*ptr)->next->columnData=colData;
		(*ptr)->next->next=NULL;

	}
}


char* getWords(int* ptr, char* entireData){ //returns a word, and increases a counter in writeLL
	j=0;
	char* individualWords=(char*)malloc(sizeof((char)100));

	for(i=(*ptr); i<10000; i++){ 

		if(entireData[i]=='\0'){ //exits at end of line;		
			individualWords[j]='\0';
			(*ptr)=-1;
			return individualWords;
		}

		if(entireData[i]!=','){ //writes everything until a comma
			individualWords[j]=entireData[i];
			j++;
		}
		else{ 
			individualWords[j]='\0';
			i++;
			(*ptr)=i;
			return individualWords;
		}
	}
	return individualWords;
}

void writeFirstRow(node** ptr, char* entireData){ //writes the first row with nodes having data type like Food, Calories
	int count=0;
	int* pCount=&count;
	while(count!=-1){
		appendDataType(ptr, getWords(pCount, entireData));		
	}
}

void writeLL(node** ptr, char* entireData){ //makes the rest of the "box", with linked lists holding data, like celery and 200
	int count=0;
	int* pCount=&count;
	while(count!=-1){
		appendData(ptr, getWords(pCount, entireData));		
	}
 
}

void connectLL(node** oldHead, node** newHead){	//makes up and down on every node
	temp1=oldHead;
	temp2=newHead;
	while((*temp1)->next!=NULL && (*temp2)->next!=NULL){
		(*temp1)->down=(*temp2);
		(*temp2)->up=(*temp1);	
		(*temp2)->dataType=(*temp1)->dataType;
		temp1=&((*temp1)->next);
		temp2=&((*temp2)->next);
		if((*temp1)->next!=NULL && (*temp2)->next==NULL){
			printf("not a square matrix\n");
			exit(0);
		}
		if((*temp1)->next==NULL && (*temp2)->next!=NULL){
			printf("not a square matrix\n");
			exit(0);
		}
	}
}

void makeSortLL(node** headLL, node** ptr, char* sortData){ //creates the LL to be sorted
temp1=ptr;
temp2=ptr;

	while((*temp2)->next!=NULL){ //finds column of the category to be sorted	
		i=strcmp((deleteSpace(deleteQ((*temp2)->dataType))), sortData);
		if(i==0){ //found column
			break;
		}
		else{
			temp2=&((*temp2)->next);
		}
	}

	

	//temp1 should still be at the head of the first LL in our box
	//temp 2 should now be at the column to be sorted

	temp1=&((*temp1)->down);
	temp2=&((*temp2)->down);
	
	while((*temp1)->down!=NULL && (*temp2)->down!=NULL){
		appendSort(headLL, (*temp1)->data, (*temp2)->data);
		temp1=&((*temp1)->down);
		temp2=&((*temp2)->down);	
	}

}
