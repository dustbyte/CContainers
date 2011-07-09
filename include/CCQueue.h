/*
** Copyright(c), Pierre ``Mota'' Wacrenier
** All rights reserved.
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of the University of California, Berkeley nor the
**       names of its contributors may be used to endorse or promote products
**       derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
** EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
** DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
** ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
** CCQueue.h for project CContainers
**
** Made by mota
** email <mota@souitom.org>
**
** Started on  Sat Jul  9 23:30:51 2011 mota
** Last update Sat Jul  9 23:30:52 2011 mota
*/

#ifndef		CCQUEUE_H_
# define	CCQUEUE_H_

#include "CCList.h"

#define		CCQUEUE_ENTRY(entry_type)	\
CCLIST_ENTRY(entry_type)

#define		CCQUEUE_PROTO(name, entry_type)	\
CCLIST_PROTO(name, entry_type)

#define		CCQUEUE_NAME(name)		\
CCLIST_NAME()

#define		CCQUEUE_CREATE(name)		\
CCLIST_CREATE(name)

#define		CCQUEUE_EMTPY(queue)	CCLIST_EMPTY(queue)
#define		CCQUEUE_HEAD(queue)	CCLIST_HEAD(queue)
#define		CCQUEUE_TAIL(queue)	CCLIST_TAIL(queue)
#define		CCQUEUE_SIZE(queue)	CCLIST_SIZE(queue)

#define		CCQUEUE_INIT(queue)	CCLIST_INIT(queue)

#define		CCQUEUE_PUSH(queue, entry)	\
CCLIST_PUSH_FRONT(queue, entry)

#define		CCQUEUE_POP(queue, var)		\
CCLIST_POP_BACK(queue, var)

#define		CCQUEUE_REF(queue, newqueue)	\
CCLIST_REF(queue, newqueue)

/* void	(*copy_func)(const entry_type * const ref); */
/* void (*delete_func)(entry_type *entry); */
#define		CCQUEUE_COPY(queue, newqueue, entry_type, copy_func, delete_func) \
CCLIST_COPY(queue, newqueue, entry_type, copy_func, delete_func)

#define		CCQUEUE_CLEAR(queue, free_func)	\
CCLIST_CLEAR(queue, free_func)

#define		CCQUEUE_FREE(queue)		\
CCQUEUE_CLEAR(queue, free)

#endif		/* !CCQUEUE */
