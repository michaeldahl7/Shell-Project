/*Synopsis  - Takes input from the keyboard and returns the characterCount followed by the array of characeters.
 Also will return 0 when /n is reached and an empty array, and -1 and an empty array at EOF.

Michael Dahl
John Carroll
CS 570
Due: 2/10/2016
 */

/* Include Files */
#include <stdio.h>
//#include <string.h>
//#include <strings.h>

int getword(char *w)
{
    int iochar;
	int letterCount = 0;
    while ( ( iochar = getchar() ) && letterCount < 255)   {
		if(letterCount == 254){
 			w[letterCount] = '\0';			//Section of code intended to handle for max size 255
 			int temp = letterCount;
 			letterCount = 0;
 			ungetc(iochar, stdin);
			return temp;
    	}
		switch(iochar){
			case ' ' :
					if(letterCount < 1)
						break;
					else {
						w[letterCount] = '\0';
						return letterCount;
						break;
					}
			case '\n' :
				if(letterCount < 1){
					w[0] = '\0';
					return 0;
				}
				else{
					ungetc(iochar, stdin);
					w[letterCount] = '\0';
					return letterCount;
				}
			case EOF :
				if(letterCount < 1){
					w[0] = '\0';
					return iochar;
				}
				else{
					ungetc(iochar, stdin);
					w[letterCount] = '\0';
					return letterCount;
				}
			case '<' :
					if(letterCount < 1){
						w[letterCount] = iochar;
						w[1] = '\0';
						return 1;
					}
					else{
						ungetc(iochar, stdin);
						w[letterCount] = '\0';
						return letterCount;
					}
			case '>' :
					if(letterCount < 1){
						w[letterCount] = iochar;
						w[1] = '\0';
						return 1;
					}
					else{
						ungetc(iochar, stdin);
						w[letterCount] = '\0';
						return letterCount;
					}
			case '\'' :
				while((iochar = getchar())){
					switch(iochar){
						case '\\' :
							w[letterCount] = iochar;
							if((iochar = getchar()) == '\'')
								w[letterCount] = iochar;
							else
								ungetc(iochar, stdin);
							letterCount++;
							break;
						case '\n' :
							ungetc(iochar, stdin);
							w[letterCount] = '\0';
							return letterCount;
						case '\'' :
							w[letterCount] = '\0';
							return letterCount;
						case EOF :
							ungetc(iochar, stdin);
							w[letterCount] = '\0';
							return letterCount;
						default:
							w[letterCount] = iochar;
							letterCount++;
							break;

 					}
				}
			case '|' :
				if(letterCount < 1){
					w[letterCount] = iochar;
					w[1] = '\0';
					return 1;
				}
				else{
					ungetc(iochar, stdin);
					w[letterCount] = '\0';
					return letterCount;
				}
			case ';' :
				if(letterCount < 1){
					w[0] = '\0';
					return 0;
				}
				else{
					ungetc(iochar, stdin);
					w[letterCount] = '\0';
					return letterCount;
				}
			case '\\' :
			iochar = getchar();
			if(iochar != '\n'){
					w[letterCount] = iochar;
					letterCount++;
					break;
			}
			else{
				ungetc(iochar, stdin);
				w[letterCount] = '\0';
				return letterCount;
			}
			case '&' :
					if(letterCount < 1){
						w[letterCount] = iochar;
						w[1] = '\0';
						return 1;
					}
					else{
						ungetc(iochar, stdin);
						w[letterCount] = '\0';
						return letterCount;
					}

			default :
					w[letterCount] = iochar;
					letterCount++;
					break;

		}
	}
}
