#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/riscv.h"
#include "kernel/fcntl.h"
#include "kernel/spinlock.h"
#include "kernel/sleeplock.h"
#include "kernel/fs.h"
#include "kernel/file.h"
#include "user/user.h"
enum { NAME, PARENS, BRACKETS };
int tokentype; /*type of last token  ALSO [4] !!! */
char token[MAXTOKEN]; /*last token string */
char name[MAXTOKEN]; /*identifier name */
char datatype[MAXTOKEN]; /*data type = char, int, etc. */
char out[1000];
int gettoken(void) /* return next token */
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;        /* [1] */
    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");            /* [2][3] */
            return tokentype = PARENS;           /* [4] */
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); ) /* SUPPOSING [5] */
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}
void main(int argc, char *argv[]){
	while(1){
		char* p;
		fprintf(2,"@");
		read(0, p, 1);
		
	}
	exit();
}