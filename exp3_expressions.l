%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int op = 0, i;
float a, b;

void digi();
%}

dig   [0-9]+|([0-9]*\.[0-9]+)
add   \+
sub   \-
mul   \*
div   \/
pow   \^
ln    \n

%%

{dig} { digi(); }
{add} { op = 1; }
{sub} { op = 2; }
{mul} { op = 3; }
{div} { op = 4; }
{pow} { op = 5; }
{ln}  { printf("\nThe Answer: %f\n\n", a); }

%%

void digi() {
    if (op == 0) {
        a = atof(yytext);
    } else {
        b = atof(yytext);
        switch (op) {
            case 1: a = a + b; break;
            case 2: a = a - b; break;
            case 3: a = a * b; break;
            case 4: 
                if (b == 0) {
                    printf("Error: Division by zero\n");
                    exit(1);
                }
                a = a / b;
                break;
            case 5: a = pow(a, b); break;  // Fixed exponentiation
        }
        op = 0;
    }
}

int main() {
    printf("Enter an expression: \n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
