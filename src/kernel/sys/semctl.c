#include <nanvix/syscall.h>
#include <sys/sem.h> 
#include <nanvix/klib.h>

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
				set_desactive(semid);
				return 0;
			break;
	}
	return -1;
}