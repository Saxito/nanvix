#include <nanvix/syscall.h>
#include <sys/sem.h>
#include <nanvix/pm.h>
#include <nanvix/klib.h>

/*
La fonction semop permet d’effectuer des opérations atomiques incrémentant
ou décrémentant la variable associée au sémaphore identifié par semid.
Une valeur négative pour op spécifie l’opération downw () et une valeur
positive l’opération up ().
La fonction retourne 0 en cas de réussite, ou −1 en cas d’erreur.
*/

void down(struct semaphore s) {
	if (s.size > 0) {
		s.size --;
	}else {
		sleep(s.waiting->chain, curr_proc->priority);
	}
}

void up(struct semaphore s) {
	if (s.size == 0) {
		wakeup(s.waiting->chain);
	}else {
		s.size ++;
	}
}

int sys_semop(int semid, int op){
	kprintf("debut semop");
	struct semaphore s;
	int find = 0;
	kprintf("debut get-sem");
	s = get_sem(semid);
	kprintf("fin get sem");

	if (find != 0){
		kprintf("find");
		if (op < 0){
			down(s);
		}else {
			up(s);
		}
		kprintf("end find");
	}else{
		return -1;
	}

	kprintf("final end");
	return 0;
}