#include <nanvix/syscall.h>
#include <sys/sem.h> 
#include <nanvix/klib.h>

int sys_semctl(int semid, int cmd, int val) {
	switch (cmd) {
		case GETVAL:
			kprintf("%d",get_index(semid));
			return get_index(semid);
			break;
		case SETVAL:

			if (get_value(semid) == SEM_MAX + 1) {
				return -1;
			} else {
				set_size(semid,val);
				return 0;
			}
			break;
		case IPC_RMID:
			if (get_size(semid) == get_value(semid)) {
				set_size(semid,-1);
				return 0;
			}else{ return -1; }
			break;
	}
	return -1;
}