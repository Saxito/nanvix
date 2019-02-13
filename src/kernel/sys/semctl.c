#include <nanvix/syscall.h>
#include <sys/sem.h>

int sys_semctl(int semid, int cmd, int val) {
	switch (cmd) {
		case 1:
			return tab_sem[semid].index;
			break;
		case 2:
			if (tab_sem[semid].size == -1) {
				return -1;
			} else {
				tab_sem[semid].size = val;
				return 0;
			}
			break;
		case 3:
			if (tab_sem[semid].size == tab_sem[semid].value) {
				tab_sem[semid].size = -1;
				return 0;
			}else{ return -1; }
			break;
	}
	return -1;
}