/*
pipe() EXAMPLE: USING A PIPELINE TO FACILITATE PROCESS COMMUNICATION

Illustrates pipefitting that simulates:
              sort pipe.c | tr A-Za-z a-zA-Z
('pipe.c' is hardwired into this program, so if ./pipe.c does not exist, the
sort command will fail, and send no output to tr)

This may be compiled with
gcc -g -O -Wall -Wpointer-arith -Wcast-qual -Wwrite-strings \
  -Wstrict-prototypes -Wmissing-prototypes -Wnested-externs \
  pipe.c -o pipe

or, to see what can go wrong, compile it with the file close step omitted:
gcc -g -O -Wall -Wpointer-arith -Wcast-qual -Wwrite-strings \
  -Wstrict-prototypes -Wmissing-prototypes -Wnested-externs \
  -DPROBLEM \
  pipe.c -o pipe

(If the parent does not close its access to the pipe then the child would never
see EOF on stdin and would not terminate until the shell interpreter terminated)

or, to see how the CHK() macro catches failed calls, compile it with the name
of one of the binaries misspelled:
gcc -g -O -Wall -Wpointer-arith -Wcast-qual -Wwrite-strings \
  -Wstrict-prototypes -Wmissing-prototypes -Wnested-externs \
  -DSPELLING \
  pipe.c -o pipe

Note that
#include "CHK.h"
...means that the file CHK.h must be in the current directory.
#include "/home/ma/cs570/CHK.h"
...would instead follow an absolute path rather than the relative path.
#include <CHK.h>
...would instead look for /usr/include/CHK.h [and fail to find it].

*/

#include <unistd.h>
#include <stdlib.h>
#include "CHK.h"
#include <sys/types.h>  /* added for wait call */
#include <sys/wait.h>   /* added for wait call */

int main(void) {
   int fildes[2];
   pid_t first, second;

   CHK(pipe(fildes));

   CHK(first = fork());
   if (0 == first) {
      /* first of two child processes */
      CHK(dup2(fildes[1],STDOUT_FILENO));
      CHK(close(fildes[0]));
      CHK(close(fildes[1]));
#ifndef SPELLING
      CHK(execlp("sort","sort","pipe.c",NULL));
#else
      CHK(execlp("srot","sort","pipe.c",NULL));
#endif
      /* no return! */
   }  /* the first child's code ends with the execlp() */

/* running "gcc -E -DSPELLING pipe.c" shows that CHK in the above line expands to:

do {if((execlp("srot","sort","pipe.c",0)) == -1) {fprintf((&__iob[2]),"In file %s, o
n line %d:\n","pipe.c",61); fprintf((&__iob[2]),"errno = %d\n",errno); perror("Exiti
ng because"); exit(1); } } while(0);

...which results in perror() being called when "srot" cannot be found.
You can misspell the second argument to execlp() without any ill effects;
the second argument is ignored!  */

   CHK(second = fork());
   if (second == 0) {
      /* for second of two child processes */
      CHK(dup2(fildes[0],STDIN_FILENO));
      CHK(close(fildes[0]));
      CHK(close(fildes[1]));
      CHK(execlp("tr","tr","A-Za-z","a-zA-Z",NULL));
      /* no return! */
   }  /* the second child's code ends with the execlp() */

/* only the parent reaches this point in the code. */

#ifndef PROBLEM
   CHK(close(fildes[0]));
   CHK(close(fildes[1]));
#endif

   /* wait() might find the first child; continue reaping children until
      the second child is found */
   for (;;) {
     pid_t pid;
     CHK(pid = wait(NULL));
     if (pid == second) {
       break;
     }
   }
   /* parent says: */
   printf("Parent is Done!\n");
   exit(EXIT_SUCCESS);
}

/* The parent created a pipe prior to any fork, so the parent has open
 * file descriptors for the pipe.  Each child starts as a clone of the parent,
 * so both children also have the pipe file descriptors open.  Hence, all
 * three processes are capable of writing into the pipe.  If a process tries
 * to read from the pipe, the pipe will only indicate EOF if there are no
 * longer ANY processes capable of writing into the pipe.  That is why
 * close(fildes[1])
 * had to occur in THREE separate places in the above code, or else the
 * second child ("tr") will never see EOF, and will therefore never terminate.
 * 
 * Actually, due to the dup2() of fildes[1] in the first child, there is
 * in fact not just three but FOUR avenues for writing into the pipe.
 * After closing three of them, only the stdout file descriptor of "sort"
 * is still capable of writing into the pipe.  This very last file descriptor
 * will close once "sort" exits, at which point "tr" will receive EOF, and
 * then "tr" will finish reading, do the actual case-inversion, and exit.
 * 
 * Note that the parent blocks until "tr" finishes.
 * Can you identify the race condition caused by -DPROBLEM?
 * (That is, who is waiting for whom [and for what] in a circular wait?)
 */
