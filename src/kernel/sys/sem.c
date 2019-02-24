#include <sys/sem.h>
#include <nanvix/pm.h>
#include <nanvix/klib.h>


PUBLIC struct semaphore * tab_sem[SEM_MAX];

PUBLIC void init_tab_sem() {
	for (int i = 0; i < SEM_MAX; i++) {
		(*tab_sem+i)-> active = 0;
		(*tab_sem+i)-> index = i;
	}
}


PUBLIC int get_size(int id) {
	return (*tab_sem+id)->size;
}

PUBLIC void set_size(int id, int val) {
	(*tab_sem+id)->size = val;
}

PUBLIC int get_value(int id) {
	return (*tab_sem+id)->value;
}

PUBLIC void set_value(int id, int v){
	(*tab_sem+id)-> value = v;
}

PUBLIC struct semaphore * get_sem(int id) {
	return (*tab_sem+id);
}

// PUBLIC void set_sem(int id, struct semaphore* sem) {
// 	// kprintf("id set = %d", id);
// 	struct semaphore* s = tab_sem[id+1];
// 	// (*tab_sem+id) = sem;
// 	// tab_sem[id+1]= s;

// }

PUBLIC unsigned get_key(int id){
	return (*tab_sem+id)->key;
}

PUBLIC void set_key(int id, unsigned k){
	(*tab_sem+id)->key = k;
}

PUBLIC int is_active(int id) {
	return (*tab_sem+id)->active;
}

PUBLIC void set_active(int id) {
	(*tab_sem+id)-> active = 1;
}


PUBLIC void set_desactive(int id) {
	(*tab_sem+id)-> active = 0;
}

PUBLIC struct process* get_waiting(int id){
	return (*tab_sem+id)->waiting;
}
PUBLIC void set_waiting(int id, struct process* pro){
	(*tab_sem+id)->waiting = pro;
}

PUBLIC void echo(struct semaphore* s) {
	kprintf("index : %d", s->index);
	kprintf("value : %d", s->value);
	kprintf("size : %d", s->size);
	kprintf("key : %d", s->key);
	kprintf("active : %d", s->active);
}

PUBLIC void down(int id) {
	kprintf("debut down");
	echo((*tab_sem+id));
	if (get_size(id) > 0) {
		kprintf("debut if");
		set_size(id, get_size(id)-1) ;
		kprintf("fin if");

	}else {
		kprintf("debut else");
		struct process* wait = get_waiting(id);
		sleep(wait->chain, curr_proc->priority);
		kprintf("fin else");

	}
	kprintf("fin down");

}

PUBLIC void up(int id) {
	kprintf("debut up");

	if (get_size(id) == 0) {
		struct process* wait = get_waiting(id);
		wakeup(wait->chain);
	}else {
		set_size(id, get_size(id)+1) ;
	}
	kprintf("fin up");

}

PUBLIC int first_free() {
	for (int i = 0; i < SEM_MAX; i++) {
		// kprintf("active i: %d  : %d ", i, is_active(i));
		if (is_active(i) == 0) {
			// kprintf("first free : %d", i);
			return i;
		}
	}
	// kprintf("error first_free");
	return -1;
}

