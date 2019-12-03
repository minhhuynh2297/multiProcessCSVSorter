#include "simpleCSVsorter.h"

void split(node* head, node** a, node** b){
	
	node* first;
	node* second;

	if(head==NULL || head->next==NULL){
		(*a)=head;
		(*b)=NULL;
	}
	else{
		second=head;
		first=head->next;
		
		while(first!=NULL){
			first=first->next;		
			
			if(first !=NULL){
				second=second->next;
				first=first->next;
			}
		}
		
	}
	(*a)=head;
	(*b)=second->next;
	second->next=NULL;

}

node* mergeList(node* a, node* b){

	node* mergedList=NULL;
	
	if(a==NULL){
		return b;
	}
	else if(b==NULL){
		return a;
	}

	if(strcmp(a->data, b->data)<0){
		mergedList=a;
		mergedList->next = mergeList(a->next, b);
	}
	else{
		mergedList=b;
		mergedList->next = mergeList(a, b->next);
		
	}

	return mergedList;
}



void mergeSort(node** headLL){
//	printf("\n");
	node* curr = *headLL;
	node* a=NULL;
	node* b=NULL;

	if(curr==NULL || curr->next==NULL){ //empty case
		return;
	}
	
	split(curr, &a, &b);
	
	mergeSort(&a);
;
	mergeSort(&b);
	
	(*headLL)=mergeList(a, b);

}
