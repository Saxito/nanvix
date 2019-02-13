#include <sys/sem.h>

int sys_semget(int key){
	int semid = 0;
	for(int i = 0; i<SEM_MAX; i++){
		if(tab_sem[i].index == key){
			semid = i;
		}
	}
	if(semid == 0){
		struct semaphore s;
		semid = s.create(1);
	}
	return semid;
}