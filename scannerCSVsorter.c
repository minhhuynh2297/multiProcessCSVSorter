#include <string.h> 
#include <dirent.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include "scannerCSVsorter.h"


void printFirst(node** head, FILE* output){
	while((*head)->next!=NULL){
		fprintf(output, "%s,", (*head)->dataType);
		head=&((*head)->next);
	}	
	fprintf(output, "%s", (*head)->dataType);
	fprintf(output, "\n"); 
}

void printLL(node** head, FILE* output){ //prints individual linked lists
	while((*head)->next!=NULL){
	//printf("%s,", (*head)->data);
	fprintf(output, "%s,", (*head)->data);
	head=&((*head)->next);
	}

	//printf("%s\n", (*head)->datsa);
	fprintf(output, "%s", (*head)->data);
	fprintf(output, "\n"); 
}

void printBox(node** sortedLL, node** ptr, char* sort, FILE* output){
	temp1=ptr; //always stays at first node of box
	temp2=ptr; //goes to column to be sorted, and stays there
	printFirst(ptr, output);
	char* data=(char*)malloc(sizeof((char)100)); //holds data
	char* head=(char*)malloc(sizeof((char)100)); //holds columnData

	while((*temp2)!=NULL){ //goes through column to be sorted in box
		i=strcmp(((*temp2)->dataType), sort); //do "
		if(i==0){
			break;
		}
		else{
			temp2=&((*temp2)->next);
		}
	}
	temp1=&((*temp1)->down); //now stays at row 2
	temp2=&((*temp2)->down); //now stays at row 2
	//we are now in useful information rows
	temp3=temp1; //goes down the first column
	temp4=temp2; //goes down the column to be sorted

	while((*sortedLL)->next!=NULL){ //now prints out the sorted LL's

		data=deleteSpace((*sortedLL)->data);
		head=deleteSpace((*sortedLL)->columnData);
		while((*temp3)->down!=NULL && (*temp4)->down!=NULL){ //finds LL to be sorted
			i=strcmp((deleteSpace((*temp4)->data)), data);
			if(i==0){
				break;
			}
			else{
				temp3=&((*temp3)->down);	
				temp4=&((*temp4)->down);			
			}
		}	

		printLL(temp3, output); //prints LL starting at the head
		temp3=temp1; //goes back to row 2
		temp4=temp2; //goes back to row 2
		sortedLL=&((*sortedLL)->next);

	}
	//prints last LL
		temp3=temp1;
		temp4=temp2;
		data=deleteSpace((*sortedLL)->data);
		head=deleteSpace((*sortedLL)->columnData);
		while((*temp3)->down!=NULL && (*temp4)->down!=NULL){ //finds LL to be sorted
			i=strcmp((deleteSpace((*temp4)->data)), data);
			if(i==0){
				break;
			}
			else{
				temp3=&((*temp3)->down);	
				temp4=&((*temp4)->down);			
			}
		}
	printLL(temp3, output); 
	free(data);
	free(head);
	fclose(output);
}

int countP =1;

void countProcess(const char *name){ // this is good 
    DIR *dir; //directory stream
    struct dirent *entry; //holds file serial # and file name

    if (!(dir = opendir(name))){ 
	printf("Error directory could not be opened or does not exist \n");
		return; 
        }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) { // checks if it a directory 
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){ //skips hidden paths
                continue; 
		} 
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name); //directly prints entry->d_name into path[1024]
		//printf("Name of Directory:%s\n",entry->d_name);
		countP++;
            countProcess(path);
            } 
	else if(entry->d_type = DT_REG){// list stuff in directory such as files and checks is its a csv. 
			char *str = entry->d_name;
			//printf("Name of file: %s\n",entry->d_name);
			char ch = '.';
			char *ret;
			char *csv;
			csv = ".csv"; 
			ret = strrchr(str, ch);

				if (strcmp(ret,csv)==0){
					countP++;
				} 

	        }
    }
    closedir(dir);
}
void sort(char * colName,const char* file, char* outputDirectory){ // this works 
	
	int countLL=-1;	
	char *line; //holds line by line 
	line = malloc(10000 * sizeof(char));
	FILE *fp = fopen(file, "r");  
	if(fp == NULL){
		printf("File not found\n");
		exit(-1);
	}
	node* head=NULL;
	node** ptr=&head;
	fgets(line, 10000, fp);
	writeFirstRow(ptr, line); 
	node** oldRow = &head;
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
	node* sortedLL=NULL;
	node** headLL=&sortedLL;
	makeSortLL(headLL, ptr, colName);
	mergeSort(headLL);
//	
	if(opendir(outputDirectory) == NULL){
		int status;
		status = mkdir(outputDirectory, S_IRWXU);
		if(status==1){
			printf("ERROR MAKING NEW DIRECTORY\n");
			exit(0);
		}
	}
	












	FILE *output;

	char *name, *csv;
	size_t length = 0;
	csv = strrchr(file, '.'); //pointer to .csv in name of file
	char* ptrcsv = strstr(file, csv); 
	size_t lengthName = ptrcsv - file;
	name = malloc(length + 1);
	memcpy(name, file, lengthName);
	name[lengthName]='\0';
	if(strcmp(outputDirectory, "") !=0){
		name = strrchr(name, '/');
	}
	int totalLength = strlen(outputDirectory) + strlen(name) + strlen("sorted")+ strlen("file") + strlen(".csv") +1; 

	char fileName[totalLength];
	snprintf(fileName, totalLength + 1, "%s/%ssorted%s%s", outputDirectory, name, colName, csv);
	output=fopen(fileName, "w");
	printBox(headLL, ptr, colName, output);
}

void traverse(char *colname, char *directory, char* outputDirectory) {
	DIR *dir;
	struct dirent *entry;
	int counter = 0;
	dir = opendir(directory);

	int pid0 = 0; 
	int pid1 =0;
	
	if(dir == NULL) {
		return;
	}

	while((entry = readdir(dir))!=NULL){
		if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..")==0){
		continue;
		}
		if(entry->d_type == 4){
			pid0=fork();
			if(pid0==0){
				printf("%d, ", getpid()); 
				fflush(stdout);
				char pathway[1024];
				snprintf(pathway, sizeof(pathway), "%s/%s", directory, entry->d_name);
				traverse(colname, pathway, outputDirectory);
				exit(0);
			}
		}
	else if(entry->d_type = DT_REG){// list stuff in directory such as files and checks is its a csv. 
			char *str = entry->d_name;
			char ch = '.';
			char *ret;
			char *csv;
			csv = ".csv"; 
			ret = strrchr(str, ch);

				if (strcmp(ret,csv)==0){
					counter++;
					pid1 = fork();
					if(pid1==0){
					printf("%d, ", getpid()); 
					fflush(stdout);
					char pathway[1024];
					snprintf(pathway, sizeof(pathway), "%s/%s", directory, entry->d_name);
					sort(colname, pathway, outputDirectory);
					exit(0);
				}
						
				} 

	        }
	}
	if(pid0!=0){
		wait(0);
	}
	if(pid1!=0){
		while(counter>0){
			wait(0);
			counter--;
			}
		}
	return;
}

int main(int argc,char*argv[]){
	printf("Initial PID :%d\n",getpid());
	printf("PIDS of all child processes: ");
	fflush(stdout);
	char * column = (char*)malloc(sizeof(char*)*200);
	char * directory = (char*)malloc(sizeof(char*)*200);
	char* output = (char*)malloc(sizeof(char*)*200);
	column = argv[2];
	if(strcmp(argv[1], "-c")!=0){
		printf("need -c\n");
		exit(0);
	}
	if(argc < 3 || argc > 7){
		printf("wrong input\n");
		exit(0);
	}
	
	if(argc==3){
		strcpy(directory, ".");
		strcpy(output, ".");
	}
	else if(argc==5){
		if(strcmp(argv[3], "-d")==0){
			strcpy(directory, argv[4]);
			strcpy(output, "");
		}
		else{
			strcpy(directory, ".");
			strcpy(output, argv[4]);
		}
	}
	else{
		strcpy(directory, argv[4]);
		strcpy(output, argv[6]);
	}
		
	if(argc!=3 && argv[3]!=NULL){
		if(strcmp(argv[3], "-d")!=0 && strcmp(argv[3], "-o")!=0){
		printf("need -d or -o\n");
		exit(0);
		}
	}
	if(argc > 5 && argv[5]!=NULL && strcmp(argv[5], "-o")!=0){
		printf("need -o\n");
		exit(0);
	}

	countProcess(directory);
	traverse(column,  directory, output);
	printf("\nTotal Number of processes:%d\n",countP);

} 
 

