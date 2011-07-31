#include <stdio.h>

#include "CContainers/CCSlist.h"
#include "unit_test.h"

/* C++ compilable */
#undef CC_CAST
#define CC_CAST int

static int	list_append(ccslist_t *list, int val)
{
  int*		tmp;

  ccslist_malloc(sizeof(*tmp), tmp);
  if (tmp != NULL)
    {
      *tmp = val;
      ccslist_push_head(list, tmp);
      return (1);
    }
  return (0);
}

int		int_cmp(int *left, int *right)
{
  return (*left - *right);
}

int		main()
{
  ccslist_t	list;
  ccslist_t	list2;
  int		i;
  int*		tmp;

  ccslist_init(&list);
  ccslist_init(&list2);

  for (i = 0; i < 10; ++i)
    {
      if (list_append(&list, i) == 0 || list_append(&list2, i) == 0)
	break;
    }

  ccslist_malloc(sizeof(*tmp), tmp);
  if (tmp != NULL)
    {
      *tmp = 42;
      ccslist_insert_after(&list, ccslist_head(&list), tmp);
    }

  ut_log("insert");

  list_append(&list, 20);
  list_append(&list, -1);
  list_append(&list, 23);
  list_append(&list, 13);
  list_append(&list, -4);

  ccslist_foreach(&list, tmp)
    printf("%d\n", *tmp);

  ut_log("reverse and remove");

  ccslist_remove_head(&list, tmp);
  printf("head removed: %d\n", *tmp);
  ccslist_free(tmp);

  ccslist_remove(&list, ccslist_head(&list), tmp);
  printf("entry removed: %d\n", *tmp);
  ccslist_free(tmp);

  ccslist_reverse(&list);
  ccslist_foreach(&list, tmp)
    printf("%d\n", *tmp);

  ut_log("sort");

  ccslist_sort(&list, int_cmp);
  ccslist_foreach(&list, tmp)
    printf("%d\n", *tmp);

  ut_log("concat");

  ccslist_concat(&list, &list2);
  ccslist_init(&list2);
  ccslist_foreach(&list, tmp)
    printf("%d\n", *tmp);

  ut_log("find");

  i = 42;
  ccslist_find(&list, int_cmp, &i, tmp);
  if (tmp != NULL)
    printf("entry found: %d\n", *tmp);

  ccslist_clear(&list);

  return (0);
}
