#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  printf(1, "[test 1] :: Attempting to change ticket value to 20\n");
  int test = settickets(20);
  if (test != 0) {
      printf(1, "[test 1] :: Failed to set tickets\n");
  } else {
      printf(1, "[test 1] :: Successfully set tickets\n");
  }

  printf(1, "[test 2] :: Attempting to set  negative ticket value\n");
  test = settickets(-10);
  if (test != 0) {
      printf(1, "[test 2] :: Received proper error code\n");
  } else {
      printf(1, "[test 2] :: Failed to receive proper error code\n");
  }

  printf(1, "[test 3] :: Attempting to set ticket value that is not divisible by 10\n");
  test = settickets(15);
  if (test != 0) {
      printf(1, "[test 3] :: Received proper error code\n");
  } else {
      printf(1, "[test 3] :: Failed to receive proper error code\n");
  }

  printf(1, "[test 4] :: Attempting to set ticket value greater than 200\n");
  test = settickets(210);
  if (test != 0) {
      printf(1, "[test 4] :: Received proper error code\n");
  } else {
      printf(1, "[test 4] :: Failed to receive proper error code\n");
  }

  exit();
  return 0;
}
