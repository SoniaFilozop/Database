/*                      Б А З А   Д А Н Н Ы Х -
                  О Д Н О С В Я З Н Ы Й   С П И С О К
*/

#include <iostream>
#include <fstream>
using namespace std;

// Два варианта фильмов: полнометражный фильм и сериал.
struct Subscriber
{
    Subscriber* Next;   // Указатель на следующую структуру в списке.
    char Case;
    union
    {
        struct { char Director[20]; int Duration; } Movie;
        struct { int Series; } Serial;
    };
    char Name[20];
    int Year;
};
// Указатель начала списка - базы данных:
Subscriber* DataBase = NULL;
// Ввод информации варианта cs :
Subscriber InpSubscriberInfo(char cs)
{
    Subscriber scb;
    if (scb.Case = cs)
    {
        cout << "НАЗВАНИЕ ФИЛЬМА: "; cin >> scb.Name;
        cout << "РЕЖИССЕР: "; cin >> scb.Movie.Director;
        cout << "ГОД ВЫХОДА: "; cin >> scb.Year;
        cout << "ДЛИТЕЛЬНОСТЬ: "; cin >> scb.Movie.Duration;

    }
    else
    {
        cout << "НАЗВАНИЕ СЕРИАЛА: "; cin >> scb.Name;
        cout << "ГОД ВЫХОДА: "; cin >> scb.Year;
        cout << "КОЛИЧЕСТВО СЕРИЙ: "; cin >> scb.Serial.Series;
    }
    return scb;
}
// Вывод информации:
void OutSubscriberInfo(Subscriber scb)
{
    if (scb.Case)
    {
        cout << scb.Name << " | " << scb.Year << " | " << scb.Movie.Director << " | " << scb.Movie.Duration << endl;
    }
    else cout << scb.Name << " | " << scb.Year << " | " << scb.Serial.Series << endl;
}

/* Поиск в списке фильма с заданным порядковым номером num в списке
(нумеруем, начиная с 0):   */
Subscriber* FoundSubscriberNum(int num)
{
    Subscriber* p = DataBase;
    while (p != NULL && num--)   // Пока не конец списка и не найден фильм,
        p = p->Next;            // продвигаем указатель вдоль списка.
    return p;   // Возвращаем указатель на найденный элемент или NULL,
}              /* если элемент не найден.
   Добавить новый фильм в список за номером num:   */
void AddSubscriber(int num, char cs)
{
    Subscriber* q = new Subscriber;// Создали новую структуру.
    *q = InpSubscriberInfo(cs);    // Заполнили ее информацией.
    if (DataBase == NULL) num = 0;   // Если список пустой - добавим в начало.
    if (num)
    {
        Subscriber* p = DataBase;      // Ищем указатель
        while (p->Next != NULL && --num) // на предыдущую структуру.
            p = p->Next;
        q->Next = p->Next; p->Next = q;// Вставляем новую структуру после *p
    }
    else { q->Next = DataBase; DataBase = q; } // Добавим в начало списка.
}
// Удалить фильм с номером num из списка:
void DeleteSubscriber(int num)
{
    Subscriber* q;
    if (DataBase == NULL) return;
    if (num)
    {
        Subscriber* p = DataBase;// Ищем указатель на предыдущую структуру.
        while (p->Next != NULL && --num) p = p->Next;
        if ((q = p->Next) != NULL) { p->Next = q->Next; delete q; }
    }                           // Удаляем начальный элемент:
    else { q = DataBase; DataBase = q->Next; delete q; }
}


void main()
{
    setlocale(LC_ALL, "Russian");

    Subscriber* p;   int i, j;
    while (1)
    {
        cout << "    Меню СУБД:" << endl
            << "1. Ввод данных." << endl
            << "2. Вывод информации о фильме." << endl
            << "3. Вывод всей информации." << endl
            << "4. Удалить фильм." << endl
            << "5. Ввод данных из файла." << endl
            << "6. Вывод данных в файл. " << endl
            << "7. Закончить работу." << endl
            << ">";
        cin >> i;
        switch (i)
        {
        case 1: cout << "Номер фильма: "; cin >> i;
            cout << "Вариант (0 - Сериал, 1 - полнометражный фильм): "; cin >> j;
            AddSubscriber(i - 1, j); break;
        case 2: cout << "Номер фильма: "; cin >> i;
            if ((p = FoundSubscriberNum(i - 1)) != NULL)
                OutSubscriberInfo(*p);
            else cout << "Фильм не найден!" << endl;
            break;
        case 3: p = DataBase; i = 1;
            while (p != NULL)
            {
                cout << "Фильм" << i++ << ':' << endl;
                OutSubscriberInfo(*p); p = p->Next;
            }
            break;
        case 4: cout << "Номер фильма: "; cin >> i;
            DeleteSubscriber(i - 1); break;
        case 5:
        {
            ifstream theFile("movies.txt");
            int num, id;

            while (!theFile.eof()) {
                theFile >> num >> id;
                Subscriber* q = new Subscriber;// Создали новую структуру.
                Subscriber scb;
                if (scb.Case = (char) id) {
                    theFile >> scb.Name >> scb.Movie.Director >> scb.Year >> scb.Movie.Duration;
                }
                else {;
                    theFile >> scb.Name >> scb.Year >> scb.Serial.Series;
                }
                *q = scb;    // Заполнили ее информацией.
                if (DataBase == NULL) num = 0;   // Если список пустой - добавим в начало.
                if (num)
                {
                    Subscriber* p = DataBase;      // Ищем указатель
                    while (p->Next != NULL && --num) // на предыдущую структуру.
                        p = p->Next;
                    q->Next = p->Next; p->Next = q;// Вставляем новую структуру после *p
                }
                else { q->Next = DataBase; DataBase = q; } // Добавим в начало списка.
                num++;
            }
            break;
        }
        case 6:
        {
            ofstream outFile("/Users/sonia/Documents/outMovies.txt");
            p = DataBase; i = 1;
            while (p != NULL)
            {
                outFile << "Фильм" << i++ << ':' << endl;
                Subscriber scb = *p;
                if (scb.Case)
                {
                    outFile << scb.Name << " | " << scb.Year << " | " << scb.Movie.Director << " | " << scb.Movie.Duration << endl;
                }
                else outFile << scb.Name << " | " << scb.Year << " | " << scb.Serial.Series << endl;
                p = p->Next;
            }
            break;
        }
        case 7: while (DataBase != NULL)   // Удаляем весь список.
        {
            p = DataBase; DataBase = p->Next; delete p;
        }
              return;
        default: cout << "Поторите ввод!" << endl;
        }
    }
}
