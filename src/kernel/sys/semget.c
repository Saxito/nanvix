 #include <sys/sem.h>
#include <nanvix/klib.h>


int create(int n, unsigned key){
	
	int index = first_free();
	set_value(index, n);
	set_size(index, n);
	set_key(index ,key);
	set_active(index);
	set_waiting(index, NULL);
	return index;

}

int sys_semget(unsigned key){
	int semid = 0;
	for(int i = 0; i < SEM_MAX; i++){
		if(get_key(i) == key && is_active(i) != 0){
			semid = i;
		}
	}
	if(semid == 0){
		// we create a new semaphore
		semid = create(0, key);
		kprintf("semaphore %d created", semid);
	}
	return semid;
}



