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
