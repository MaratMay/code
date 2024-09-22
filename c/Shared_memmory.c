#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<fcntl.h>
#define FORK_ERROR {fprintf(stderr, "Can't do fork()\n"); shmdt(shmaddr); shmctl(shmid, IPC_RMID, NULL); semctl(semid, 0, IPC_RMID); return 1;}
#define SHARED_MEM_ERROR {fprintf(stderr, "Shared memory problem\n"); return 1;}
#define HOW_MANY_SON 3
#define COUNT_LETTERS 26
#define COUNT_NUM 10
int main(int argc, char **argv) 
{
	unsigned int n;
	scanf("%d", &n);

	int file;
	if ((file = open("MZ17.txt", O_CREAT | O_TRUNC, 0666)) == -1) {fprintf(stderr, "File() problem\n"); return 1;}
	close(file);

	key_t key;
	if ((key = ftok("MZ17.txt", 0)) == -1) {fprintf(stderr, "Ftok() problem\n"); return 1;}

	union semun {
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	int semid;
	if ((semid = semget(key, 3, IPC_CREAT | 0666)) == -1) {fprintf(stderr, "Semget() problem\n"); return 1;}
	semctl(semid, 0, SETVAL, 0);
	semctl(semid, 1, SETVAL, 0);
	semctl(semid, 2, SETVAL, 0);
	struct sembuf unlock_son_1 = {0, 1, 0}, unlock_son_2 = {1, 1, 0}, unlock_son_3 = {2, 1, 0},
		lock_son_1 = {0, -1, 0}, lock_son_2 = {1, -1, 0}, lock_son_3 = {2, -1, 0};

	char *shmaddr=NULL;
	int shmid;
	if ((shmid = shmget(key, sizeof(char) * (n + 1), IPC_CREAT | 0666)) == -1) {perror("jopa");SHARED_MEM_ERROR};
	if ((shmaddr = (char*) shmat(shmid, NULL, 0)) == (void*) -1) {shmctl(shmid, IPC_RMID, NULL); SHARED_MEM_ERROR};

	pid_t son_1, son_2, son_3;
	int i, my_num, limit_num;
	if ((son_1 = fork()) == -1) {FORK_ERROR}
	if (!son_1) { //сын1
		my_num = 0;
		limit_num = n / HOW_MANY_SON;
		if (n % HOW_MANY_SON) limit_num++;
		for (i=0; i < limit_num; i++) {
			semop(semid, &lock_son_1, 1);
			shmaddr[i * HOW_MANY_SON + my_num] = 'a' + i % COUNT_LETTERS;
			shmaddr[i * HOW_MANY_SON + my_num + 1] = 0;
			printf("son1: %s\n", shmaddr); fflush(stdout);
			semop(semid, &unlock_son_2, 1);
		}
		shmdt(shmaddr);
		return 0;
	}  

	if ((son_2 = fork()) == -1) {kill(son_1, SIGKILL); FORK_ERROR}
	if (!son_2) { //сын2
		my_num = 1;
		limit_num = n / HOW_MANY_SON;
		if (n % HOW_MANY_SON == 2) limit_num++;
		for (i=0; i < limit_num; i++) {
			semop(semid, &lock_son_2, 1);
			shmaddr[i * HOW_MANY_SON + my_num] = '0' + i % COUNT_NUM;
			shmaddr[i * HOW_MANY_SON + my_num + 1] = 0;
			printf("son2: %s\n", shmaddr); fflush(stdout);
			semop(semid, &unlock_son_3, 1);
		}
		shmdt(shmaddr);
		return 0;
	}

	if ((son_3 = fork()) == -1) {kill(son_1, SIGKILL); kill(son_2, SIGKILL); FORK_ERROR}
	if (!son_3) { //сын3
		my_num = 2;
		limit_num = n / HOW_MANY_SON;
		for (i=0; i < limit_num; i++) {
			semop(semid, &lock_son_3, 1);
			shmaddr[i * HOW_MANY_SON + my_num] = 'A' + i % COUNT_LETTERS;
			shmaddr[i * HOW_MANY_SON + my_num + 1] = 0;
			printf("son3: %s\n", shmaddr); fflush(stdout);
			semop(semid, &unlock_son_1, 1);
		}
		shmdt(shmaddr);
		return 0;
	}
	
	semop(semid, &unlock_son_1, 1);
	while (wait(NULL) != -1) {}
	printf("father: %s\n", shmaddr); fflush(stdout);
	shmdt(shmaddr);
	shmctl(shmid, IPC_RMID, NULL);
	semctl(semid, 0, IPC_RMID);
	return 0;
}
