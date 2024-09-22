#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>
#include<stdlib.h>
#include<math.h>

volatile long long num = 0;
volatile int cnt = 0;

void sigIntHandler(int s) {
	signal(SIGINT, sigIntHandler);
	cnt++;
	if (cnt == 4) _exit(0);
	printf("%lld\n", num); fflush(stdout);
}

void sigTermHandler(int s) {
	_exit(0);
}

int main() {
	long long i, nextnum, low, high;
	int found = 0;
	if(!(scanf("%lld", &low) == 1) || !(scanf("%lld", &high) == 1)) return 0;
	printf("%d\n", getpid()); fflush(stdout);
	signal(SIGINT, sigIntHandler);
	signal(SIGTERM, sigTermHandler);
	for(nextnum=low; nextnum < high; nextnum++) {
		found = 1;
		for (i = 2; i < sqrt(nextnum) + 1; i+=1) {
			if (nextnum % i == 0) {
				found = 0;
				break;
			}
		}
		if (found) num = nextnum;
	}
	printf("-1\n"); fflush(stdout);
	_exit(0);
}
