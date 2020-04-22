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

#include <errno.h>
#include <pthreadP.h>


int
pthread_condattr_setprotocol_np (pthread_condattr_t *attr, int protocol)
{
  if (protocol != PTHREAD_PRIO_NONE
      && protocol != PTHREAD_PRIO_INHERIT
      && __builtin_expect (protocol != PTHREAD_PRIO_PROTECT, 0))
    return EINVAL;

  int *valuep = &((struct pthread_condattr *) attr)->value;

  *valuep = ((*valuep & ~CONDATTR_PROTOCOL_MASK)
	     | (protocol << CONDATTR_PROTOCOL_SHIFT));

  return 0;
}
