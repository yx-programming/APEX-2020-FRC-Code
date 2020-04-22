/* Copyright (C) 2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <errno.h>
#include <sysdep.h>
#include <lowlevellock.h>
#include <sys/time.h>
#include <pthreadP.h>


void
 __attribute__ ((visibility ("hidden")))
__lll_pi_lock(int *futexp, int private)
{
  pid_t id = THREAD_GETMEM (THREAD_SELF, tid);
  int newval = id;
  int ret;

  newval |= FUTEX_WAITERS;
  ret = atomic_compare_and_exchange_val_acq (futexp, newval, 0);

  if (ret != 0)
    {
      /* The mutex is locked.  The kernel will now take care of
	 everything.  */
      INTERNAL_SYSCALL_DECL (__err);
      INTERNAL_SYSCALL (futex, __err, 4, futexp,
			__lll_private_flag (FUTEX_LOCK_PI, private), 1, 0);
    }
}


void
__attribute__ ((visibility ("hidden")))
__lll_pi_unlock(int *futexp, int private)
{

  if ((*futexp & FUTEX_WAITERS) != 0
      || atomic_compare_and_exchange_bool_acq (futexp, 0,
					       THREAD_GETMEM (THREAD_SELF,
							      tid)))
    {
      INTERNAL_SYSCALL_DECL (__err);
      INTERNAL_SYSCALL (futex, __err, 2, futexp,
			__lll_private_flag (FUTEX_UNLOCK_PI, private));
    }
}
