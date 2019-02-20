#include <nanvix/syscall.h>
#include <sys/sem.h>

int sys_semctl(int semid, int cmd, int val) {
	switch (cmd) {
		case 1:
			return get_index(semid);
			break;
		case 2:
			if (get_size(semid) == -1) {
				return -1;
			} else {
				set_size(semid,val);
				return 0;
			}
			break;
		case 3:
			if (get_size(semid) == get_value(semid)) {
				set_size(semid,-1);
				return 0;
			}else{ return -1; }
			break;
	}
	return -1;
}