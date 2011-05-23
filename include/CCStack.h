/*
** Copyright(c), CContainers
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
** CCStack.h for project CContainers
**
** Made by mota
** email <mota@souitom.org>
**
** Started on  Mon May 23 00:47:14 2011 mota
** Last update Mon May 23 03:37:49 2011 mota
*/

#ifndef		CCSTACK_H_
# define	CCSTACK_H_

#include "CCSlist.h"

#define		CCSTACK_ENTRY(entry_type)	\
CCSLIST_ENTRY(entry_type)

#define		CCSTACK_PROTO(name, entry_type)	\
CCSLIST_PROTO(name, entry_type)

#define		CCSTACK_NAME(name)		\
CCSLIST_NAME(name)

#define		CCSTACK_CREATE(name)		\
CCSTACK_NAME(name)

#define		CCSTACK_EMPTY(stack)	CCSLIST_EMPTY(stack)
#define		CCSTACK_TOP(stack)	CCSLIST_HEAD(stack)
#define		CCSTACK_SIZE(stack)	CCSLIST_SIZE(stack)

#define		CCSTACK_INIT(stack)		\
CCSLIST_INIT(stack)

#define		CCSTACK_REF(stack, newstack)	\
CCSLIST_REF(stack, newstack)

#define		CCSTACK_PUSH(stack, entry)	\
CCSLIST_INSERT(stack, entry)

#define		CCSTACK_POP(stack, tmp)		\
CCSLIST_POP_HEAD(stack, tmp)

#define		CCSTACK_COPY(stack, newstack, entry_type, copy_func, delete_func) \
CCSLIST_COPY(stack, newstack, entry_type, copy_func, delete_func)

#define		CCSTACK_CLEAR(stack, free_func)	\
CCSLIST_CLEAR(stack, free_func)

#define		CCSTACK_FREE(stack)		\
CCSTACK_CLEAR(stack, free)

#endif		/* !CCSTACK */
