/*
 * Copyright(C) 2011-2016 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * This file is part of Nanvix.
 * 
 * Nanvix is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Nanvix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Nanvix. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SEM_H_
#define SEM_H_

	/**
	 * @brief Comand values for semaphores.
	 */
	/**@{*/
	#define SEM_MAX     64
	#define GETVAL		1
	#define SETVAL		0
	#define IPC_RMID	3
	/**@}*/

	/* Forward definitions. */
	extern struct semaphore {
		int index;
		int value;
		int size;
		int key;
		struct process * waiting;
	}semaphore;

	extern void init_tab_sem();
	extern int first_free();
	extern int get_size(int);
	extern int get_index(int);
	extern int get_value(int);
	extern void set_size(int,int);
	extern unsigned get_key(int);
	extern struct semaphore get_sem(int);
	extern void set_sem(int,struct semaphore*);

	extern int semget(unsigned);
	extern int semctl(int, int, int);
	extern int semop(int, int);

#endif /* SEM_H_ */
