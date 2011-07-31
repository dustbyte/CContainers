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

#include <stdio.h>

#include "CContainers/CCList.h"
#include "unit_test.h"

#undef CC_CAST
#define CC_CAST int

static int	list_append(cclist_t *list, int val)
{
  int		*tmp;

  cclist_malloc(sizeof(*tmp), tmp);
  if (tmp != NULL)
    {
      *tmp = val;
      cclist_push_head(list, tmp);
      return (1);
    }
  return (0);
}

int		main()
{
  cclist_t	list;
  int		*tmp;
  int		i;

  cclist_init(&list);

  for (i = 0; i < 10; ++i)
    if (list_append(&list, i) == 0)
      break;

  cclist_foreach(&list, tmp)
    printf("%d\n", *tmp);

  cclist_clear(&list);

  return (0);
}
