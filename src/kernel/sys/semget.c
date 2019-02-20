#include <sys/sem.h>


int create(int n){
	struct semaphore s;
	s.index = first_free();
	s.size = n;
	set_sem(s.index, s);
	return s.index;

}

int sys_semget(int key){
	int semid = 0;
	for(int i = 0; i<SEM_MAX; i++){
		if(get_index(i) == key && get_size(i) != -1){
			semid = i;
		}
	}

	if(semid == 0){
		// we create a new semaphore 
		semid = create(0);
	}
	
	return semid;
}



