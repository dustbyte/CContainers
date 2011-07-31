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
** Made by Mota <mota_AT_DONOTSPAM_souitom.org>
**
*/

#ifndef CCSLIST_H_
#define CCSLIST_H_

#include <stdlib.h>

#include "CContainers/CContainers.h"

typedef struct		_ccslist_entry
{
  struct _ccslist_entry	*next;
}			ccslist_entry_t;

typedef struct 		_ccslist
{
  ccslist_entry_t*	head;
  unsigned int		size;
}			ccslist_t;

#define	ccslist_init(list)			\
  do {						\
	(list)->head = NULL;			\
	(list)->size = 0;			\
  } while (/* CONSTCOND */0)

#define	ccslist_entry(ptr) ((ccslist_entry_t *)ptr - 1)
#define	ccslist_data(ptr) ((CC_CAST *)((ptr) + 1))

#define	ccslist_head_entry(list)	(list)->head
#define	ccslist_head(list)		ccslist_data((list)->head)

#define	ccslist_next_entry(data)	ccslist_entry(data)->next
#define	ccslist_next(data)		ccslist_data(ccslist_next_entry(data))

#define	ccslist_size(list)	(list)->size
#define ccslist_empty(list)	(ccslist_size(list) == 0)

#define	ccslist_foreach(list, tmp)						\
  for ((tmp) = ccslist_size(list) != 0 ? ccslist_head(list) : NULL;	\
	(tmp) != NULL;								\
	(tmp) = (ccslist_next_entry(tmp) != NULL ? ccslist_next(tmp) : NULL))

#define ccslist_foreach_safe(list, dummy, tmp)									\
  for (	(tmp) = ccslist_size(list) != 0 ? ccslist_head(list) : NULL;					\
	(tmp) != NULL && ((dummy) = (ccslist_next_entry(tmp) != NULL ? ccslist_next(tmp) : NULL)) != NULL;	\
	(tmp) = (dummy))

#define ccslist_concat(left, right)					\
  do {									\
	void	*_tail;							\
									\
	ccslist_foreach(left, _tail)					\
	  if (_tail == NULL || ccslist_next_entry(_tail) == NULL)	\
	    break;							\
									\
	if (_tail == NULL)						\
	  *left = *right;						\
	else								\
	  {								\
	    ccslist_next_entry(_tail) = ccslist_head_entry(right);	\
	    ccslist_size(left) += ccslist_size(right);			\
	  }								\
  } while (/* CONSTCOND */0)

#define	ccslist_reverse(list)				\
  do {							\
	ccslist_t	_tmp_list;			\
	void		*_tmp;				\
	\
	ccslist_init(&_tmp_list);			\
	while (!ccslist_empty(list))			\
	  {						\
	    ccslist_remove_head(list, _tmp);		\
	    ccslist_push_head(&_tmp_list, _tmp);	\
	  }						\
	*list = _tmp_list;				\
  } while (/* CONSTCOND */0)

#define	ccslist_sort(list, cmp_func)					\
  do {									\
  	ccslist_entry_t	*_prev = ccslist_head_entry(list);		\
	ccslist_entry_t	*_tmp = _prev;					\
	ccslist_entry_t	*_next;						\
	\
	while (_tmp != NULL && (_next = _tmp->next) != NULL)		\
	  {								\
	    if (cmp_func(ccslist_data(_tmp), ccslist_data(_next)) > 0)	\
	      {								\
		_prev->next = _next;					\
		_tmp->next = _next->next;				\
		_next->next = _tmp;					\
		if (_prev == _tmp)					\
		  ccslist_head_entry(list) = _next;			\
		_prev = ccslist_head_entry(list);			\
		_tmp = _prev;						\
	      }								\
	    else							\
	      {								\
		_prev = _tmp;						\
		_tmp = _next;						\
	      }								\
	  }								\
  } while (/* CONSTCOND */0)

#define ccslist_find(list, cmp_func, data, result)	\
  do {							\
  	ccslist_foreach(list, result)			\
	  if (cmp_func(data, result) == 0)		\
	    break;					\
  } while (/* CONSTCOND */0)

#define	ccslist_alloc(size, data, alloc_func)							\
  do {												\
	ccslist_entry_t	*_ptr = (ccslist_entry_t *)alloc_func(size + sizeof(ccslist_entry_t));	\
												\
	if (_ptr == NULL)									\
	  break;										\
	_ptr->next = NULL;									\
	data = (CC_CAST *) ccslist_data(_ptr);							\
  } while (/* CONSTCOND */0)

#define ccslist_malloc(size, data)	\
  ccslist_alloc(size, data, malloc)

#define	ccslist_destroy(data, free_func)	\
  do {						\
  	free_func(ccslist_entry(data));		\
  } while (/* CONSTCOND */0)

#define	ccslist_free(data)			\
  ccslist_destroy(data, free)			\

#define	ccslist_push_head(list, data)			\
  do {							\
	ccslist_entry_t* entry = ccslist_entry(data);	\
							\
	entry->next = ccslist_head_entry(list);		\
      	ccslist_head_entry(list) = entry;		\
	++ccslist_size(list);				\
  } while (/* CONSTCOND */0)

#define	ccslist_insert_after(list, target, data)		\
  do {								\
	ccslist_entry_t* _target_entry = ccslist_entry(target);	\
	ccslist_entry_t* _new_entry = ccslist_entry(data);	\
								\
	_new_entry->next = _target_entry->next;			\
	_target_entry->next = _new_entry;			\
	++ccslist_size(list);					\
  } while (/* CONSTCOND */0)

#define	ccslist_remove_head(list, ptr)				\
  do {								\
	ccslist_entry_t* entry = ccslist_head_entry(list);	\
	ccslist_head_entry(list) = entry->next;			\
	entry->next = NULL;					\
	ptr = ccslist_data(entry);				\
	--ccslist_size(list);					\
  } while (/* CONSTCOND */0)

#define	ccslist_remove(list, data, ptr)			\
  do {							\
	ccslist_entry_t* entry = ccslist_entry(data);	\
	ccslist_entry_t* rm_entry = entry->next;	\
							\
	entry->next = rm_entry->next;			\
	rm_entry->next = NULL;				\
	ptr = ccslist_data(rm_entry);			\
	--ccslist_size(list);				\
  } while (/* CONSTCOND */0)

#define ccslist_pollard(list, free_func)	\
  do {						\
	void	*_tmp;				\
						\
  	ccslist_remove_head(list, _tmp);	\
	ccslist_destroy(_tmp, free_func);	\
  } while (/* CONSTCOND */0)

#define	ccslist_pop_head(list)	\
  ccslist_pollard(list, free)

#define	ccslist_release(list, free_func)		\
  do {							\
	while (!ccslist_empty(list))			\
	  ccslist_pollard(list, free_func);		\
  } while (/* CONSTCOND */0)

#define ccslist_clear(list)	\
  ccslist_release(list, free)

#endif /* end of include guard: CCSLIST_H_ */
