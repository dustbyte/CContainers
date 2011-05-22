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
** ut_slist.c for project CContainers
**
** Made by mota
** email <mota@souitom.org>
**
** Started on  Sun May 22 22:42:54 2011 mota
** Last update Mon May 23 00:40:16 2011 mota
*/

#include <stdio.h>
#include <stdlib.h>

#include "CCSlist.h"

typedef struct s_entry t_entry;

struct s_entry
{
  int		nb;

  CCSLIST_ENTRY(t_entry);
};

CCSLIST_PROTO(s_slist, t_entry);
typedef struct s_slist t_slist;

static void	insert_entry(t_slist *slist, int val)
{
  t_entry	*nentry = malloc(sizeof(*nentry));

  if (nentry != NULL)
    {
      nentry->nb = val;
      CCSLIST_INSERT(slist, nentry);
    }
}

static int	cmp_entry(t_entry *left, t_entry *right)
{
  return (right->nb - left->nb);
}

static int	cmp_val(int left_val, int right_val)
{
  return (right_val - left_val);
}

static void	display_entry(t_entry *entry)
{
  printf("%d :: %p\n", entry->nb, (void *)entry);
}

static void	copy_entry(const t_entry * const orig, t_entry *copy)
{
  copy->nb = orig->nb;
}

static void	ut_step(const char *msg)
{
  printf("\n==%s==\n\n", msg);
}

int		main()
{
  t_slist	slist;
  t_slist	cpy;
  t_entry	*tmp;
  t_entry	ref = {5, NULL};
  size_t	i;

  CCSLIST_INIT(&slist);

  ut_step("Creation");

  for (i = 0; i < 10; ++i)
    insert_entry(&slist, i);

  ut_step("Iteration");

  CCSLIST_FOREACH(&slist, tmp)
    {
      display_entry(tmp);
    }

  if ((tmp = malloc(sizeof(*tmp))) != NULL)
    {
      ut_step("Insertion");
      tmp->nb = i + 1;
      CCSLIST_INSERT_AFTER(&slist, CCSLIST_HEAD(&slist), tmp);

      CCSLIST_FOREACH(&slist, tmp)
	{
	  display_entry(tmp);
	}
    }

  ut_step("Search");

  CCSLIST_FIND(&slist, tmp, &ref, cmp_entry);
  if (tmp != NULL)
    display_entry(tmp);

  ut_step("Search with field");

  CCSLIST_FIND_FIELD(&slist, tmp, 2, nb, cmp_val);
  if (tmp != NULL)
    display_entry(tmp);

  ut_step("Copy");

  CCSLIST_COPY(&slist, &cpy, t_entry, copy_entry, free);

  CCSLIST_FOREACH(&cpy, tmp)
    {
      display_entry(tmp);
    }

  ut_step("Reversion");

  CCSLIST_REVERSE(&cpy, t_entry);

  CCSLIST_FOREACH(&cpy, tmp)
    {
      display_entry(tmp);
    }

  ut_step("Destruction");

  CCSLIST_FREE(&slist);
  CCSLIST_FREE(&cpy);
  return (0);
}
