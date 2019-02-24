 #include <sys/sem.h>
#include <nanvix/klib.h>


int create(int n, unsigned key){
	
	struct process * p = NULL;
	int index = first_free();
	kprintf("index :%d", index);
	struct semaphore* s = get_sem(index);
	kprintf("first free done %d", s->index);
	set_value(index, n);
	kprintf("value done %d", s->value);
	set_size(index, n);
	kprintf("size done %d", s->size);
	set_key(index ,key);
	kprintf("key done %d", s->key);
	set_active(index);
	kprintf("active done %d", s->active);
	set_waiting(index, p);
	kprintf("waiting done");
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
		semid = create(1, key);
		kprintf("semaphore %d created", semid);
	}
	return semid;
}



