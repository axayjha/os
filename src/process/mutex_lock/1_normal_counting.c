#include <stdio.h>
#include <pthread.h>

#define NUM_LOOPS 5000000
long long sum = 0;

void counting_thread(void *arg) {
	int offset = *(int *) arg;
	for (int i = 0; i < NUM_LOOPS; i++) {		

		sum += offset;

	}
}

int main(void) {
	int offset1 = 1;
	counting_thread(&offset1);

	int offset2 = -1;
	counting_thread(&offset2);

	printf("Sum = %lld\n", sum);
}