/*
 * fork() EXAMPLE 1:    A PARENT CREATES A CHILD
 */

/* These examples will be discussed in class, and as such,
 * they are poorly documented here.  
 */

#include <stdio.h>

main()
{
   int kidpid;

   /* do the fork, remember the value returned by fork(), and test it */
   if (-1 == (kidpid = fork())) { 
      /* -1 indicates the fork was unsuccessful */
      perror("Cannot fork");
      exit(1);
   } else if (0 == kidpid) {
      /* fork() returns 0 to the newly-created child process */
      sleep(1);
      /* block for 1 second, to ensure a context switch for this example */
      printf("child says: my pid = %d, parent pid = %d\n", getpid(), getppid());
      exit(0);
   } else {
/* fork() returns a positive number to the process that issued the fork()
 * The number it returns is the PID of the child process that was just created */
      sleep(1);
      /* block for 1 second, to ensure a context switch for this example */
      printf("parent says: child pid = %d, my pid = %d\n", kidpid, getpid());
      exit(0);
   }
}

/* Trick question: which process (parent or child) executes its printf()
 * statement first?  Run the program enough times to confirm your answer,
 * and make sure you understand the behavior you observe.
 *
 * NOTE: the sleep() commands above are NOT needed, but are only there to
 * make the variable behavior more readily observable.
 */
