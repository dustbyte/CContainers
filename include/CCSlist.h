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
** CCSlist.h for project CContainers
**
** Made by mota
** email <mota@souitom.org>
**
** Started on  Fri May 20 03:54:25 2011 mota
** Last update Tue May 31 19:58:44 2011 mota
*/

#ifndef		CCSLIST_H_
# define	CCSLIST_H_

#include <stdlib.h>

/* -- Types */


#define		CCSLIST_ENTRY(entry_type)	\
entry_type	*next

#define		CCSLIST_PROTO(name, entry_type)	\
struct name					\
{						\
  entry_type	*head;				\
  size_t	size;				\
}

#define		CCSLIST_NAME(name)		\
struct name

#define		CCSLIST_CREATE(name)		\
CCSLIST_NAME(name)

/* -- List tools */

#define		CCSLIST_EMPTY(list)	((list)->head == NULL)
#define		CCSLIST_HEAD(list)	(list)->head
#define		CCSLIST_SIZE(list)	(list)->size
#define		CCSLIST_NEXT(entry)	(entry)->next

#define		CCSLIST_LAST(list, tmp)		\
do						\
  {						\
    tmp = NULL;					\
    CCSLIST_FOREACH(list, tmp)			\
      if (tmp->next == NULL)			\
	break;					\
  } while (0)

#define		CCSLIST_INIT(list)		\
do						\
  {						\
    CCSLIST_HEAD(list) = NULL;			\
    CCSLIST_SIZE(list) = 0;			\
  } while (0)

/* -- Loops */

#define		CCSLIST_FOREACH(list, tmp)	\
for ((tmp) = CCSLIST_HEAD(list);		\
     (tmp) != NULL;				\
     (tmp) = CCSLIST_NEXT(tmp))

#define		CCSLIST_FOREACH_SAFE(list, tmp, junk)	\
for ((tmp) = CCSLIST_HEAD(list);			\
     (tmp) != NULL && ((junk) = CCSLIST_NEXT(tmp));	\
     (tmp) = (junk))

/* -- Searching */

/* int (*cmp_func)(entry_type *left, entry_type *right) */
#define		CCSLIST_FIND(list, tmp, ref, cmp_func)	\
do							\
  {							\
    CCSLIST_FOREACH(list, tmp)				\
      {							\
	if (cmp_func(ref, tmp) == 0)			\
	  break;					\
      }							\
  } while (0)

/* int	(*cmp_func)(val_type left, val_type right) */
#define		CCSLIST_FIND_FIELD(list, tmp, val, field, cmp_func)	\
do									\
  {									\
    CCSLIST_FOREACH(list, tmp)						\
      {									\
	if (cmp_func(val, (tmp)->field) == 0)				\
	  break;							\
      }									\
  } while (0)

/* -- Operations */

#define		CCSLIST_REVERSE(list, entry_type)	\
do							\
  {							\
    entry_type			*_tmp;			\
    entry_type			*_next;			\
    entry_type			*_dead = NULL;		\
							\
    CCSLIST_FOREACH_SAFE(list, _tmp, _next)		\
      {							\
        CCSLIST_NEXT(_tmp) = _dead;			\
	(_dead) = (_tmp);				\
      }							\
    CCSLIST_NEXT(_tmp) = (_dead);			\
    CCSLIST_HEAD(list) = (_tmp);			\
  } while (0)

#define		CCSLIST_CONCAT(left_list, right_list, entry_type)	\
{									\
  entry_type	*_tmp;							\
									\
  if (!CCSLIST_EMPTY(right_list))					\
    {									\
      if (!CCSLIST_EMPTY(left_list))					\
	{								\
	  CCSLIST_LAST(left_list, _tmp);				\
 	  CCSLIST_NEXT(_tmp) = CCSLIST_HEAD(right_list);		\
	  CCSLIST_SIZE(left_list) += CCSLIST_SIZE(right_list);		\
	}								\
      else								\
	CCSLIST_REF(right_list, left_list);				\
      CCSLIST_INIT(right_list);						\
    }									\
}

/* --- Copy and reference */

#define		CCSLIST_REF(list, newlist)	\
do						\
  {						\
    CCSLIST_HEAD(newlist) = CCSLIST_HEAD(list);	\
    CCSLIST_SIZE(newlist) = CCSLIST_SIZE(list);	\
  } while (0)

/* void	(*copy_func)(const entry_type * const ref); */
/* void (*delete_func)(entry_type *entry); */
#define		CCSLIST_COPY(list, newlist, entry_type, copy_func, delete_func) \
do									\
  {									\
    entry_type	*_tmp;							\
    entry_type	*_entry;						\
    entry_type	*_dead;							\
									\
    CCSLIST_INIT(newlist);						\
    CCSLIST_FOREACH(list, _tmp)						\
      {									\
	if ((_entry = copy_func(_tmp)) == NULL)				\
	  {								\
	    CCSLIST_CLEAR(newlist, delete_func);			\
	    break;							\
	  }								\
	if (CCSLIST_HEAD(newlist) == NULL)				\
	  CCSLIST_INSERT(newlist, _entry);				\
	else								\
	  CCSLIST_INSERT_AFTER(newlist, _dead, _entry);			\
	_dead = (_entry);						\
      }									\
  } while (0)

/* -- Entry insertion */

#define		CCSLIST_INSERT_AFTER(list, before, entry)	\
do								\
  {								\
    CCSLIST_NEXT(entry) = CCSLIST_NEXT(before);			\
    CCSLIST_NEXT(before) = (entry);				\
    ++CCSLIST_SIZE(list);					\
  } while (0)

#define		CCSLIST_INSERT(list, entry)		\
do							\
  {							\
    CCSLIST_NEXT(entry) = CCSLIST_HEAD(list);		\
    CCSLIST_HEAD(list) = (entry);			\
    ++CCSLIST_SIZE(list);				\
  } while (0)

/* -- Entry deletion */

#define		CCSLIST_POP_HEAD(list, tmp)		\
do							\
  {							\
    (tmp) = CCSLIST_HEAD(list);				\
    CCSLIST_HEAD(list) = CCSLIST_HEAD(list)->next;	\
    --CCSLIST_SIZE(list);				\
  } while (0)

#define		CCSLIST_REMOVE(list, entry, entry_type)	\
do							\
  {							\
    entry_type	*_tmp;					\
							\
    if ((entry) == CCSLIST_HEAD(list))			\
      CCSLIST_REMOVE_HEAD(list, _tmp);			\
    else						\
      {							\
	CCSLIST_FOREACH(list, _tmp)			\
	  if (CCSLIST_NEXT(_tmp) == (entry))		\
	    break;					\
	CCSLIST_NEXT(_tmp) = CCSLIST_NEXT(entry);	\
	--CCSLIST_SIZE(list);				\
      }							\
  } while (0)

/* In C: void	(*free_func)(entry_type *entry) */
/* In C++: void	(*free_func)(void *entry) */
#define		CCSLIST_DESTROY_HEAD(list, free_func)	\
do							\
  {							\
    void	*_tmp;					\
							\
    CCSLIST_POP_HEAD(list, _tmp);			\
    free_func(_tmp);					\
  } while (0)

/* -- List deletion */

#define		CCSLIST_CLEAR(list, free_func)	\
do						\
  {						\
    while (!CCSLIST_EMPTY(list))		\
      {						\
	CCSLIST_DESTROY_HEAD(list, free_func);	\
      }						\
  } while (0)

#define		CCSLIST_FREE(list)		\
CCSLIST_CLEAR(list, free)

#endif		/* !CCSLIST_H */
