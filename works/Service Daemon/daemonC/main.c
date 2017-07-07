#include <stdio.h>
#include <time.h>

void daemon(void) {
    time_t rawtime;
    while(1)
    {
        time(&rawtime);
        printf("The current date/time is: %s",ctime(&rawtime));
        sleep(20);
    }
}

int main() {
    setsid();
    chdir("/");
    fclose(stdin);
    //оставим вывод в консоль наш демон будет периодически выводить дату и время
    //fclose(stdout);
    fclose(stderr);
    daemon();

//  int pid = fork();
//  switch(  pid ) {
//  case 0:
//    setsid();
//    chdir("/");
//    close(stdin);
//    //close(stdout);
//    close(stderr);
//    demon();
//    //mainloop();
//    exit(0);
//  case -1:
//    printf("Fail: unable to fork\n");
//    break;
//  default:
//   printf("OK: demon with pid %d is created\n", pid);
//   break;
// }
 //return 0;
}
