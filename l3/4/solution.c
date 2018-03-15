/*
Разработать программу solution, которая по заданному pid, осуществляет поиск пути в дереве процессов
до процесса с идентификатором 1 (init). Для каждого найденного процесса печатается в отдельной строке его идентификатор.
*/

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

int step(int pid) {
    char path[80];
    char pid_buf[20];
    // itoa(pid, pid_buf, 10);
    sprintf(pid_buf, "%d", pid);
    sprintf(path, "/proc/%s/status", pid_buf);
    FILE *fp = fopen(path, "r");
    char inp[80];
    regex_t regex;
    regmatch_t groupArray[2];
    regcomp(&regex, "PPid:\t([0-9]+)", REG_EXTENDED);
    // char *buff;
    // buff=(char*)malloc(80);
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
                        return atoi(sourceCopy + groupArray[g].rm_so);
                }
            }
        fclose(fp);
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    // char *last_ppid = (char *)argv[1];
    int last_ppid;
    int counter = 1;
    DIR *d = opendir("/proc");
    struct dirent *dir;
    int sub_counter = 0;
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (!isstr(dir->d_name)) {
                last_ppid = atoi(dir->d_name);
                // printf("%d\n", last_ppid);
                // while (strcmp(last_ppid, "0")) {
                while (last_ppid != 0) {
                    // printf("%d\n", last_ppid);
                    last_ppid = step(last_ppid);
                    // sub_counter++;
                    if (last_ppid == atoi(argv[1])) {
                        // counter = counter + sub_counter;
                        // sub_counter = 0;
                        counter++;
                        break;
                    }
                }
            }
        }
    }
    printf("%d\n", counter);
    return 0;
}

