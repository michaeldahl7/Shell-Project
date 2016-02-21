main(){
int i = 5;
char c[4] = "ab"; /* proper syntax is:  char c[4] = {'a', 'b', '\0'}; */
int j = 3;
printf("%s, %d, %d\n", c, i, j);
strcat(c, "cde");
c[-1] = 'd';
printf("%s, %d, %d\n", c, i, j);
}
