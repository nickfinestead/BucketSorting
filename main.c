/*
	Name: BucketSortNF.c
	Author: Nicholas Finestead
	Date: 3/9/2023
	Purpose: Demonstrating a BucketSort with a Linked List

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define size(a) (sizeof(a)/sizeof(int))

#define MAX 0
#define MIN 1

typedef struct node
{
    int Data;
    struct node *next_ptr;
    
}Node;


// Sort Function
void bucket_sort(int size, int Array[], int max, int min);


// Linked List Functions
void AddToLL(Node **LLH, int Value);
void sortedInsert(Node** head_ref, int Value);
int CopyListToArray(Node **LLH, int Array[], int index);


// Helper Functions
int findmaxNmin(int Array[], int Size, int MaxNMin[2]);
void PrintList(Node *LLH);

int main()
{
    int Array[5] = {10,4, 6, 1, 0};
    size_t SizeA = size(Array);
	
	int MaxNMin[2] = {0};
	
    if(findmaxNmin(Array, SizeA, MaxNMin) != -1) // Returns -1 if min and max are equal after looping over the array
		bucket_sort(SizeA, Array, MaxNMin[0], MaxNMin[1]);
	else
	{
		printf("Array is size 1 and already sorted, exiting now.\n");
		exit(0);
	}

	for(int i = 0; i < SizeA; i++)
		printf("%d ", Array[i]); 
	printf("\n");
    return 0;
}

int findmaxNmin(int Array[], int Size, int MaxNMin[2])
{
    MaxNMin[MAX] = Array[0];
	MaxNMin[MIN] = Array[0];
    
    for(int i = 1; i < Size; i++)
    {
        
        if(MaxNMin[MAX] < Array[i])
            MaxNMin[MAX] = Array[i];
		if(MaxNMin[MIN] > Array[i])
			MaxNMin[MIN] = Array[i];
    }        
	
	if(MaxNMin[MAX] == MaxNMin[MIN]) // Either Loop failed, or Size == 1 which means array is sorted
		return -1;
	
	return 0;
}

int findmin(int Array[], int Size)
{
    int min = Array[0];
    
    for(int i = 1; i < Size; i++)
    {
        if(min > Array[i])
            min = Array[i];
    } 
    return min;
}

void bucket_sort(int size, int Array[], int max, int min)
{
    Node *LLH[size];
    int index = 0;
    for(int i = 0; i < size; i++)
        LLH[i] = NULL;
        
    for(int i = 0; i < size; i++)
    {
      int BucketIndex =   floor((size * (Array[i] - min)) / (1 + max - min));
      sortedInsert(&LLH[BucketIndex], Array[i]);
    }
    
    for(int i = 0; i < size; i++)
    {
        if(LLH[i] != NULL)
		{
			//PrintList(LLH[i]);
            index = CopyListToArray(&LLH[i], Array, index);
		}
    }
    
    
}

void PrintList(Node *LLH)
{
	Node *tmp_ptr = LLH;
	while(tmp_ptr != NULL)
	{
		printf("%d\t",tmp_ptr->Data);
		tmp_ptr = tmp_ptr->next_ptr;
	}
		printf("\n");
}

int CopyListToArray(Node **LLH, int Array[], int index)
{
    Node *temp_ptr = NULL;
    while((*LLH) != NULL)
    {
        temp_ptr = *LLH;
        Array[index] = temp_ptr->Data;
        *LLH = (*LLH)->next_ptr;
        free(temp_ptr);
        index++;
    }
    return index;
}


void sortedInsert(Node** head_ref, int Value)
{
	Node *newNode = NULL;
	newNode = malloc(sizeof(Node)); // if NewNode is not set to NULL first valgrind complains
    newNode->next_ptr = NULL;
    newNode->Data = Value;
    
	
    if (*head_ref == NULL || (*head_ref)->Data >= newNode->Data) 
	{
        newNode->next_ptr = *head_ref;
        *head_ref = newNode;
    }
    else 
	{
        Node *current = *head_ref;
        while(current->next_ptr != NULL && current->next_ptr->Data < newNode->Data)
            current = current->next_ptr;
        newNode->next_ptr = current->next_ptr;
        current->next_ptr = newNode;
    }
}

/*
void AddToLL(Node **LLH, int Value)
{
    Node *temp_ptr = *LLH;
    Node *newNode = malloc(sizeof(Node));
    newNode->next_ptr = NULL;
    newNode->Data = Value;
    if(*LLH == NULL || (*LLH)->Data >= newNode->Data)
    {
        newNode->next_ptr = *LLH;
        *LLH = newNode;
    }
    else
	{
		while(temp_ptr->next_ptr != NULL && temp_ptr->Data < newNode->Data)
			temp_ptr = temp_ptr->next_ptr;
			newNode->next_ptr = temp_ptr->next_ptr;
			temp_ptr->next_ptr = newNode;
	}
}*/
