#include <sys/sem.h>


int create(int n){
	struct semaphore s;
	s.index = first_free();
	s.size = n;
	tab_sem[s.index] = s;
	return s.index;

}

int sys_semget(int key){
	int semid = 0;
	for(int i = 0; i<SEM_MAX; i++){
		if(tab_sem[i].index == key && tab_sem[i].size != -1){
			semid = i;
		}
	}

	if(semid == 0){
		// we create a new semaphore 
		semid = create(0);
	}
	
	return semid;
}



