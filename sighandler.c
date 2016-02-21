/*
 * from http://airtower.wordpress.com/2010/06/16/catch-sigterm-exit-gracefully/
 * if you run this program in the background (with '&'), your shell will report
 * the PID of the process.  You can then use the reported PID number to send
 * this program the SIGTERM signal, via:
 * kill -TERM <PID>  or  kill -15 <PID>
 * By default, your program abruptly terminates upon receiving SIGTERM...
 * but you can CATCH the signal and instead do something other than the default,
 * by using signal() to install your own signal handler (called 'myhandler'
 * below).  All signals (except for SIGKILL and SIGSTOP, which can't be caught)
 * can be ignored or replaced by your own customized handler.
 * A fork()ed process [being an exact copy] will likewise use the customized 
 * handler of the parent, but an exec() will reset the handler to the default
 * [because branching to the entry point of a handler that has been blown away
 * by exec() makes no sense at all...
 * man -s 3c sleep    states that:          The actual suspension
 *   time may be less than that requested because any caught sig-
 *   nal  will  terminate the sleep() following execution of that
 *   signal's catching routine.
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
 
int complete = 0;
 
void myhandler(int signum)
{
    printf("Received SIGTERM, and the special handler is running...\n");
    complete = 1;
}
 
int main(int argc, char *argv[])
{
    signal(SIGTERM, myhandler);
    int loop = 0;
    int unslept;
 
    while (!complete) {
        unslept = sleep(30);
        printf("Finished loop run %d. Unslept amount is %d\n", loop++, unslept);
    }
 
    printf("Something has set 'complete' to TRUE...\n");
    return 0;
}

/* Sample [edited] output:
rohan[249]% a.out &
[1] 3656
Finished loop run 0. Unslept amount is 0
Finished loop run 1. Unslept amount is 0
rohan[250]% kill -15 3656    
Received SIGTERM, and the special handler is running...
Finished loop run 2. Unslept amount is 23
Something has set 'complete' to TRUE...
[1]    Done                          a.out
rohan[251]% 

(The 'rohan[250]% ' prompt actually occurs 30 seconds before the program
even begins to print anything, but I moved it down to where I typed the kill
command, to make it clearer what is going on.)
*/
