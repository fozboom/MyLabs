#include "headerPractice.h"


//                                                 Шифрование текста: алгоритм RSA и шифр четырех квадратов

int main()
{
    char **text = NULL, **newText = NULL;                           //text - исходный текст, newText - текст зашифрованный Square
    struct dataCode* keys;                                          //keys - структура с данными о зашифрованных файлах
    long **codeText = NULL, countKeys, rows, n;                     //codeText - текст зашифрованный RSA, n - кол-во строк исходного текста
                                                                    //countKeys - кол-во структур, rows - кол-во строк закодированного текста
    const char* commands[] = {"input", "read", "encoding", "decoding", "save", "finish"};
    enum choiceCommand command;                                     //command - перечисления для читабельности кода
    bool taskIsFound;                                               //TaskIsFound - переменная для определения правильности введенной команды
    int end = 1;                                                    //end - переменная для продолжения/завершения программы

    readStructInfo(&keys, &countKeys);                   //считываю информацию о зашифрованных файлах в keys
    do
    {
        choiceTask(&command, commands, &taskIsFound);  //выбор команды
        if (taskIsFound)
        {
            switch(command)
            {
                case input:
                    input2DString(&text, &n);                        //ввод текста с клавиатуры
                    break;
                case read:
                    caseReadText(&text, &n);                   //чтение текста из файла
                    break;
                case encoding:                                       //кодирование текста
                    caseEncoding(&keys, &countKeys, &codeText, text, n, &newText);
                    break;
                case decoding:                                       //декодирование текста
                    caseDecoding(&text, codeText, newText, keys, countKeys, &rows);
                    break;
                case save:                                           //сохранение данных в файл
                    saveInformation(text, newText, codeText, n, keys, countKeys);
                    break;
                case finish:
                    saveStructInfo(keys, countKeys);       //сохранение данных о закодированных файлах
                    end = 0;
                    break;
            }
        }
        else
        {
            printf("\n\033[3;31m Команда введена неверно, попробуйте еще раз \033[0m\n");
        }
    }while(end);
    freeMemory(text, newText, codeText, keys, countKeys, n);            //очистка памяти
    return 0;
}




