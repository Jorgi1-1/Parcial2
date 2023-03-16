#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{
    int status;
    pid_t pid_D, pid_E, pid_F;

    pid_D = fork();
    if( pid_D == 0 )
    {
        return 2;

    }

    pid_E = fork();
    if( pid_E == 0 )
    {
        return 13;
    } else

    pid_F = fork();
    if( pid_F == 0 )
    {
        return(14);
    }

    if(pid_D > 0 && pid_E > 0 && pid_F > 0)
    {
        float res = 0;
        waitpid(pid_D, &status, 0);
        if (WIFEXITED(status))
        {
            res = (WEXITSTATUS(status) * 2) - 1;
        }
        waitpid(pid_F, &status, 0);
        if(WIFEXITED(status))
        {
            res = res + ((float)WEXITSTATUS(status)/100);
        }
        waitpid(pid_E, &status, 0);
        if(WIFEXITED(status))
        {
            res = res + ((float)WEXITSTATUS(status) + 3)/10000;
        }
        printf("Resultado es: %f", res);
    }
}
