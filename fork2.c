/*
 * fork() EXAMPLE 2:    THE PROCESS GROUP OF A PARENT, CHILD AND GRANDCHILD
 * getpid(): returns your own PID
 * getppid(): returns the PID of your parent
 * getpgrp(somepid): returns the process group of the designated process
 */

#include <stdio.h>

main()
{
   int i, kidpid, grandpid;

   /* do the fork, remember the value returned by fork(), and test it */
   if (-1 == (kidpid = fork())) {
      /* -1 indicates the fork was unsuccessful */
      perror("Cannot fork");
      exit(1);
   } else if (0 == kidpid) {
      /* fork() returns 0 to the newly-created child process */
      printf("child says: my process group = %d, ", getpgrp(getpid()));
      printf("my pid = %d, parent pid = %d\n", getpid(), getppid());
      if (-1 == (grandpid = fork())) {
         /* -1 indicates this second fork was unsuccessful */
         perror("Cannot fork");
         exit(1);
      } else if (0 == grandpid) {
         /* another fork() returns 0 to another newly-created child process */
         for (i = 0; ++i < 9; ) {
           printf("grandchild says: my process group = %d, ",getpgrp(getpid()));
           printf("my pid = %d, parent pid = %d\n", getpid(), getppid());
           sleep(1);
         }
         exit(0);
      } else { /* this is the process that forked the grandchild (Why?) */
         for (i = 0; ++i < 5; ) {
           printf("child says: my process group = %d, ", getpgrp(getpid()));
           printf("my pid = %d, parent pid = %d\n", getpid(), getppid());
           sleep(1);
         }
         exit(0);
      }
   } else {
      /* fork() returns a positive number to the process issuing the (first)
       * fork(). The number it returns is the PID of the child process */
      printf("parent says: my process group = %d, ", getpgrp(getpid()));
      printf("my pid = %d, parent pid = %d\n", getpid(), getppid());
      sleep(2);
      exit(0);
   }
}

/* Do all three processes have the same process group number?
 * Does the process group number match one of the pids?  Which one?
 * Which of the three processes usually finishes first?
 * What process becomes the parent of an orphan?
 * Which death causes the shell to issue another prompt?
 */
