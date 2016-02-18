#include "p2.h" /* Not sure what else ill need*/
//#define statements /*such as flags , */
//declarations;
int c;
char s[STORAGE*MAXITEM];
char * ptr;
int wordCount = 0;

int main()
{

//Declaration of locals
//any necessary setup, including signal catcher??
	for(;;){
		printf("p2: ");
		/*setup redirections*/
		parse(s);
		if(wordCount == 0)
			continue;
		//else if()
		/*if(fork() == 0){
			redirect I/O as requested

			use execvp() to start requested process
			If execvp() vails {
				print error message
			exit(9);
			}
		}
		If approprioate, wait for child to complete;
		Else print the childs pid, and in this case, the child should redirect its stdin to /dev/null*/
	}
	//killpg(getpid(), SIGTERM); //Terminate any children that are still running. WARNING: bad args to killpg can kill auto grader,

	printf("p2 terminated. \n");

	exit(0);
}

void parse(char *w){
	//ptr = w;
	int letters = getword(w);
	while(letters != 0 && letters != -1){
		wordCount++;
		printf("n=%d, s=[%s]\n", letters, s);
		w = (w+(letters+1));
		letters = getword(w);
	}
}
