/*
Разработать программу solution, которая осуществляет поиск и подсчет числа процессов
с именем genenv в системе Linux на которой выполняется программа. 
*/


#include <ctype.h>
#include <dirent.h> 
#include <stdio.h>
#include <string.h>

int main(void) {
  DIR *d;
  struct dirent *dir;
  d = opendir("/proc");
  int isstr = 0;
  FILE *fp;
  char path[80];
  char inp[80];
  char key[] = "genenv\n";
  int counter =0;
  int i;
  if (d) {
    while ((dir = readdir(d)) != NULL) {
        isstr = 0;
        for (i=0;i<strlen(dir->d_name);i++)
            if (!isdigit(dir->d_name[i])) {
                isstr = 1;
                break;
            }
        if (!isstr) {
            // printf("%s\n", dir->d_name);
            sprintf(path, "/proc/%s/status", dir->d_name);
            fp = fopen(path, "r");
            if (fp) {
                fgets(inp, 80, (FILE*) fp);
                if (!strcmp(inp+6, key))
                    // printf("%s", inp + 6);
                    counter++;
            }
            fclose(fp);
        }
    }
    closedir(d);
  }
  printf("%d\n", counter);
  return(0);
}