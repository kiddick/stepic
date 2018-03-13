/*
Разработать программу solution, которая осуществляет поиск родительского PID текущего процесса в файловой системе proc 
и выводит найденное значение на консоль.  Результат, возвращаемый функций должен быть выведен отдельной строкой
(должен оканчиваться символом перевода строки \n) в stdio.
*/

#include <regex.h>
#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fp;
    char inp[80];
    regex_t regex;
    regmatch_t groupArray[2];
    regcomp(&regex, "PPid:\t([0-9]+)", REG_EXTENDED);
    fp = fopen("/proc/self/status", "r");
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
                        printf("%s\n", sourceCopy + groupArray[g].rm_so);
                }
            }
        fclose(fp);
    }
    return 0;
}
