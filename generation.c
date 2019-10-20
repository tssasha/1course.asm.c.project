#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char data[2000] = "section .data\n";
char text[2000] = "section .text\nglobal f1\nglobal f2\nglobal f3\n";

int main(int argc, char *argv[])
{
    FILE *in, *out;
    printf("%s\n", argv[1]);
    in = fopen(argv[1], "r");
    out = fopen("functions.asm", "w");
    char temp[100], temp_const[100];
    double a, b;
    int n = 1, k = 1;
    fscanf(in, "%lf %lf", &a, &b);

    strcat(text, "f1:\n");
    strcat(text, "    push ebp\n");
    strcat(text, "    mov ebp, esp\n");
    strcat(text, "    finit\n");

    while (fscanf(in, "%s", temp) != -1)
    {
        if (strcmp(temp, ",") == 0)
        {
            strcat(text, "    pop ebp\n");
            strcat(text, "    ret\n");
            if (n == 1)
            {
                strcat(text, "\nf2:\n");
            }
            if (n == 2)
            {
                strcat(text, "\nf3:\n");
            }
            strcat(text, "    push ebp\n");
            strcat(text, "    mov ebp, esp\n");
            strcat(text, "    finit\n");
            ++n;
        }
        if (strcmp(temp, "+") == 0)
        {
            strcat(text, "    faddp\n");
        }
        if (strcmp(temp, "-") == 0)
        {
            strcat(text, "    fsubp\n");
        }
        if (strcmp(temp, "*") == 0)
        {
            strcat(text, "    fmulp\n");
        }
        if (strcmp(temp, "/") == 0)
        {
            strcat(text, "    fdivp\n");
        }
        if (strcmp(temp, "sin") == 0)
        {
            strcat(text, "    fsin\n");
        }
        if (strcmp(temp, "cos") == 0)
        {
            strcat(text, "    fcos\n");
        }
        if (strcmp(temp, "tan") == 0)
        {
            strcat(text, "    fptan\n");
            strcat(text, "    fstp st0\n");
        }
        if (strcmp(temp, "rtg") == 0)
        {
            strcat(text, "    fpatan\n");
        }
        if (strcmp(temp, "x") == 0)
        {
            strcat(text, "    fld qword[ebp + 8]\n");
        }
        if (strcmp(temp, "e") == 0)
        {
            strcat(text, "    fldl2e\n");
            strcat(text, "    fld1\n");
            strcat(text, "    fscale\n");
        }
        if (strcmp(temp, "pi") == 0)
        {
            strcat(text, "    fldpi\n");
        }
        if (temp[0] >= '0' && temp[0] <= '9')
        {
            sprintf(temp_const, "%d", k);
            strcat(data, "    const");
            strcat(data, temp_const);
            strcat(data, " dq ");
            sprintf(temp, "%f", atof(temp));
            strcat(data, temp);
            strcat(data, "\n");

            strcat(text, "    fld qword[const");
            strcat(text, temp_const);
            strcat(text, "]\n");
            ++k;
        }
    }
    strcat(text, "    pop ebp\n");
    strcat(text, "    ret\n");
    fprintf(out, "%s\n", data);
    fprintf(out, "%s", text);
    fclose(in);
    fclose(out);
}