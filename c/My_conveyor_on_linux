#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>

#define NEW_CMD 1
#define CMD 2
#define NEW_PARAMETR 3
#define PARAMETR_OR_CMD 4
#define QUOTE_1 5
#define QUOTE_2 6
#define NO_QUOTE 7
#define MEMMORY_ERROR {fprintf(stderr, "Memmory error\n"); free_pr(&pr, &count_pr); free_all_cmd(&all_cmd, &count_all_cmd); free(buf); return 1;}
#define SYNTAX_ERROR {fprintf(stderr, "Syntax error\n"); free_all_cmd(&all_cmd, &count_all_cmd); return 1;}
#define FORK_ERROR {fprintf(stderr, "Can't do fork()\n"); free_all_cmd(&all_cmd, &count_all_cmd); return 1;}
#define PIPE_ERROR {fprintf(stderr, "Can't do pipe()\n"); free_all_cmd(&all_cmd, &count_all_cmd); return 1;}
#define EXECVP_ERROR {fprintf(stderr, "Command %s not found\n", all_cmd[i][0]); free_all_cmd(&all_cmd, &count_all_cmd); return 1;}

volatile sig_atomic_t flag_stupid_son = 0;

void stupid_son(int s)
{
    signal(SIGUSR1, stupid_son);
    flag_stupid_son = 1;
}

void free_pr(char ***pr, long long int *count_pr)
{
	for(int i=0; i <= (*count_pr); i++) {
		free((*pr)[i]);
		(*pr)[i] = NULL;
	}
	free(*pr);
	(*pr) = NULL;
	(*count_pr) = 0;
	fflush(stdout);
}

void free_all_cmd(char ****all_cmd, long long int *count_all_cmd)
{
	for(int i=0; i < (*count_all_cmd); i++) {
		for(int j=0; (*all_cmd)[i][j] != NULL; j++) {
			free((*all_cmd)[i][j]);
			(*all_cmd)[i][j] = NULL;
		}
		free((*all_cmd)[i]);
		(*all_cmd)[i] = NULL;
	}
	free(*all_cmd);
	(*all_cmd) = NULL;
	(*count_all_cmd) = 0;
}

int new_in_all_cmd(char ****all_cmd, long long int *size_all_cmd, long long int *count_all_cmd, char **new_pr)
{
	(*count_all_cmd)++;
	if ((*count_all_cmd) == (*size_all_cmd)) {
		(*size_all_cmd) *= 2;
		if (((*all_cmd) = realloc((*all_cmd), (*size_all_cmd) * sizeof(char **))) == NULL) return 1;
	}
	(*all_cmd)[(*count_all_cmd) - 1] = new_pr;
	return 0;
}

int new_in_pr(char ***pr, long long int *size_pr, long long int *count_pr, long long int count_buf, char *new_buf)
{
	(*count_pr)++;
	if ((*count_pr) == (*size_pr)) {
		(*size_pr) *= 2;
		if (((*pr) = realloc((*pr), (*size_pr) * sizeof(char *))) == NULL) return 1;
	}
	if (new_buf) {
		if (((*pr)[(*count_pr) - 1] = realloc(new_buf, (count_buf + 1) * sizeof(char))) == NULL) return 1;
		(*pr)[(*count_pr) - 1][count_buf] = 0;
	} else (*pr)[(*count_pr) - 1] = new_buf;
	return 0;
}


int new_in_buf(char **buf, long long int *size_buf, long long int *count_buf)
{
	(*count_buf)++;
	if ((*count_buf) == (*size_buf)) {
		(*size_buf) *= 2;
		if (((*buf) = realloc((*buf), (*size_buf) * sizeof(char *))) == NULL) return 1;
	}
	(*buf)[(*size_buf)] = 0;
	return 0;
}

int main()
{
	long long int size_pr = 10, size_buf = 10, size_all_cmd = 10, count_pr = 0, count_buf = 0, count_all_cmd = 0;
	char c, status = NEW_CMD, quote_flag = NO_QUOTE, ***all_cmd, **pr, *buf;

	buf = NULL;
	pr = NULL;
	if ((all_cmd = (char ***) malloc(size_all_cmd * sizeof(char **))) == NULL) {fprintf(stderr, "Memmory error\n"); return 1;}

	while((c = getchar()) != '\n') {
		switch(status) {
			case NEW_CMD: //верно
				if (c == '|') {SYNTAX_ERROR}
				if (c != ' ') {
					if ((pr = (char **) malloc(size_pr * sizeof(char *))) == NULL) {MEMMORY_ERROR}
					if ((buf = (char *) malloc(size_buf * sizeof(char))) == NULL) {MEMMORY_ERROR}
					count_buf = -1; count_pr = 0;
					if (c == '\'') quote_flag = QUOTE_1; else if (c == '\"') quote_flag = QUOTE_2;
					else {quote_flag = NO_QUOTE; count_buf = 0; buf[count_buf] = c;}
					status = PARAMETR_OR_CMD;
				}
				break;

			case NEW_PARAMETR:
				if (c ==  '|') {
					if (new_in_pr(&pr, &size_pr, &count_pr, count_buf, NULL)) {MEMMORY_ERROR}
					if (new_in_all_cmd(&all_cmd, &size_all_cmd, &count_all_cmd, pr)) {MEMMORY_ERROR}
					status = NEW_CMD;
				}
				else if (c != ' ') {
					if ((buf = (char *) malloc(size_buf * sizeof(char))) == NULL) {MEMMORY_ERROR}
					count_buf = -1;
					if (c == '\'') quote_flag = QUOTE_1; else if (c == '\"') quote_flag = QUOTE_2;
					else {quote_flag = NO_QUOTE; count_buf = 0; buf[count_buf] = c;}
					status = PARAMETR_OR_CMD;
				}
				break;

			case PARAMETR_OR_CMD:
				if (c == '\'' && quote_flag == QUOTE_1 || c == '\"' && quote_flag == QUOTE_2) quote_flag = NO_QUOTE;
				else if (c == '\'' || c == '\"') {
					free_pr(&pr, &count_pr);
					free(buf);
					SYNTAX_ERROR }
				else if (quote_flag == NO_QUOTE) { //это ошибка "blabla ' " ?
					if (new_in_buf(&buf, &size_buf, &count_buf)) {MEMMORY_ERROR}
					if (c == ' ' || c == '|') {
						if (new_in_pr(&pr, &size_pr, &count_pr, count_buf, buf)) {MEMMORY_ERROR}
						if (c == '|') {
							if (new_in_pr(&pr, &size_pr, &count_pr, count_buf, NULL)) {MEMMORY_ERROR}
							if (new_in_all_cmd(&all_cmd, &size_all_cmd, &count_all_cmd, pr)) {MEMMORY_ERROR}
							status = NEW_CMD;
						} else status = NEW_PARAMETR;
					}
					else buf[count_buf] = c;
				} else { if (new_in_buf(&buf, &size_buf, &count_buf)) {MEMMORY_ERROR} buf[count_buf] = c; }
				break;
		}
	}
	if (quote_flag != NO_QUOTE) {free_pr(&pr, &count_pr); free(buf); SYNTAX_ERROR}
	if (status == NEW_CMD) {SYNTAX_ERROR}
	if (new_in_buf(&buf, &size_buf, &count_buf)) {MEMMORY_ERROR}
	if (status == PARAMETR_OR_CMD) {if (new_in_pr(&pr, &size_pr, &count_pr, count_buf, buf)) {MEMMORY_ERROR}}
	if (new_in_pr(&pr, &size_pr, &count_pr, count_buf, NULL)) {MEMMORY_ERROR}
	if (new_in_all_cmd(&all_cmd, &size_all_cmd, &count_all_cmd, pr)) {MEMMORY_ERROR}

	signal(SIGUSR1, stupid_son);
	pid_t pid;
	int fd[2], input;

	for(int i = 0; i < count_all_cmd; i++) {
		if (pipe(fd) == -1) {PIPE_ERROR}
		if ((pid = fork()) == -1) {FORK_ERROR}
		if (!pid) { //сыночек
			if (i != 0) dup2(input, 0); //если первый, то читать нечего
			if (i != count_all_cmd - 1) dup2(fd[1], 1); //если последний то вывод на экран
			close(fd[0]); close(fd[1]);
			execvp(all_cmd[i][0], all_cmd[i]);
			pid = getppid();
			kill(pid, SIGUSR1);
			return 1;
		}
		close(fd[1]);
		input = fd[0];
		wait(NULL);
		if (flag_stupid_son) {EXECVP_ERROR}
	}
	close(fd[0]);
	return 0;
}
