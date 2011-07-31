#ifndef CCSTACK_H_
#define CCSTACK_H_

#include "CCSlist.h"

typedef ccslist_entry_t ccstack_entry_t;
typedef ccslist_t ccstack_t;

#define ccstack_init(stack) ccslist_init(stack)

#define	ccstack_top(stack) ccslist_head(stack)
#define ccstack_size(stack) ccslist_size(stack)
#define ccstack_empty(stack) ccslist_empty(stack)

#define ccstack_alloc(size, data, alloc_func) ccslist_alloc(size, data, alloc_func)
#define ccstack_malloc(size, data) ccstack_alloc(size, data, malloc)

#define ccstack_destroy(data, free_func) ccslist_destroy(data, free_func)
#define ccstack_free(data) ccstack_destroy(free)

#define ccstack_push(stack, data) ccslist_push_head(stack, data)
#define ccstack_remove_head(stack, data) ccslist_remove_head(stack, data)

#define ccstack_pollard(stack, free_func) ccslist_pollard(stack, free_func)
#define ccstack_pop(stack) ccstack_pollard(stack, free)

#define ccstack_release(stack, free_func) ccslist_release(stack, free_func)
#define ccstack_clear(stack) ccstack_release(stack, free)

#endif /* end of include guard: CCSTACK_H_ */
