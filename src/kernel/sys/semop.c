#include <nanvix/syscall.h>
#include <nanvix/sem.c>


/*
La fonction semop permet d’effectuer des opérations atomiques incrémentant
ou décrémentant la variable associée au sémaphore identifié par semid.
Une valeur négative pour op spécifie l’opération downw () et une valeur
positive l’opération up ().
La fonction retourne 0 en cas de réussite, ou −1 en cas d’erreur.
*/

int sys_semop(int semid, int op){
	semaphore s;
	int find = 0;
	for(int i = 0 ; i < SEM_MAX && find == 0; i++){
		s = tab_sem[i];
		if(s->index == semid){
			find = 1;
		}
	}
	if (find != 0){
		if (op < 0){
			down(s);
		}else {
			up(s);
		}
	}else{
		return -1;
	}
}

void down(semaphore s) {
	if (s->size > 0) {
		s->size --;
	}
	else {
		curr_proc.sleep(waiting->chain,curr_proc->priority);
	}
}

void up(semaphore s) {
	if (s->size == 0) {
		waiting.wakeup(waiting->chain);
	}
	else {
		s->size ++;
	}
}