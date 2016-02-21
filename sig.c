/*
 * SIGNAL EXAMPLE 1:    SIGTSTP and SIGCONT
 */

#include <stdio.h>
#include <signal.h>

// #define OMIT

/* Because of the '//' above, the #define statement is not seen by the
 * preprocessor; consequently, the #ifndef ["IF Not DEFined"] statement
 * below is true, and all four printf() statements are compiled.
 * If the '//' above is removed, then OMIT will be defined, and only the
 * first and last printf() statements will be compiled into the a.out file.
 * [Note that this is not a run-time directive that gets tested when the
 * process executes; the middle printf() statements are never even seen
 * by the C compiler (because cpp, the C preprocessor, strips them out).]
 *
 * If you need to debug your C programs, by far the best way is to use
 * a debugger (like dbx).  If you insist on littering your program with
 * printf() statements instead, then at least use this #ifndef/#endif trick.
 * That way, you don't have to keep adding and removing multiple iterations
 * of debugging code -- just #define them away when you are finished debugging.
 */

main()
{
int pid = getpid();

printf("This is PID %d sending a stop signal to itself...\n", pid );

#ifndef OMIT
printf("A shell must do 'kill -CONT %d' to make it resume...\n", pid );
printf("Or some other process must execute 'kill(%d, SIGCONT);'\n", pid );
#endif

kill(pid, SIGTSTP);
printf("PID %d says: Someone must have sent SIGCONT to me!\n", pid);
exit(3);
}

/* Sample interaction and output:

rohan[247]% a.out
This is PID 10981 sending a stop signal to itself...
A shell must do 'kill -CONT 10981' to make it resume...
Or some other process must execute 'kill(10981, SIGCONT);'
Suspended
rohan[248]% kill -CONT 10981
PID 10981 says: Someone must have sent SIGCONT to me!
rohan[249]% 
[1]    Exit 3                        a.out
 */
