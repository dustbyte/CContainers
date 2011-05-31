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
** ut_stack.c for project CContainers
**
** Made by mota
** email <mota@souitom.org>
**
** Started on  Mon May 23 01:12:01 2011 mota
** Last update Tue May 31 18:58:13 2011 mota
*/

#include <stdio.h>
#include <stdlib.h>

#include "CCStack.h"

typedef struct s_entry
{
  int		nb;

  CCSTACK_ENTRY(struct s_entry);
} t_entry;

CCSTACK_PROTO(s_stack, t_entry);
typedef struct s_stack t_stack;

/* This is evil, created only for tests */
static void	display_stack(t_stack *stack)
{
  t_entry	*tmp;

  CCSLIST_FOREACH(stack, tmp)
    {
      printf("%d :: %p\n", tmp->nb, (void *)tmp);
    }
}

static void	push_on_stack(t_stack *stack, int i)
{
  t_entry	*nentry = malloc(sizeof(*nentry));

  if (nentry != NULL)
    {
      nentry->nb = i;
      CCSTACK_PUSH(stack, nentry);
    }
}

static t_entry	*copy_entry(const t_entry * const orig)
{
  t_entry	*cpy = malloc(sizeof(*orig));

  if (cpy != NULL)
    cpy->nb = orig->nb;
  return (cpy);
}

static void	ut_step(const char *msg)
{
  printf("\n==%s==\n\n", msg);
}

int		main(void)
{
  t_stack	stack;
  t_stack	cpy;
  t_entry	*tmp;
  size_t	i;

  CCSTACK_INIT(&stack);

  for (i = 0; i < 10; ++i)
    push_on_stack(&stack, i);

  display_stack(&stack);

  ut_step("Poping");

  CCSTACK_POP(&stack, tmp);
  display_stack(&stack);

  ut_step("Pushing");

  CCSTACK_PUSH(&stack, tmp);
  display_stack(&stack);

  ut_step("Copying");

  CCSTACK_COPY(&stack, &cpy, t_entry, copy_entry, free);
  display_stack(&cpy);

  ut_step("Cleaning");
  CCSTACK_FREE(&stack);
  CCSTACK_FREE(&cpy);

  printf("%ld\n\n", CCSTACK_SIZE(&stack));
  return (0);
}
