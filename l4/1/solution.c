/*
Некоторая утилита генерирует довольно большой вывод, а вам требуется всего-лишь
посчитать количество символов '0' в этом выводе. Утилита при запуске принимает 1 параметр.
Вам требуется разработать программу, которая вызывает указанную утилиту,
с заданным параметром и подсчитывает количество символов '0' в ее выводе.
Ваша программа принимает на вход 2 параметра -- имя утилиты,
в текущем каталоге и ее параметр. Ваша программа должна после подсчета
вывести найденное число '0' в отдельной строке, заканчивающейся символом конца строки.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char *command = malloc(sizeof(char) * (strlen(argv[1]) + strlen(argv[2]) + 1));
    strcat(command, argv[1]);
    strcat(command, " ");
    strcat(command, argv[2]);
    FILE *pipe = popen(command, "r");
    free(command);

    int n = 0, c;
    if (pipe) {
        do {
            c = fgetc(pipe);
            if (c == '0') n++;
        } while (c != EOF);
        pclose(pipe);
    }
    printf("%d\n", n);
    return 0;
}
