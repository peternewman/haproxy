/*
  include/types/task.h
  Macros, variables and structures for task management.

  Copyright (C) 2000-2007 Willy Tarreau - w@1wt.eu
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, version 2.1
  exclusively.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _TYPES_TASK_H
#define _TYPES_TASK_H

#include <sys/time.h>

#include <common/config.h>
#include <common/mini-clist.h>
#include <import/tree.h>

/* values for task->state */
#define TASK_IDLE	0
#define TASK_RUNNING	1

/* The base for all tasks */
struct task {
	struct list qlist;              /* chaining in the same queue; bidirectionnal but not circular */
	struct ultree *wq;		/* NULL if unqueued, or back ref to the carrier node in the WQ */
	int state;			/* task state : IDLE or RUNNING */
	struct timeval expire;		/* next expiration time for this task, use only for fast sorting */
	void (*process)(struct task *t, struct timeval *next);	/* the function which processes the task */
	void *context;			/* the task's context */
};

#define sizeof_task     sizeof(struct task)
extern void **pool_task;

#endif /* _TYPES_TASK_H */

/*
 * Local variables:
 *  c-indent-level: 8
 *  c-basic-offset: 8
 * End:
 */
