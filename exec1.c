/*
 * EXEC EXAMPLE 1:    A PROCESS exec()S A NEW IMAGE
 */

#include <unistd.h>
#include <strings.h>
#include <stdio.h>
#define MAXARGS 20
#define FLAG  "-l"

int main (int argc, char *argv[])
{
   char *newargv[MAXARGS];
   int max;

   (void)printf("argc = %d\n", argc);
   newargv[0] = "/bin/ls";
/* Don't misinterpret the above line!  The string "/bin/ls" is not 'in'
 * the newargv array; the compiler stores this string (terminated with
 * a null character) elsewhere, and then the ADDRESS of where the
 * leading '/' lives is put into newargv[0].  newargv is an array of
 * ADDRESSES (i.e., POINTERS to characters), NOT an array of characters!
 */
   newargv[1] = FLAG;
   max = (argc > (MAXARGS - 2)) ? (MAXARGS - 2) : argc;
   {
   int i;
   for (i=1; i < max; i++)
       newargv[i+1] = argv[i];
   }
   newargv[max+1] = NULL;
   execv("/bin/ls", newargv);

/* A production version should check to see if the exec() failed 
 * and take appropriate action.  In many cases, failure to do
 * so can result in spectacular problems.
 */

   (void)printf("Under what conditions will this line be printed?\n");
}

/*
 *  execv("ls", newargv);  ...will fail, unless you happen to be in /bin
 *  execvp("ls", newargv); ...will succeed, whatever the current working dir-
 *                            ectory is, as long as /bin is in your $PATH
 */
