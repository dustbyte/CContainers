#ifndef CCLIST_H_
#define CCLIST_H_

#include <stdlib.h>

#include "CContainers/CContainers.h"

typedef struct 		_cclist_entry
{
  struct _cclist_entry	*prev;
  struct _cclist_entry	*next;
}			cclist_entry_t;

typedef struct		_cclist
{
  cclist_entry_t	*head;
  cclist_entry_t	*tail;
  unsigned int		size;
}			cclist_t;

#define cclist_init(list)			\
  do {						\
  	(list)->head = NULL;			\
	(list)->tail = NULL;			\
	(list)->size = 0;			\
  } while (/* CONSTCOND */0)

#define cclist_entry(ptr) ((cclist_entry_t *)ptr - 1)
#define cclist_data(ptr) ((CC_CAST *)((ptr) + 1))

#define cclist_head_entry(list) (list)->head
#define cclist_head(list) cclist_data(cclist_head_entry(list))

#define cclist_tail_entry(list) (list)->tail
#define cclist_tail(list) cclist_data(cclist_tail_entry(list))

#define cclist_next_entry(data) cclist_entry(data)->next
#define cclist_next(data) cclist_data(cclist_next_entry(data))

#define cclist_prev_entry(data) cclist_entry(data)->prev
#define cclist_prev(data) cclist_data(cclist_prev_entry(data))

#define cclist_size(list) (list)->size
#define cclist_empty(list) (cclist_size(list) == 0)

#define cclist_foreach(list, tmp)						\
  for ((tmp) = cclist_size(list) != 0 ? cclist_head(list) : NULL;		\
	(tmp) != NULL;								\
	(tmp) = (cclist_next_entry(tmp) != NULL ? cclist_next(tmp) : NULL))

#define cclist_foreach_safe(list, dummy, tmp)									\
  for (	(tmp) = cclist_size(list) != 0 ? cclist_head(list) : NULL;						\
	(tmp) != NULL && ((dummy) = (cclist_next_entry(tmp) != NULL ? cclist_next(tmp) : NULL)) != NULL;	\
	(tmp) = (dummy))

#define cclist_alloc(size, data, alloc_func)						\
  do {											\
  	cclist_entry_t *_ptr = (cclist_entry_t *)alloc_func(size + sizeof(*_ptr)); 	\
											\
	if (_ptr == NULL)								\
	  break;									\
	_ptr->next = NULL;								\
	_ptr->prev = NULL;								\
	data = (CC_CAST *) cclist_data(_ptr);						\
  } while (/* CONSTCOND */0)

#define cclist_malloc(size, data)		\
  cclist_alloc(size, data, malloc)

#define cclist_destroy(data, free_func)		\
  do {						\
  	free_func(cclist_entry(data));		\
  } while (/* CONSTCOND */0)

#define cclist_free(data)			\
  cclist_destroy(data, free)

#define cclist_push_head(list, data)			\
  do {							\
	cclist_entry_t *_tmp = cclist_entry(data);	\
							\
	_tmp->next = cclist_head_entry(list);		\
	_tmp->prev = NULL;				\
	if (!cclist_empty(list))			\
	  cclist_head_entry(list)->prev = _tmp;		\
	else						\
	  cclist_tail_entry(list) = _tmp;		\
	cclist_head_entry(list) = _tmp;			\
	++cclist_size(list);				\
  } while (/* CONSTCOND */0)

#define cclist_push_tail(list, data)			\
  do {							\
  	cclist_entry_t *_tmp = cclist_entry(data);	\
							\
	_tmp->prev = cclist_tail_entry(list);		\
	_tmp->next = NULL;				\
	if (!cclist_empty(list))			\
	  cclist_tail_entry(list)->next = _tmp;		\
	else						\
	  cclist_head_entry(list) = _tmp;		\
	cclist_tail_entry(list) = _tmp;			\
	++cclist_size(list);				\
  } while (/* CONSTCOND */0)

#define cclist_insert_before(list, target, data)	\
  do {							\
  	cclist_entry_t	*_target_entry;			\
	cclist_entry_t	*_new_entry;			\
							\
	if (target == cclist_head(list))		\
	  cclist_push_head(list, data);			\
	else						\
	  {						\
	    _target_entry = cclist_entry(target);	\
	    _new_entry = cclist_entry(data);		\
	    _target_entry->prev->next = _new_entry;	\
	    _new_entry->prev = _target_entry->prev;	\
	    _target_entry->prev = _new_entry;		\
	    _new_entry->next = _target_entry;		\
	    ++cclist_size(list);			\
	  }						\
  } while (/* CONSTCOND */0)

#define cclist_insert_after(list, target, data)		\
  do {							\
  	cclist_entry_t	*_target_entry;			\
	cclist_entry_t	*_new_entry;			\
							\
	if (target == cclist_tail(list))		\
	  cclist_push_tail(list, data);			\
	else						\
	  {						\
	    _target_entry = cclist_entry(target);	\
	    _new_entry = cclist_entry(data);		\
	    _target_entry->next->prev = _new_entry;	\
	    _new_entry->next = _target_entry->next;	\
	    _target_entry->next = _new_entry;		\
	    _new_entry->prev = _target_entry;		\
	    ++cclist_size(list);			\
	  }						\
  } while (/* CONSTCOND */0)

#define cclist_remove_head(list, ptr)				\
  do {								\
	cclist_entry_t *_tmp = cclist_head_entry(list);		\
								\
	if (_tmp->next != NULL)					\
	  _tmp->next->prev = NULL;				\
	(ptr) = cclist_data(_tmp);				\
	cclist_head_entry(list) = _tmp->next;			\
	--cclist_size(list);					\
  } while (/* CONSTCOND */0)

#define cclist_remove_tail(list, ptr)				\
  do {								\
  	cclist_entry_t	*_tmp = cclist_tail_entry(list);	\
								\
	if (_tmp->prev != NULL)					\
	  _tmp->prev->next = NULL;				\
	(ptr) = cclist_data(_tmp);				\
	cclist_tail_entry(list) = _tmp->prev;			\
	--cclist_size(list);					\
  } while (/* CONSTCOND */0)

#define cclist_remove(list, data)		\
  do {						\
  	cclist_entry_t	*entry;			\
						\
	if (data == cclist_head(list))		\
	  cclist_remove_head(list, data);	\
	else if (data == cclist_tail(list))	\
	  cclist_remove_tail(list, data);	\
	else					\
	  {					\
	    entry = cclist_entry(data);		\
						\
	    if (entry->prev != NULL)		\
	      entry->prev->next = entry->next;	\
	    if (entry->next != NULL)		\
	      entry->next->prev = entry->prev;	\
	    entry->next = NULL;			\
	    entry->prev = NULL;			\
	    --cclist_size(list);		\
	  }					\
  } while (/* CONSTCOND */0)

#define cclist_pollard(list, free_func)		\
  do {						\
  	void	*_ptr = NULL;			\
						\
	cclist_remove_head(list, _ptr);		\
	cclist_destroy(_ptr, free_func);	\
  } while (/* CONSTCOND */0)

#define cclist_pop_head(list)			\
  cclist_pollard(list, free)

#define cclist_hull(list, free_func)		\
  do {						\
	void	*_ptr;				\
						\
  	cclist_remove_tail(list, _ptr)		\
	cclist_destroy(_ptr, free_func)		\
  } while (/* CONSTCOND */0)

#define cclist_pop_tail(list)			\
  cclist_hull(list, free)

#define cclist_release(list, free_func)		\
  do {						\
  	while (!cclist_empty(list))		\
	  cclist_pollard(list, free_func);	\
  } while (/* CONSTCOND */0)

#define cclist_clear(list)			\
  cclist_release(list, free)

#endif /* end of include guard: CCLIST_H_ */
