#include <iostream>
#include "VectorNew.h"
using namespace std;

// Печать обычного массива
void printArr(ValueType arr[], int size) {
    for (int i=0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

// Печать массива переданного через указатель
void printPntArr(ValueType* arr, int size) {
    for (int i=0; i < size; i++) {
        cout << *(arr + i) << " ";
    }
    cout << "\n";
}

// Печать нашего Vector
void printVector(Vector& vector) {
    if (vector.size() == 0) cout << "vector is null ";
    for (double i : vector) {
        cout << i << " ";
    }
    cout << "(" << vector.capacity() << ", " << vector.size() << ")";
    cout << "\n";
}


int main() {
    //----------------------------------------------
    cout << "START (1) ......................." << "\n";
    // Обычный массив и его тест
    ValueType arr[11] = {10, 20, 30, 40, 50, 60, 70, 71, 72, 73, 74}; // Обычный массив
    ValueType* pntArr = arr;                 // Указатель на массив

    printArr(arr, 5);
    printPntArr(pntArr, 5);

    cout << "START (2) ......................." << "\n";
    // Создание вектора
    Vector v1(pntArr, 5, 2.0);
    printVector(v1);

    Vector v2(pntArr, 3, 2.0);
    printVector(v2);

    cout << "START (3) ......................." << "\n";
    // Копирование вектора
    Vector v11(v1);
    printVector(v1);
    printVector(v11);
    Vector v12;
    v12 = v1;
    printVector(v12);
    printVector(v1);

    cout << "START (4) ......................." << "\n";
    //Перемещение вектора
    Vector v21(pntArr, 5, 2.0);
    Vector v22(move(v21));
    printVector(v22);
    printVector(v21);

    Vector v31(pntArr, 5, 2.0);
    Vector v32;
    v32 = move(v31);
    printVector(v32);
    printVector(v31);

    cout << "START (5) ......................." << "\n";
    // Добавление в конец, добавление в начало
    v1.pushBack(200);
    printVector(v1);
    v1.pushFront(100);
    printVector(v1);

    cout << "START (6) ......................." << "\n";
    // Удаление с конца, удаление с начала
    v1.popBack();
    printVector(v1);
    v1.popFront();
    printVector(v1);

    cout << "START (7) ......................." << "\n";
    Vector v71(pntArr, 11, 2.0);
    printVector(v71);
    v71.erase(6, 3);
    printVector(v71);

    Vector v72(pntArr, 11, 2.0);
    printVector(v72);
    v72.eraseBetween(6, 9);
    printVector(v72);
    v72.eraseBetween(9, 10);
    printVector(v72);

    cout << "START (8) ......................." << "\n";
    Vector v81(pntArr, 11, 2.0);
    printVector(v81);
    v81.insert(5, 8);
    printVector(v81);
    v81.insert(0, 5);
    printVector(v81);

    cout << "START (9) ......................." << "\n";
    ValueType arr9[5] = {1, 2, 3, 4, 5}; // Обычный массив
    Vector v91(pntArr, 10, 2.0);
    printVector(v91);
    v91.insert(arr9, 5, 3);
    printVector(v91);
    v91.insert(arr9, 5, 1);
    printVector(v91);

    Vector v92(pntArr, 4, 2.0);
    printVector(v92);
    v91.insert(v92, 3);
    printVector(v91);

    cout << "START (10) ......................." << "\n";
    printVector(v91);
    int val = 30;
    long long idx = v91.find(val);
    cout << "find " << val << " -> " << idx << "\n";

    cout << "START (11) ......................." << "\n";
    printVector(v91);
    v91.shrinkToFit();
    printVector(v91);
    v91.reserve(40);
    printVector(v91);

    cout << "START (12) ......................." << "\n";
    printVector(v91);

    auto iterBegin { v91.begin() };  // получаем итератор
    cout << "begin -> " << *iterBegin << "\n";

    auto iterEnd { v91.end() };  // получаем итератор (Должен быть OUT)
    cout << "end -> " << *iterEnd << "\n";

    ++iterBegin;
    cout << "begin (1)-> " << *iterBegin << "\n";
    iterBegin++;
    cout << "begin (2)-> " << *iterBegin << "\n";

    // Пробегаем по вектору с помощью итераторов
    for (auto it = v91.begin(), end = v91.end(); it != end; ++it) {
        const auto i = *it;
        cout << i << ".";
    }
    cout << " \n";

    cout << "FINISH.........................." << "\n";

    return 0;
}
