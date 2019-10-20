#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

extern double f1();    
extern double f2();   
extern double f3();

int it;

double root(double (*f)(double), double (*g)(double), double a, double b, double eps1)
{
    it = 0;
    int var = 1;
    double Fa = f(a) - g(a);
    double Fb = f(b) - g(b);
    double Fab2 = f((a + b) / 2) - g((a + b) / 2);
    if (Fa > 0)
    {
        var = -1;
    }
    if (Fab2 > (Fa + Fb) / 2)
    {
        var *= -1;
    }
    double c = (a * Fb - b * Fa) / (Fb - Fa);
    ++it;
    if (var == 1)
    {
        while((f(c) - g(c)) * (f(c + eps1) - g(c + eps1)) > 0)
        {
            a = c;
            c = (a * (f(b) - g(b)) - b * (f(a) - g(a))) / ((f(b) - g(b)) - (f(a) - g(a)));
            ++it;
        }
    }
    else
    {
        while((f(c) - g(c)) * (f(c - eps1) - g(c - eps1)) > 0)
        {
            b = c;
            c = (a * (f(b) - g(b)) - b * (f(a) - g(a))) / ((f(b) - g(b)) - (f(a) - g(a)));
            ++it;
        }
    }
    return c;
}

double integral(double (*f)(double), double a, double b, double eps2)
{
    if (a > b)
    {
        double t = a;
        a = b;
        b = t;
    }
    int n = 20;
    double I_sum = 0, I1, I2;
    double h = (b - a) / n;
    for (int i = 0; i < n; ++i)
    {
        I_sum += 0.5 * (f(a + i * h) + f(a + (i + 1) * h));
    }
    I2 = h * I_sum;
    do
    {
        I1 = I2;
        for (int i = 0; i < n; ++i)
        {
            I_sum += f(a + 0.5 * h + i * h);
        }
        n *= 2;
        h /= 2;
        I2 =  h * I_sum;

    } while(fabs(I1 - I2) / 3 > eps2);
    return I2;
}

void abscissa(void)
{
    FILE *in;
    in = fopen("input.txt", "r");
    double a, b;
    fscanf(in, "%lf %lf", &a, &b);
    fclose(in);
    printf("Abscissa of the point of intersection f1 and f2 is %.4lf.\n", root(f1, f2, a, b, 0.00005));
    printf("Abscissa of the point of intersection f1 and f3 is %.4lf.\n", root(f1, f3, a, b, 0.00005));
    printf("Abscissa of the point of intersection f2 and f3 is %.4lf.\n\n", root(f2, f3, a, b, 0.00005));
}

void iterations(void)
{
    FILE *in;
    in = fopen("input.txt", "r");
    double a, b;
    fscanf(in, "%lf %lf", &a, &b);
    fclose(in);
    int x;
    x = root(f1, f2, a, b, 0.00005);
    int n = it;
    x = root(f1, f3, a, b, 0.00005);
    n += it;
    x = root(f2, f3, a, b, 0.00005);
    n += it;
    printf("The number of iterations to find the intersection points is %d.\n\n", n);
}

void help(void)
{
    printf("Options:\n--absc                Display abscissas of the points of intersections.\n--it                  Display number of iterations of roots search.\n--help                Display this information.\n--root f g a b eps1   Find intersection point of f and g between points a and b with accuracy eps1.\n--integral f a b eps2 Find the integral from a to b for function f with accuracy eps2.\n\n");
}


char* allowedFlags[] = { "--absc", "--it", "--help", "--root", "--integral"};
 
void* commandsStore[] = {abscissa, iterations, help, root, integral};
 
int validateFlags(char* flags[], int count)
{
    int incorrectFlagIndex = -1;
    int i, j;
    for (i = 1; i < count; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (strcmp(flags[i], allowedFlags[j]) == 0)
            {
                incorrectFlagIndex = -1;
                break;
                if (strcmp(flags[i], "--root") == 0)
                {
                    i += 5;
                }
                if (strcmp(flags[i], "--integral") == 0)
                {
                    i += 4;
                }
            }
            else 
            { 
                incorrectFlagIndex = i; 
            }
        }

        if (incorrectFlagIndex > -1)
        {
            printf("Error: incorrect flag %s\n" , flags[incorrectFlagIndex]);
            return -1;
        }
        return 0;
    }
}
 
void invokeCommands(char* flags[], int count)
{
    int i, j;
    for(i = 1; i < count; i++)
    {
        if(strcmp (flags[i], "--absc") == 0)
        {
            abscissa();
        }
        if(strcmp (flags[i], "--it") == 0)
        {
            iterations();
        }
        if(strcmp (flags[i], "--help") == 0)
        {
            help();
        }
        if(strcmp (flags[i], "--root") == 0)
        {
            if (atoi(flags[i + 1]) == 1 && atoi(flags[i + 2]) == 2)
            {
                printf("Intersection point of curves f1 and f2 is %.4lf.\n\n", root(f1, f2, atof(flags[i + 3]), atof(flags[i + 4]), atof(flags[i + 5])));
            }
            if (atoi(flags[i + 1]) == 1 && atoi(flags[i + 2]) == 3)
            {
                printf("Intersection point of curves f1 and f3 is %.4lf.\n\n", root(f1, f3, atof(flags[i + 3]), atof(flags[i + 4]), atof(flags[i + 5])));
            }
            if (atoi(flags[i + 1]) == 2 && atoi(flags[i + 2]) == 3)
            {
                printf("Intersection point of curves f2 and f3 is %.4lf.\n\n", root(f2, f3, atof(flags[i + 3]), atof(flags[i + 4]), atof(flags[i + 5])));
            }
            i += 5;
        }
        if(strcmp (flags[i], "--integral") == 0)
        {
            if (atoi(flags[i + 1]) == 1)
            {
                printf("Integral from %lf to %lf of function f1 is %.4lf.\n\n", atof(flags[i + 2]), atof(flags[i + 3]), integral(f1, atof(flags[i + 2]), atof(flags[i + 3]), atof(flags[i + 4])));
            }
            if (atoi(flags[i + 1]) == 2)
            {
                printf("Integral from %lf to %lf of function f2 is %.4lf.\n\n", atof(flags[i + 2]), atof(flags[i + 3]), integral(f2, atof(flags[i + 2]), atof(flags[i + 3]), atof(flags[i + 4])));
            }
            if (atoi(flags[i + 1]) == 3)
            {
                printf("Integral from %lf to %lf of function f3 is %.4lf.\n\n", atof(flags[i + 2]), atof(flags[i + 3]), integral(f3, atof(flags[i + 2]), atof(flags[i + 3]), atof(flags[i + 4])));
            }
            i += 4;
        }
    }
}





int main(int argc, char *argv[])
{
    int err = 0;
    if(argc > 1)
    {
        err = validateFlags(argv, argc);
    }
    if (err)
    {
        help();
    }
    else
    {
        invokeCommands(argv, argc);
    }

    double eps1 = 0.00005, eps2 = 0.0001;
    double x12, x13, x23, s1, s2, s3, s, a, b;
    FILE *in;
    in = fopen("input.txt", "r");
    fscanf(in, "%lf %lf", &a, &b);
    fclose(in);
    x12 = root(f1, f2, a, b, eps1);
    x13 = root(f1, f3, a, b, eps1);
    x23 = root(f2, f3, a, b, eps1);
    
    s1 = integral(f1, x12, x13, eps2);
    s2 = integral(f2, x12, x23, eps2);
    s3 = integral(f3, x13, x23, eps2);
    if ((x12 - x13) * (x12 - x23) < 0)
    {
        s = fabs(s3 - s1 - s2);
    }
    else if ((x13 - x12) * (x13 - x23) < 0)
    {
        s = fabs(s2 - s1 - s3);
    }
    else
    {
        s = fabs(s1 - s2 - s3);
    }
    printf("The area of the figure bounded by three given curves is %.3lf.\n", s);
    return 0;
}