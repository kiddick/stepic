/*
Разработать программу solution, которая по заданному pid, осуществляет поиск пути в дереве процессов
до процесса с идентификатором 1 (init). Для каждого найденного процесса печатается в отдельной строке его идентификатор.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char * step(char *pid) {
    char path[80];
    sprintf(path, "/proc/%s/status", pid);
    FILE *fp = fopen(path, "r");
    char inp[80];
    regex_t regex;
    regmatch_t groupArray[2];
    regcomp(&regex, "PPid:\t([0-9]+)", REG_EXTENDED);
    char *buff;
    buff=(char*)malloc(80);
    if (fp) {
        while (fgets(inp, 80, (FILE*) fp))
            if (!regexec(&regex, inp, 2, groupArray, 0)) {
                unsigned int g = 0;
                for (g = 0; g < 2; g++)
                {
                    if (groupArray[g].rm_so == (size_t)-1)
                        break;

                    char sourceCopy[strlen(inp) + 1];
                    strcpy(sourceCopy, inp);
                    sourceCopy[groupArray[g].rm_eo] = 0;
                    if (g)
                        strcpy(buff, sourceCopy + groupArray[g].rm_so);
                }
            }
        fclose(fp);
    }
    return (char *)buff;
}

int main(int argc, char const *argv[])
{
    char *last_ppid = (char *)argv[1];
    while (strcmp(last_ppid, "0")) {
        printf("%s\n", last_ppid);
        last_ppid = step(last_ppid);
    }
    return 0;
}
