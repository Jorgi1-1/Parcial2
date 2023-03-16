#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include<fcntl.h>

int main() {
    int status, fd, m;
    pid_t pid_B, pid_C;

    pid_B = fork(); 
    if (pid_B == 0) 
    { 
        printf("ID de B: %d\n", getpid());
        printf("ID de padre de B: %d\n", getppid());
        execl("/procesoB", "", NULL);
        return(3);
    }  

    pid_C = fork();
    if (pid_C == 0) 
    {
        sleep(3);
        printf("ID de C: %d\n", getpid());
        printf("ID de padre de C: %d\n", getppid());
    } 

    if(pid_B > 0 && pid_C > 0) 
    { 
        waitpid(pid_B, &status, 0);
        if (WIFEXITED(status))
        {
            printf("El valor de retorno de B fue: %d\n", WEXITSTATUS(status));
        }

        int num;
        fd = open("enteros.dat", O_RDONLY);
        printf("Contenido de enteros.dat:\n");
        m = read(fd, "%d", &num);
        {
            printf("%d\n", num);
        }

        close(fd);
    }
    return 0;
}
