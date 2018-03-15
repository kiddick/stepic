/*
Разработать программу solution, которая по заданному pid, осуществляет поиск всех потомков процесса 
с этим идентификатором и выводит их количество (включая процесс с заданным pid).
*/

// !В данном решении не учитываются потомки потомков при подсчете

#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int isstr(char *str) {
    int flag = 0;
    int i;
    for (i = 0; i < strlen(str); i++) {
        if (!isdigit(*str)) {
            flag = 1;
            break;
        }
    }
    return flag;
}

int get_ppid(char *inp, regmatch_t * groupArray) {
    unsigned int g = 0;
    for (g = 0; g < 2; g++)
    {
        if (groupArray[g].rm_so == (size_t)-1)
            break;

        char sourceCopy[strlen(inp) + 1];
        strcpy(sourceCopy, inp);
        sourceCopy[groupArray[g].rm_eo] = 0;
        if (g)
            return atoi(sourceCopy + groupArray[g].rm_so);
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    DIR *d = opendir("/proc");
    struct dirent *dir;
    FILE *fp;
    char path[80];
    regex_t regex;
    regmatch_t groupArray[2];
    regcomp(&regex, "PPid:\t([0-9]+)", REG_EXTENDED);
    char inp[80];
    int counter = 1;
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            // if (!isstr(dir->d_name)) {
            sprintf(path, "/proc/%s/status", dir->d_name);
            fp = fopen(path, "r");
            if (fp) {
                while (fgets(inp, 80, (FILE*) fp)) {
                    if (!regexec(&regex, inp, 2, groupArray, 0)) {
                        if (get_ppid(inp, groupArray) == atoi(argv[1]))
                            counter++;
                    }

                }
                fclose(fp);
            }
            // }

        }
        closedir(d);
    }
    printf("%d\n", counter);
    return 0;
}
