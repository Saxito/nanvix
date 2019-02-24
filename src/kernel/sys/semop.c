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


int sys_semop(int semid, int op){
	if (is_active(semid)) {
		if (op < 0){
			down(semid);
		}else {
			up(semid);
		}
		return 0;
	} else {
		return -1;
	}
}