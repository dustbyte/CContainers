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
