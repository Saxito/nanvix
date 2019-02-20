#include <sys/sem.h>
#include <nanvix/pm.h> 
#include <nanvix/klib.h>


PUBLIC struct semaphore* tab_sem[SEM_MAX];

PUBLIC void init_tab_sem() {
	for (int i = 0; i < SEM_MAX; i++) {
		tab_sem[i]->value = SEM_MAX+1;
		tab_sem[i]->size = SEM_MAX+1;
	}
}

PUBLIC int get_index(int id) {
	return tab_sem[id]->index;
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

PUBLIC struct semaphore get_sem(int id) {
	kprintf("tab_sem[%d].value = %d", id, tab_sem[id]->value);
	return *tab_sem[id];
}

PUBLIC void set_sem(int id, struct semaphore* sem) {
	tab_sem[id] = sem;
}

PUBLIC unsigned get_key(int id){
	return tab_sem[id]->key;
}

PUBLIC int first_free() {
	for (int i = 0; i < SEM_MAX; i++) {
		if (tab_sem[i]->value == SEM_MAX+1) {
			return i;
		}
	}
	return -1;
}

