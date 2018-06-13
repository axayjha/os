#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>

enum {
	DONE = 0xfde,
	NOT_DONE = 0xfdc,
	SINGLE = 0xfdd,
	CONSECUTIVE = 0xfda
};

typedef struct mem_partition mem_partition;
struct mem_partition {
	char id;
	uint64_t start_addr;
	int size;
	mem_partition *next;
};

mem_partition* new_node(char id, uint64_t start_addr, int size)
{
	mem_partition *node = (mem_partition *)malloc(sizeof(mem_partition));
	node->id = id;
	node->start_addr = start_addr;
	node->size = size;
	node->next = NULL;
	return node;
}

mem_partition*
addend(mem_partition *listp, 
		 char id, 
		 uint64_t start_addr,
		 int size)
{
	mem_partition *walkp = listp;
	if(listp == NULL)
		return new_node(id, start_addr, size);

	for( ; walkp->next != NULL; walkp = walkp->next)
			;

	walkp->next = new_node(id, start_addr, size);
    return listp;
}

void display(mem_partition *walkp)
{	
	for( ; walkp != NULL; walkp = walkp->next)
			printf("[ %c| %ld| %u ]-> ", walkp->id, walkp->start_addr, walkp->size);
	printf(".\n");	
}

void first_fit(mem_partition *listp, char id, int size)
{	
	int flag = NOT_DONE;
	mem_partition *walkp = listp;
	if(listp == NULL)
		fprintf(stderr, "Memory partition not allocated\n");

	for( ; walkp != NULL; walkp = walkp->next) {
		if (walkp->id == 'H' && walkp->size >= size) {
			if (walkp->size - size > 0){
				mem_partition* temp = walkp->next;
				walkp->next = new_node('H', (walkp->start_addr + size), (walkp->size - size));
				walkp->next->next = temp;
			}
			walkp->id = id;
			walkp->size = size;
			flag = DONE;
			break;
		}
	}
	walkp = listp;
	if (flag == NOT_DONE){
		fprintf(stderr, "Process [id: %c] larger than partition\n", id);
	}
}


void best_fit(mem_partition *listp, char id, int size)
{	
	int flag = NOT_DONE;
	mem_partition *walkp = listp;
	int min = INT_MAX;
	if(listp == NULL)
		fprintf(stderr, "Memory partition not allocated\n");

	for( ; walkp != NULL; walkp = walkp->next) {
		if (walkp->id == 'H' && walkp->size >= size) {
			if (min > walkp->size - size) 
				min = walkp->size - size;
		}			
	}

	for(walkp = listp ; walkp != NULL; walkp = walkp->next) {
		if ((walkp->size - size) == min){
			if (walkp->size - size > 0){
				mem_partition* temp = walkp->next;
				walkp->next = new_node('H', (walkp->start_addr + size), (walkp->size - size));
				walkp->next->next = temp;
			}
			walkp->id = id;
			walkp->size = size;
			flag = DONE;
			break;
		}		
	}

	walkp = listp;
	if (flag == NOT_DONE){
		fprintf(stderr, "Process [id: %c] larger than partition\n", id);
	}
}

void worst_fit(mem_partition *listp, char id, int size)
{	
	int flag = NOT_DONE;
	mem_partition *walkp = listp;
	int max = INT_MIN;
	if(listp == NULL)
		fprintf(stderr, "Memory partition not allocated\n");

	for( ; walkp != NULL; walkp = walkp->next) {
		if (walkp->id == 'H' && walkp->size >= size) {
			if (max < walkp->size - size) 
				max = walkp->size - size;
		}			
	}

	for(walkp = listp ; walkp != NULL; walkp = walkp->next) {
		if ((walkp->size - size) == max){
			if (walkp->size - size > 0){
				mem_partition* temp = walkp->next;
				walkp->next = new_node('H', (walkp->start_addr + size), (walkp->size - size));
				walkp->next->next = temp;
			}
			walkp->id = id;
			walkp->size = size;
			flag = DONE;
			break;
		}		
	}

	walkp = listp;
	if (flag == NOT_DONE){
		fprintf(stderr, "Process [id: %c] larger than partition\n", id);
	}
}

mem_partition* compact_partition(mem_partition* listp)
{
	mem_partition* walkp = listp;
	static int total_size = 0;
	uint64_t end_addr = 0;
	if(listp == NULL)
		fprintf(stderr, "Memory partition not allocated\n");
	for( ; walkp != NULL; walkp = walkp->next) {
		if (walkp->id == 'H') {
			total_size += walkp->size;			
		}
		else{
			walkp->start_addr -= total_size;
		}
		end_addr = walkp->start_addr+ walkp->size;
	}

	mem_partition* prev = NULL;
	for(walkp = listp; walkp!= NULL; walkp = walkp->next) {
		if (walkp->id == 'H') {
			if(prev == NULL)
				listp = walkp->next;
			else
				prev->next = walkp->next;
			free(walkp);
		}
		prev = walkp;
	}
	listp = addend(listp, 'H', end_addr, total_size);
	return listp;
}



int main(int argc, char *argv[])
{
	mem_partition *list = new_node('G', 0, 100 );
	list = addend(list, 'H', 100, 80);
	list = addend(list, 'J', 180, 80);
	list = addend(list, 'H', 260, 40);
	list = addend(list, 'N', 300, 40);
	best_fit(list, 'L', 30);
	display(list);
	list = compact_partition(list);
	display(list);
	return 0;
}