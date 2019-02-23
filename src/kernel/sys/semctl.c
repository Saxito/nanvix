#include <nanvix/syscall.h>
#include <sys/sem.h> 

int sys_semctl(int semid, int cmd, int val) {
	switch (cmd) {
		case GETVAL:
			if (is_active(semid)) {
				return get_value(semid);
			} else {
				return -1;
			}
			break;
		case SETVAL:
			if (!is_active(semid)) {
				return -1;
			} else {
				set_size(semid,val);
				return 0;
			}
			break;
		case IPC_RMID:
			if (get_size(semid) == get_value(semid)) {
				set_active(semid, 0);
				return 0;
			}else{ return -1; }
			break;
	}
	return -1;
}