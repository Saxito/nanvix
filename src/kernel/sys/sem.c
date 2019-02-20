#include <sys/sem.h>
#include <nanvix/pm.h>

/*PUBLIC struct semaphore {
	int index;
	int size;
	struct process * waiting;

	int create(int n) {
		index = tab_sem.first_free();
		size = n;
		return index;
	}

	void down() {
		if (size > 0) {
			size --;
		}
		else {
			curr_proc.sleep(waiting->chain,curr_proc->priority);
		}
	}

	void up() {
		if (size == 0) {
			waiting.wakeup(waiting->chain);
		}
		else {
			size ++;
		}
	}

	void destroy() {
		tab_sem[index].size = -1;
	}

};*/

PUBLIC struct semaphore tab_sem[SEM_MAX];

PUBLIC void init_tab_sem() {
	for (int i = 0; i < SEM_MAX; i++) {
		tab_sem[i].size = -1;
	}
}

PUBLIC int get_index(int id) {
	return tab_sem[id].index;
}

PUBLIC int get_size(int id) {
	return tab_sem[id].size;
}

PUBLIC void set_size(int id, int val) {
	tab_sem[id].size = val;
}

PUBLIC int get_value(int id) {
	return tab_sem[id].value;
}

PUBLIC struct semaphore get_sem(int id) {
	return tab_sem[id];
}

PUBLIC void set_sem(int id, struct semaphore sem) {
	tab_sem[id] = sem;
}

PUBLIC int first_free() {
	for (int i = 0; i < SEM_MAX; i++) {
		if (tab_sem[i].size == -1) {
			return i;
		}
	}
	return -1;
}

