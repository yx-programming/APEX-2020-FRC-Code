/* Copyright (C) 2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _COND_LOCK_H
#define _COND_LOCK_H 1

extern void __lll_pi_lock (int *futex, int private) attribute_hidden;
extern void __lll_pi_unlock (int *futex, int private) attribute_hidden;

#define lll_pi_lock(futex, private) __lll_pi_lock (&(futex), private)
#define lll_pi_unlock(futex, private) __lll_pi_unlock (&(futex), private)

static inline void
cond_lock(pthread_cond_t *cond, int pshared)
{
  if (pshared == LLL_PRIVATE &&
      (((cond->__data.__nwaiters & COND_PROTOCOL_MASK) >> COND_PROTOCOL_SHIFT)
       == COND_PRIO_INHERIT))
    lll_pi_lock (cond->__data.__lock, pshared);
  else
    lll_lock (cond->__data.__lock, pshared);
}

static inline void
cond_unlock(pthread_cond_t *cond, int pshared)
{
  if (pshared == LLL_PRIVATE &&
      (((cond->__data.__nwaiters & COND_PROTOCOL_MASK) >> COND_PROTOCOL_SHIFT)
       == COND_PRIO_INHERIT))
    lll_pi_unlock (cond->__data.__lock, pshared);
  else
    lll_unlock (cond->__data.__lock, pshared);
}

#endif
