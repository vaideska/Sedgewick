﻿// 03062020>>TKUZNETSOVA
//Программа демонстрирует использование массивов, а так же разное их объявление. Демонстрируется использование 
//индексации массива по вычесляемым значениям и массив структур.

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "point.h"
using namespace std;

static const int N = 1000;

void SieveOfEratosthenes();     //Решето Эрастофена
void DynamicAllocation();       //Динамическое выделение памяти массиву
void CoinToss();                //Имитация подбрасывания монеты
void NearestPointCalculation(); //Рассчет ближайшей точки

int heads() {
    return rand() < RAND_MAX / 2;
}

float randFloat() {
    return 1.0 * rand() / RAND_MAX;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SieveOfEratosthenes();
    DynamicAllocation();
    CoinToss();
    NearestPointCalculation();
}

/*Решето Эратосфена. Функция выводит на экран все простые числа меньше N.*/
void SieveOfEratosthenes() {
    int i, a[N];                                            //память под массив выделяется во время компиляции
    for (i = 2; i < N; i++) a[i] = 1;                       //иницилизируем весь массив 1
    for (i = 2; i < N; i++)
        if (a[i])
            for (int j = i; j * i < N; j++) a[i * j] = 0;   //перебираем все множесва меньше N и приравниваем 0
    for (i = 2; i < N; i++)
        if (a[i]) cout << " " << i;                         //выводим индексы элементов, значения которых остались = 1
    cout << endl;
}

/*Динамическое выделение памяти для массива. На время компиляции неизвестно кол-во элементов.*/
void DynamicAllocation() {
    int N;                                                  //Теперь берем N локальную для функции, а не глобальную константу
    cout << "Введите размер массива:" << endl;
    cin >> N;

    int* a = new int[N];                                    //new[] - выделяет динамическ память под массив
    if (a == 0)
    {
        cout << "Не хватате памяти!" << endl;
    }

    for (int i = 0; i < N; i++) {
        a[i] = i;
        cout << a[i] << " ";
    }
    cout << endl;
}

/*Иммитация подбрасывания монеты. Если подбросить монету N раз, то ожидается N/2 выпадений. Но в принципе это число
может быть любым в диапазоне от 0 до N.Функця выполняет эксперимент M раз. Основная операция программы -
индексация массива по вычисляемым значениям*/
void CoinToss() {
    int N, M, i, j, cnt;                                            //Теперь берем N локальную для функции, а не глобальную константу
    cout << "Введите сколько раз подбрасываем монету:" << endl;
    cin >> N;
    cout << "Введите сколько раз повторяем эксперимент:" << endl;
    cin >> M;

    int* f = new int[N + 1];                                        //массив f отслеживает частоту выпадений "i решек"
    for (j = 0; j <= N; j++) f[j] = 0;
    for (i = 0; i < M; i++, f[cnt]++)                               //цикл по кол-ву экспериментов
        for (cnt = 0, j = 0; j <= N; j++)
            if (heads()) cnt++;                                     //подбрасываем монетку, сохраняем решку
    for (j = 0; j <= N; j++)                                        //выводит гистограмму ре-ов эксперимента
    {
        if (f[j] == 0) cout << ".";
        for (i = 0; i < f[j]; i += 10) cout << "*";                 //каждые 10 выпадений обозначается *
        cout << endl;
    }
}

/*Рассчет ближайшей точки. Импользуем массив структур данных. Это типичный случай, когда элементы сохраняются в массиве
для последующей обработки в процессе некоторых вычислений. Время выполнения составляет О(N^2),
поэтому программа не может выполняться для больших N. */
void NearestPointCalculation() {
    int N, i, cnt = 0;
    cout << "Введите кол-во пар точек:" << endl;
    cin >> N;

    float d;
    cout << "Введите радиус:" << endl;
    cin >> d;

    point* a = new point[N];                            //массив структур, описание point см.в заголовочном файле
    for (i = 0; i < N; i++)                             //задаются N точек в рандомном порядке
    {
        a[i].x = randFloat();
        a[i].y = randFloat();
    }

    for (i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if (distance(a[i], a[j]) < d) cnt++;        //вычисляется дистанция между двумя токами
    cout << cnt << " пар в радиусе " << d << endl;
}