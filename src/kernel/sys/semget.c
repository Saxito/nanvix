 #include <sys/sem.h>
#include <nanvix/klib.h>


int create(int n, unsigned key){
	struct semaphore s;
	s.index = first_free();
	s.value = n;
	s.size = n;
	s.key = key;

	set_sem(s.index, &s);

	return s.index;

}

int sys_semget(unsigned key){
	int semid = 0;
	for(int i = 0; i < SEM_MAX; i++){
		if(get_key(i) == key && get_value(i) != SEM_MAX+1){
			semid = i;
		}
	}
	if(semid == 0){
		// we create a new semaphore 
		semid = create(0, key);
	}
	return semid;
}



