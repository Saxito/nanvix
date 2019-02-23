 #include <sys/sem.h>
#include <nanvix/klib.h>


int create(int n, unsigned key){
	struct semaphore s;
	struct process * p = NULL;
	s.index = first_free();
	kprintf("first free done %d", s.index);
	s.value = n;
	kprintf("value done %d", s.value);
	s.size = n;
	kprintf("size done %d", s.size);
	s.key = key;
	kprintf("key done %d", s.key);
	s.active = 1;
	kprintf("active done %d", s.active);
	s.waiting = p;
	kprintf("waiting done");
	echo(s);
	set_sem(s.index, s);
	kprintf("set_sem done");
	return s.index;

}

int sys_semget(unsigned key){
	int semid = 0;
	for(int i = 0; i<SEM_MAX; i++){
		if(get_key(i) == key && get_size(i) != -1){
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



