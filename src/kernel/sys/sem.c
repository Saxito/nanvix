#include <sys/sem.h>
#include <nanvix/pm.h>
#include <nanvix/klib.h>


PUBLIC struct semaphore * tab_sem[SEM_MAX];

PUBLIC void init_tab_sem() {
	for (int i = 0; i < SEM_MAX; i++) {
		tab_sem[i]->active = 0;
		tab_sem[i]->index = i;
	}
}

PUBLIC int get_size(int id) {
	return tab_sem[id]->size;
}

PUBLIC void set_size(int id, int val) {
	tab_sem[id]->size = val;
}

PUBLIC int get_value(int id) {
	return tab_sem[id]->value;
}

PUBLIC struct semaphore * get_sem(int id) {
	return tab_sem[id];
}

PUBLIC void set_sem(int id, struct semaphore sem) {
	tab_sem[id] = &sem;
}

PUBLIC unsigned get_key(int id){
	return tab_sem[id]->key;
}

PUBLIC _Bool is_active(int id) {
	return tab_sem[id]->active;
}

PUBLIC void set_active(int id, _Bool val) {
	tab_sem[id]->active = val;
}

PUBLIC void echo(struct semaphore s) {
	kprintf("index : %d\n", s.index);
	kprintf("value : %d\n", s.value);
	kprintf("size : %d\n", s.size);
	kprintf("key : %d\n", s.key);
	kprintf("active : %d\n", s.active);
}

PUBLIC int first_free() {
	for (int i = 0; i < SEM_MAX; i++) {
		if (!is_active(i)) {
			kprintf("first free : %d", i);
			return i;
		}
	}
	kprintf("error first_free");
	return -1;
}

