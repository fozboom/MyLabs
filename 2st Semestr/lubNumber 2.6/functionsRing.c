#include "headerRing.h"
#include "../myLibrary.h"

//функция добавления элемента после точки входа
void pushAfter (struct Ring **p, char* newName)
{
    struct Ring *tmp = (struct Ring*)malloc(sizeof(struct Ring));   //временный указатель на новый элемент
    tmp->next = NULL;
    tmp->prev = NULL;
    strcpy(tmp->name, newName);

    if(*p == NULL)                                                       //если кольцо пустое, то временный элемент станет точкой входа
    {
        tmp->next = tmp;
        tmp->prev = tmp;
        *p = tmp;
    }
    else                                                                 //в другом случае переписать указатели
    {
        tmp->next = (*p)->next;
        (*p)->next->prev = tmp;
        tmp->prev = (*p);
        (*p)->next = tmp;
        (*p) = tmp;
    }
}



//функция удаления текущего элемента
void deleteCurrent (struct Ring **p)
{
    if ((*p) == NULL)                               //если кольцо пустое, ничего удалять не надо
    {
        printf("\nКольцо пустое");
        return;
    }
    if ((*p) == (*p)->next)                         //если в кольце один элемент, очистить память и указать его на NULL
    {
        free(*p);
        (*p) = NULL;
        return;
    }
    struct Ring *tmp = (*p);                        //в остальных случаях переписать связь между указателями
    (*p)->next->prev = (*p)->prev;
    (*p)->prev->next = (*p)->next;
    (*p) = (*p)->next;
    free(tmp);                                      //очистить временный указатель
}



//функция для связывания элементов кольца
void connectRingElements(struct Ring* element1, struct Ring* element2)
{
    element1->next = element2;
    element2->prev = element1;
}



//функция для объединения оставшихся элементов
void appendRemainingElements(struct Ring* newRing, struct Ring** tmp, struct Ring** ring)
{
    while (*tmp != *ring)
    {
        connectRingElements(newRing, *tmp);
        *tmp = (*tmp)->next;
        newRing = newRing->next; // Обновляем newRing
    }
}



//функция слияния двух отсортированных колец в одно
struct Ring* mergeRingsInOne(struct Ring* p1, struct Ring* p2)
{
    if (p1 == NULL) return p2;                      //если одно из колец пустое, вернуть другое кольцо
    if (p2 == NULL) return p1;
    int size1 = countElementsInRing(p1), size2 = countElementsInRing(p2), i = 0, j = 0;
    struct Ring* p3 = NULL;                         //size1, size2 - размеры колец, i и j - параметры цикла по кольцам

    while (i < size1 && j < size2)                  //цикл по кольцам
    {
        if (strcmp(p1->name, p2->name) < 0)         //заносим меньший элемент
        {
            pushAfter(&p3, p1->name);   //заносим в новое кольцо имя
            p1 = p1->next;                          //сдвигаем указатель на следующий элемент
            i++;
        }
        if (strcmp(p1->name, p2->name) > 0)         //заносим больший элемент
        {
            pushAfter(&p3, p2->name);   //заносим в новое кольцо имя
            p2 = p2->next;
            j++;
        }
        else                                        //элементы одинаковые
        {
            pushAfter(&p3, p1->name);   //заносим имя в новое кольцо
            p1 = p1->next;                          //сдвигаем первый указатель
            p2 = p2->next;                          //сдвигаем второй указатель
            i++;
            j++;
        }
    }

    while (i < size1)                               //если еще остались элементы в первом кольце, сливаем их в третье кольцо
    {
        pushAfter(&p3, p1->name);
        p1 = p1->next;
        i++;
    }

    while (j < size2)                               //если еще остались элементы во втормо кольце, сливаем их в третье кольцо
    {
        pushAfter(&p3, p2->name);
        p2 = p2->next;
        j++;
    }
    p3 = p3->next;
    return p3;
}



//функция сортировки кольца
struct Ring* sortingRing(struct Ring *p)
{
    if (p == NULL || p->next == p)  return p;                   //если кольцо пустое или содержит один элемент, сортировать не надо

    struct Ring *start = p;                                     //start - начальный элемент списка

    int flag = 0;                                               //flag - флажок для отслеживания, когда закончить сортировку
    while (!flag)                                               //пока массив не отсортирован
    {
        flag = 1;
        struct Ring *tmp = p->next;
        while (tmp != p)                                        //пока не прошел все кольцо
        {
            if (strcmp(tmp->name, tmp->prev->name) < 0)         //если элементы стоят неправильно
            {
                flag = 0;                                       //помечаю, что надо еще сортировать
                char tmpName[SIZE];                             //tmpName - буфер для обмена
                strcpy(tmpName, tmp->name);                     //обмен местами
                strcpy(tmp->name, tmp->prev->name);
                strcpy(tmp->prev->name, tmpName);
            }
            tmp = tmp->next;                                    //передвигаю указатель
        }
    }

    return start;
}



//функция игры 'считалочка'
void countingHumans (struct Ring **p)
{
    char* phrase = NULL;                                //phrase - строка с текстом считалочки
    int count = 1;                                      //count - кол-во слов в считалочке
    if (*p == NULL)                                     //обработка случая, если кольцо пустое
    {
        printf("\nВы не ввели список людей");
        return;
    }
    if(*p == (*p)->next)                                //обработка случая, когда в кольце один элемент
    {
        printf("\nВ списке один человек - %s", (*p)->name);
        return;
    }
    printf("\nВведите слова считалочки: ");
    inputStr(&phrase);                              //ввод текста считалочки
    for (int i = 0; phrase[i+1] != '\0'; i++)            //цикл по строке, чтобы посчитать кол-во слов в считалочке
    {
        if(!ifLetter(phrase[i]) && ifLetter(phrase[i+1]))
        {
            count++;                                    //если переход с не буквы на букву, увеличиваю кол-во слов на один
        }
    }
    while ((*p) != ((*p)->next))                        //цикл по кольцу пока не останется один элемент
    {
        for (int i = 0; i < count - 1; i++)             //становлюсь на count-го человека
        {
            (*p) = (*p)->next;
        }
        deleteCurrent(p);                               //удаляю элемент кольца
    }
}



//функция сохранения кольца в файл
void saveToFile(struct Ring* p, char* filename, int format)
{
    FILE* file;
    if (format == 1)
        file = fopen(filename, "w");                    // открытие файла в текстовом формате для записи
    else
        file = fopen(filename, "wb");                   // открытие файла в бинарном формате для записи

    if (file == NULL)
    {
        printf("Ошибка открытия файла для записи.\n");
        return;
    }
    struct Ring* tmp = p;                                       //временный указатель на кольцо чтобы не разрушить структуру
    if (tmp != NULL)
    {
        do
        {
            if (format == 1)
                fprintf(file, "%s\n", tmp->name);               //запись в текстовом формате
            else                                                //запись в бинарном формате
                fwrite(tmp->name, sizeof(char), SIZE, file);
            tmp = tmp->next;                                    //передвигаю указатель
        } while (tmp != p);
    }

    fclose(file);
}



//функция чтения кольца из файла
struct Ring* readFromFile(char* filename, int format)
{
    FILE* file;
    if (format == 1)
        file = fopen(filename, "r");                //открытие файла в текстовом формате для чтения
    else
        file = fopen(filename, "rb");               //открытие файла в бинарном формате для чтения

    if (file == NULL)
    {
        printf("Ошибка открытия файла для чтения.\n");
        return NULL;
    }

    struct Ring* p = NULL;                              //указатель на текущую позицию в новом кольце
    char name[SIZE];                                    //буфер для чтения имени
    if (format == 1)
    {
        while (fgets(name, SIZE, file) != NULL)         //пока есть что считать
        {
            name[strcspn(name, "\n")] = '\0'; //удаляем символ новой строки
            pushAfter(&p, name);               //добавляем элемент в кольцо
        }
    }
    else
    {
        while (fread(name, sizeof(char), SIZE, file) != 0)
        {
            pushAfter(&p, name);                //добавляем считанный элемент в кольцо
        }
    }

    fclose(file);

    return p;
}



//функция удаления определенного имени из файла
void deleteName (struct Ring **p)
{
    if((*p) == NULL)
    {
        printf("\nКольцо пустое");
        return;
    }
    char* name;                                         //name - имя которое надо удалить
    int flag = 0;                                       //flag - флажок для отслеживания, есть ли имя в кольце
    printf("\nВведите имя человека, которого хотите исключить из кольца - ");
    inputStr(&name);

    struct Ring *tmp = (*p);                            //временный указатель для прохода по кольцу
    while (tmp->next != (*p))                           //пока не прошли все кольцо
    {
        if (strcmp(name, tmp->name) == 0)               //если имя нашлось, выйти из цикла и отметить это флажком
        {
            flag = 1;
            break;
        }
        tmp = tmp->next;
    }
    if (flag)                                           //если имя существует, удалить его
    {
        (*p) = tmp;
        deleteCurrent(p);
    }
    else
    {
        printf("\nТакое имя не найдено");
    }
    free(name);
}



//функция вывода кольца на экран
void printRing (struct Ring *p)
{
    printf("\n\033[3;34mСодержимое кольца:\033[0m");
    if (p == NULL)
    {
        printf("\n\033[1;41m\033[1mКольцо пустое\033[0m");
        return;
    }
    struct Ring *tmp = p;
    printf("\n");
    do
    {
        printf("\033[32m%s\033[0m\033[1;31m <-> \033[0m", tmp->name);
        tmp = tmp->next;
    }while(tmp != p);
    printf("\n");
    printf("\033[1;31m↑\033[0m");
    do
    {
        for(int i = 0; i < strlen(tmp->name) + 4; i++)
            printf("\033[1;31m_\033[0m");

        tmp = tmp->next;
    }while(tmp != p);
    printf("\033[1;31m|\033[0m");
}



//функция ввода элементов кольца с клавиатуры
void inputRing (struct Ring **p)
{
    free(*p);
    *p = NULL;
    char* name = NULL;
    printf("\nВведите имена. Чтобы завершить ввод, введите Enter");
    do
    {
        printf("\nВведите имя - ");
        inputStr(&name);
        if(name[0] == '\0') break;
        pushAfter(p, name);
    }while(1);
    if((*p) != NULL){(*p) = (*p)->next;}
}



//функция для выбора задачи
void choiceTask (enum commands *doTask, const char* tasks[], bool *taskIsFound)
{
    char* task = NULL;
    printf("\nВыберите действие:\n");
    printf("\033[30;42m'mergeRings'\033[0m - ввод данных с клавиатуры\n");
    printf("\033[30;42m'sortRing'\033[0m - использовать готовые данные из файла\n");
    printf("\033[30;42m'counting'\033[0m - считалочка\n");
    printf("\033[30;42m'save'\033[0m - сохранить данные файл\n");
    printf("\033[30;42m'finish'\033[0m - завершить программу\n");
    rewind(stdin);
    inputStr(&task);
    for(*doTask = mergeRings; *doTask < finish; (*doTask)++)
    {
        if(strcmp(task, tasks[*doTask]) == 0)
        {
            *taskIsFound = true;
            break;
        }
    }
    free(task);
}



//функция для проверки символа на букву
int ifLetter (char s)
{
    if (s >= 'a' && s <= 'z')
        return 1;
    if (s >= 'A' && s <= 'Z')
        return 1;
    return 0;
}



//функция очистки памяти
void freeRing(struct Ring *p1, struct Ring *p2, struct Ring *newRing)
{
    if(p1 != NULL)
    {
        while (p1->next != NULL)
        {
            struct Ring *tmp = p1;
            p1->next->prev = p1->prev;
            p1->prev->next = p1->next;
            p1 = p1->next;
            free(tmp);
        }
    }
    if (p2 != NULL)
    {
        while (p2->next != NULL)
        {
            struct Ring *tmp = p2;
            p2->next->prev = p2->prev;
            p2->prev->next = p2->next;
            p2 = p2->next;
            free(tmp);
        }
    }
    if(newRing != NULL)
    {
        while (newRing->next != NULL)
        {
            struct Ring *tmp = newRing;
            newRing->next->prev = newRing->prev;
            newRing->prev->next = newRing->next;
            newRing = newRing->next;
            free(tmp);
        }
    }

}



//функция для запроса у пользователя, как инициализировать кольцо
void howToInput (int* input, int* format, struct Ring **tmp)
{
    char* fileName;
    printf("\nКак вы хотите заполнить кольцо?");
    printf("\n0 - чтение кольца из файла");
    printf("\n1 - ввод кольца вручную\n");
    inputInt(input, 0, 1);
    if ((*input) == 1)
    {
        inputRing(tmp);
    }
    if ((*input) == 0)
    {
        printf("\nИз какого файла вы будете читать информацию?");
        printf("\n0 - чтение из бинарного файла");
        printf("\n1 - чтение из текстового файла\n");
        inputInt(format, 0, 1);
        printf("\nВведите имя файла - ");
        inputStr(&fileName);
        *tmp = readFromFile(fileName, *format);
        printRing(*tmp);
    }

}



//функция для запроса у пользователя, как сохранить кольцо
void howToSave (int* format, struct Ring *tmp)
{
    char* fileName;
    printf("\nВ какой файл вы хотите сохранить информацию?");
    printf("\n0 - в бинарный файл");
    printf("\n1 - в текстовый файл\n");
    inputInt(format, 0, 1);
    printf("\nВведите имя файла - ");
    inputStr(&fileName);
    saveToFile(tmp, fileName, *format);
}



//функция для запроса, хочет ли пользователь удалить элемент кольца
void doYouWantToDelete (struct Ring **p)
{
    int flag;
    printf("\nЕсли желаете удалить кого-то из кольца, введите 1");
    printf("\nЕсли не желаете, введите 0\n");
    inputInt(&flag, 0, 1);
    if(flag)
    {
        deleteName(p);
    }
}



//функция для вызова функций, чтобы объединить кольца
void caseMergeRings (int* input, int* format, struct Ring **p1, struct Ring **p2, struct Ring **newRing)
{
    howToInput(input, format, p1);
    doYouWantToDelete (p1);
    howToInput(input, format, p2);
    doYouWantToDelete (p2);
    *p1 = sortingRing(*p1);
    *p2 = sortingRing(*p2);
    *newRing = mergeRingsInOne(*p1, *p2);
    //system("clear");
    printf("\nРезультат слияния двух колец:");
    printRing(*newRing);
}



//функция для вызова функций, чтобы отсортировать кольцо
void caseSortRing (int* input, int* format, struct Ring **p1, struct Ring **newRing)
{
    howToInput(input, format, p1);
    printf("\nВы ввели следующее кольцо:"); //system("clear");
    printRing(*p1);
    doYouWantToDelete (p1);
    printf("\nОтсортированное кольцо:");
    *newRing = sortingRing(*p1);
    printRing(*newRing);
}



//функция для вызова функций, чтобы сыграть в 'считалочку'
void caseCounting (int* input, int* format, struct Ring **newRing)
{
    howToInput(input, format, newRing);
    doYouWantToDelete (newRing);
    countingHumans(newRing);
    printf("\nПобедитель - %s", (*newRing)->name);
}

//функция слияния двух отсортированных колец в одно
struct Ring* mergeRingsByPush(struct Ring* p1, struct Ring* p2)
{
    if (p1 == NULL) return p2;                                  //если одно из колец пустое, вернуть другое кольцо, сливать ничего не надо
    if (p2 == NULL) return p1;

    int flag1 = 1, flag2 = 1;                                   //flag1, flag2 - флажки для контроля обхода кольца
    struct Ring* tmp1 = p1;                                     //tmp1 - указатель для обхода первого кольца
    struct Ring* tmp2 = p2;                                     //tmp2 - указатель для обхода второго кольца
    struct Ring* p3 = NULL;                                     //p3 - кольцо, в которое будем сливать

    if (strcmp(p1->name, p2->name) < 0)                         //ставим указатель p3 на меньший элемент, который будет первым элементом нового кольца
    {
        p3 = tmp1;
        tmp1 = tmp1->next;
    }
    else
    {
        p3 = tmp2;
        tmp2 = tmp2->next;
    }

    struct Ring* newRing = p3;                                  //newRing - указатель для отслеживания текущего элемента в кольце

    while (flag1 && flag2)                                      //пока одно из колец полностью не объединились
    {
        if (strcmp(tmp1->name, tmp2->name) < 0)                 //если в первом кольце элемент меньше, добавляем его в новое кольцо
        {
            connectRingElements(newRing, tmp1);//вызвать функцию перезаписи связей между указателями
            tmp1 = tmp1->next;                                  //сдвинуть указатель tmp1 на следующий элемент
            if (tmp1 == p1) flag1 = 0;                          //если прошли все кольцо, надо перестать объединять
        }
        else                                                    //если во втором кольце элемент меньше, добавить надо его
        {
            connectRingElements(newRing, tmp2);//перезаписать связь между указателями
            tmp2 = tmp2->next;                                  //передвинуть указатель tmp2 на следующий элемент
            if (tmp2 == p2) flag2 = 0;                          //если прошли все кольцо, надо перестать объединять
        }
        newRing = newRing->next;                                //передвинуть указатель newRing
    }

    appendRemainingElements(newRing, &tmp1, &p1);      //вызвать функцию досливания первого кольца
    appendRemainingElements(newRing, &tmp2, &p2);      //вызвать функцию досливания второго кольца

    connectRingElements(newRing, p3);          // Устанавливаем связь с начальным элементом, чтобы завершить кольцо
    p3->prev = newRing;

    return p3;
}



//функция подсчета элементов в кольце
int countElementsInRing(struct Ring* ring)
{
    if (ring == NULL) return 0;

    int count = 1;
    struct Ring* current = ring->next;

    while (current != ring) {
        count++;
        current = current->next;
    }

    return count;
}


