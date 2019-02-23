#include <unistd>
#include <stdlib>
#include <sys/types.h>
#include <stdio>

#include <sys/shm.h>
#include "shm_com.h"

/*
void calculateQValue(int row){
	int k=0;
	int j=0;
	int newValue=0;
	
	for (k=0; k<4; k++){
		for (j=0; j<4; j++){
			newValue = newValue + M[row,j]*N[j,k];
		}
		Q[row,k] = newValue;
	}
}*/

void printMatrix(int matrix[4][4]){
	for (k=0; k<4; k++){
		for (j=0; j<4; j++){
			if (j != 3){
				printf("%d,", matrix[k,j]);
			} else {
				printf("%d", matrix[k,j]);
			}
		}
	}
}

int main(int argc, char* argv[])
{

	void *shared_memory = (void *)0;
	
	int shmid;
	
	int numberOfChildren;
	if (argc > 1){
		numberOfChildren = argv[1] - '0';
	}
	int k=0;
	int j=0;
	int i=0;
	int newValue=0;
	
	int M[4][4] = {
		{1,2,3,4},
		{5,6,7,8},
		{4,3,2,1},
		{8,7,6,5}
	};
	
	int N[4][4] = {
		{1,3,5,7},
		{2,4,6,8},
		{7,3,5,7},
		{8,6,4,2}
	};
	
	int Q[4][4];
	
	pid_t pid, pid1;
	
	pid = fork();
	pid1 = fork();
	
	shmid = shmget((key_t)2156, sizeof(int[4][4]), 0666 | IPC_CREAT);

	if (shmid == -1) {
		fprintf(stderr, "shmget failure\n");
		exit(EXIT_FAILURE);
	}

	shared_memory = shmat(shmid, (void *)0, 0);
	if (shared_memory == (void *)-1) {
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}
	
	Q = (int[4][4] *)shared_memory;
	
	if ((pid == -1)||(pid1 == -1)){
		perror("FAILED TO FORK");
		exit("EXIT FAILURE");
	} else if ((pid > 0)&&(pid1 > 0)){
		if (numberOfChildren <= 1){
			printf("Child process: working with rows(1-4)\n");
			for (i=0; i<4; i++){
				for (k=0; k<4; k++){
					for (j=0; j<4; j++){
						newValue = newValue + M[i][j]*N[j][k];
					}
					Q[i][k] = newValue;
				}
			}
		} else if (numberOfChildren == 2){
			prinf("Child process: working with rows(1-2)");
			for (i=0; i<2; i++){
				for (k=0; k<4; k++){
					for (j=0; j<4; j++){
						newValue = newValue + M[i][j]*N[j][k];
					}
					Q[i][k] = newValue;
				}
			}
		} else if (numberOfChildren >= 4){
			printf("Child Process: working with row 1\n");
			for (k=0; k<4; k++){
				for (j=0; j<4; j++){
					newValue = newValue + M[0][j]*N[j][k];
				}
				Q[0][k] = newValue;
			}
		}
		
		wait();
		printf("Matrix M\n");
		
		for (k=0; k<4; k++){}
			for (j=0; j<4; j++){
				if (j != 3){
					printf("%d,", M[k][j]);
				} else {
					printf("%d\n", M[k][j]);
				}
			}
		}
		
		printf("Matrix N\n");
		
		for (k=0; k<4; k++){}
			for (j=0; j<4; j++){
				if (j != 3){
					printf("%d,", N[k][j]);
				} else {
					printf("%d\n", N[k][j]);
				}
			}
		}
		
		printf("Matrix Q\n");
		
		for (k=0; k<4; k++){}
			for (j=0; j<4; j++){
				if (j != 3){
					printf("%d,", Q[k][j]);
				} else {
					printf("%d\n", Q[k][j]);
				}
			}
		}
	} else if ((pid == 0)&&(pid1 > 0)){
		if (numberOfChildren == 2){
			printf("Child Process: working with rows(3-4)");
			for (i=2; i<4; i++ ){
				for (k=0; k<4; k++){
					for (j=0; j<4; j++){
						newValue = newValue + M[i][j]*N[j][k];
					}
					Q[i][k] = newValue;
				}
			}
		} else if (numberOfChildren >= 4 ){
			printf("Child Process: working with row 2\n");
			for (k=0; k<4; k++){
				for (j=0; j<4; j++){
					newValue = newValue + M[1][j]*N[j][k];
				}
				Q[1][k] = newValue;
			}
		}
		
		wait();
	} else if ((pid > 0)&&(pid1 == 0 )){
		if (nuumberOfChildren >= 4){}
			printf("Child Process: working with row 3\n");
			for (k=0; k<4; k++){
				for (j=0; j<4; j++){
					newValue = newValue + M[2][j]*N[j][k];
				}
				Q[2][k] = newValue;
			}
		}
	} else if ((pid == 0)&&(pid1 == 0)){
		if (numberOfChildren >= 4){
			printf("Child Process: working with row 4\n");
			for (k=0; k<4; k++){
				for (j=0; j<4; j++){
					newValue = newValue + M[3][j]*N[j][k];
				}
				Q[3][k] = newValue;
			}
		}
	}


	exit(EXIT_SUCCESS);
}