#include "VectorNew.h"
#include <iostream>


using namespace std;


Vector::Vector(const ValueType* rawArray, const size_t size, float coef) {
    if (coef<=1){
        throw invalid_argument("Coef must be >1");
    }
    _size = size;
    _capacity = size;
    _multiplicativeCoef = coef;
    _data = {new ValueType[size]};                 // Указатель на наш массив
    copy(rawArray, rawArray + _size, _data);       // Копируем элементы из массива (количеством size)
}
//! Конструктор копирования
//! \param other - копируемый объект
// Создаем новый вектор путем копирования переданного другого вектора
Vector::Vector(const Vector& other) {
    _size = other._size;
    _capacity = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    _data = {new ValueType[_capacity]};
    copy(other._data, other._data + _size, _data);  // Копируем элементы
}


//! Оператор присваивания копированием
//! \param other - копируемый объект
Vector& Vector::operator= (const Vector &other) {
    if (this != &other) {
        _size = other._size;
        _capacity = other._capacity;
        _multiplicativeCoef = other._multiplicativeCoef;
        ValueType *newData = {new ValueType[_capacity]};
        copy(other._data, other._data + _size, newData); // Копируем элементы
        delete[] _data; // Освобождаем старую память
        _data = newData;
    }
    return *this;
}
//! Конструктор перемещения
//! \param other - перемещаемый объект
// Создаем новый вектор путем копирования переданного другого вектора, а исходный удаляем
Vector::Vector(Vector&& other) noexcept {
    _size = other._size;
    _capacity = other._capacity;
    _data = other._data;
    _multiplicativeCoef = other._multiplicativeCoef;
    // Обнуляем
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}
//! Оператор присваивания перемещением
//! \param other - перемещаемый объект
Vector& Vector::operator=(Vector &&other) noexcept {
    if (this != &other) {
        delete[] _data; // освободим старую память
        _size = other._size;
        _capacity = other._capacity;
        _multiplicativeCoef = other._multiplicativeCoef;
        _data = other._data;
        // Обнуляем
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }
    return *this;
}


//! Деструктор
// Удаления динамического массива и освобождения его памяти
Vector::~Vector() {
    delete[] _data; // указатель на динамичсекий массив
    //cout << ">>> destructor" << "\n";
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





// void Vector::pushBack(const ValueType &value)
// {
//     _expand_size(1);
//     _data[_size] = value;
//     ++_size;
// }



//! Вставка в конец
void Vector::pushBack(const ValueType& value) {
    if (_size + 1 >= _capacity){
        if (_capacity == 0){
            _capacity++;
        }

        while (_size + 1 >= _capacity) {
            _capacity *= _multiplicativeCoef;
        }
        ValueType *newData = new ValueType[_capacity];
        for (int i = 0; i < _size; i++){
            newData[i] = _data[i];
        }
        delete [] _data;
        _data = newData;
    }
    _data[_size] = value; // Добавляем в конец
    _size++; // новый размер
}


void Vector::pushFront(const ValueType &value){
    if (_size + 1 >= _capacity){
        if (_capacity == 0){
            _capacity++;
        }
        while (_size + 1 >= _capacity){
            _capacity *= _multiplicativeCoef;
        }
        ValueType *newData = new ValueType[_capacity];
        for (int i = 0; i < _size; i++){
            newData[i] = _data[i];
        }
        delete [] _data;
        _data = newData;
    }

    for (int i = _size; i > 0; i--){
        _data[i] = _data[i-1];
    }
    _data[0] = value;
    _size++;
}



// //! Вставка элемента value в позицию pos
void Vector::insert(const ValueType& value, size_t pos) {
    if (_size == _capacity) {
        // мы уже все заняли надо выполнить расширение с учетом коэффициента расширения (если еще 0, то добавим один элемент)
        size_t newCapacity = _capacity == 0 ? 1 : static_cast<size_t>(_capacity * _multiplicativeCoef);
        ValueType *newData = new ValueType[newCapacity];
        // заливаем старые данные
        if (pos > _size) {
            // Позиция за пределами массива. просто всавим в конец
            for (int i=0; i < _size; i++) {
                newData[i] = _data[i];
            }
            newData[_size] = value; // Добавляем наш элемент в конец
        } else {
            for (int i=0; i < pos; i++) {
                newData[i] = _data[i];
            }
            newData[pos] = value; // Добавляем наш элемент в конец
            for (int i=pos; i < _size; i++) {
                newData[i+1] = _data[i];
            }
        }
        _size++; // новый размер
        delete[] _data; // удаляем старые данные
        _data = newData; // новые данные
        _capacity = newCapacity; // новая граница
    } else {
        if (pos > _size) {
            // Позиция за пределами массива. просто всавим в конец
            _data[_size] = value;
            _size++; // новый размер
        } else {
            // просто сдвиг данных на один элемент вправо
            for (int i=_size; i > pos; i--) {
                _data[i] = _data[i-1];
            }
            _data[pos] = value; // Добавляем наш элемент в заданую позицию
            _size++; // новый размер
        }
    }
}


//! Вставка массива элементов типа ValueType в позицию pos
void Vector::insert(const ValueType* values, size_t size, size_t pos) {
    if ((_size + size) > _capacity) {
        // Места не хватит. Надо выполнить расширение с учетом коэффициента расширения + кусок размера size
        size_t newCapacity = _capacity == 0 ? size : (static_cast<size_t>(_capacity * _multiplicativeCoef) + size);
        ValueType *newData = new ValueType[newCapacity];
        // заливаем старые данные
        if (pos > _size) {
            //Позиция за пределами массива. просто всавим в конец
            for (int i=0; i < _size; i++) {
                newData[i] = _data[i];
            }
            for (int i=0; i < size; i++) {
                newData[_size + i] = values[i];
            }
        } else {
            for (int i=0; i < pos; i++) {
                newData[i] = _data[i];
            }
            for (int i=0; i < size; i++) {
                newData[pos + i] = values[i];
            }
            for (int i=pos; i < _size; i++) {
                newData[size + i] = _data[i];
            }
        }
        _size = _size + size; // новый размер
        delete[] _data; // удаляем старые данные
        _data = newData; // новые данные
        _capacity = newCapacity; // новая граница
    } else {
        if (pos > _size) {
            // Позиция за пределами массива. просто вставим в конец
            for (int i=0; i < size; i++) {
                _data[_size + i] = values[i];
            }
            _size = _size + size; // новый размер
        } else {
            // просто сдвиг данных на длину вставляемого массива вправо
            for (int i=_size; i > pos; i--) {
                _data[i+size-1] = _data[i-1];
            }
            for (int i=0; i < size; i++) {
                _data[pos+i] = values[i];
            }
            _size = _size + size; // новый размер
        }
    }
}


//! Вставка содержимого вектора в позицию pos
void Vector::insert(const Vector& vector, size_t pos) {
    int size = vector.size();
    if ((_size + size) > _capacity) {
        // Места не хватит. Надо выполнить расширение с учетом коэффициента расширения + кусок размера size
        size_t newCapacity = _capacity == 0 ? size : (static_cast<size_t>(_capacity * _multiplicativeCoef) + size);
        ValueType *newData = new ValueType[newCapacity];
        // заливаем старые данные
        if (pos > _size) {
            //Позиция за пределами массива. просто всавим в конец
            for (int i=0; i < _size; i++) {
                newData[i] = _data[i];
            }
            for (int i=0; i < size; i++) {
                newData[_size + i] = vector[i];
            }
        } else {
            for (int i=0; i < pos; i++) {
                newData[i] = _data[i];
            }
            for (int i=0; i < size; i++) {
                newData[pos + i] = vector[i];
            }
            for (int i=pos; i < _size; i++) {
                newData[size + i] = _data[i];
            }
        }
        _size = _size + size; // новый размер
        delete[] _data; // удаляем старые данные
        _data = newData; // новые данные
        _capacity = newCapacity; // новая граница
    } else {
        if (pos > _size) {
            // Позиция за пределами массива. просто вставим в конец
            for (int i=0; i < size; i++) {
                _data[_size + i] = vector[i];
            }
            _size = _size + size; // новый размер
        } else {
            // просто сдвиг данных на длину вставляемого массива вправо
            for (int i=_size; i > pos; i--) {
                _data[i+size-1] = _data[i-1];
            }
            for (int i=0; i < size; i++) {
                _data[pos+i] = vector[i];
            }
            _size = _size + size; // новый размер
        }
    }
}



//! Удаление с конца
void Vector::popBack() {
    if (_size == 0){
        throw "Error";
    } // Проверка, что вектор не пустой
    _size--; // новый размер
}
//! Удаление из начала
void Vector::popFront() {
    if (_size == 0){
        throw "Error";
    }
    // Проверка, что вектор не пустой
    // просто сдвиг данных на один элемент влево
    for (int i=0; i < _size; i++) {
        _data[i] = _data[i+1];
    }
    _size--; // новый размер
}

/*!
    \brief Удалить элемент(ы) из вектора
    \param pos: позиция начала удаляемого участка
    \param count: количество удаляемых элементов
    если (pos + count) > size, то элементы интервала [pos, size) должны быть удалены
*/
void Vector::erase(size_t pos, size_t count) {
    if (pos + count >= _size) {
        // от позиции до конца. следовательно просто сдвигаем границу
        _size = pos;
    } else {
        // это интервал. переносим элементы
        for (int i = pos; i < _size; i++) {
            _data[i] = _data[i + count];
        }
        _size = _size - count;
    }
}


/*!
    \brief Удалить элемент(ы) из вектора
    \param beginPos: позиция начала удаляемого участка
    \param endPos: позиция окончания удаляемого участка
    Все элементы интервала [beginPos, endPos) должны быть удалены:
    [1, 2, 3, 4] -> erase(1, 3) -> [1, 4]
    если endPos > size, то элементы интервала [beginPos, size) должны быть удалены
*/
void Vector::eraseBetween(size_t beginPos, size_t endPos) {
    if (beginPos > endPos || beginPos >= _size) {
        // контроль, чтобы начальная позиция была меньше финальной
        return;
    }
    if (endPos >= _size) {
        // от позиции до конца. следовательно просто сдвигаем границу
        _size = beginPos;
    } else {
        // это интервал. переносим элементы
        int cnt = _size - endPos - 1;
        for (int i = 0; i < cnt; i++) {
            _data[beginPos + i] = _data[endPos + i];
        }
        _size = _size - cnt;
    }
}

//! Количество элементов
// Простой getter
size_t Vector::size() const {
    return _size;
}
//! Максимальное количество элементов
// Простой getter
size_t Vector::capacity() const {
    return _capacity;
}


//! Фактор загруженности
// Расчитаем как отношение текущего размера к общедоступному
// При этом проверим, чтобы не делим на ноль, ни у приведем к типу double
double Vector::loadFactor() const {
    return _capacity == 0 ? 0 : static_cast<double>(_size)/_capacity;
}
//! Доступ к элементу по индексу
// Доступ по индексу к динамическому массиву
// Проверим, что запрос из доступного диапазона. Иначе формируем исключение
ValueType& Vector::operator[](size_t idx) {
    if (idx >= _size) throw out_of_range("Vector::operator[] ERROR: Index out of range");
    return _data[idx];
}

//! Доступ к элементу по индексу (const version)
const ValueType& Vector::operator[](size_t idx) const {
    if (idx >= _size) throw out_of_range("Vector::operator[] ERROR: Index out of range");
    return _data[idx];
}

//! Поиск первого вхождения значения
//! \return - индекс элемента
long long Vector::find(const ValueType& value) const {
    for (int i=0; i < _size; i++) {
        if (_data[i] == value) {
            return i;
        }
    }
    return -1;
}

//! Если capacity > _capacity, то выделить новый участок памяти размером capacity и перенести вектор туда, иначе - ничего
void Vector::reserve(size_t capacity) {
    if (capacity > _capacity) {
        ValueType *newData = new ValueType[capacity];
        for (int i=0; i < _size; i++) {
            newData[i] = _data[i];
        }
        delete[] _data; // удаляем старые данные
        _data = newData; // новые данные
        _capacity = capacity; // новая граница
    }
}



//! Уменьшить capacity до size
void Vector::shrinkToFit() {
    _capacity = _size;
    ValueType *newData = new ValueType[_size];
    for (int i = 0; i < _size; ++i){
        newData[i] = _data[i];
    }
    delete [] _data;
    _data = newData;
}

//==============================================================================
//! Класс, реализующий итератор

Vector::Iterator::Iterator(ValueType* ptr) {
    //cout << ".....start init Iterator" << "\n";
    _ptr = ptr; // OK
}

ValueType& Vector::Iterator::operator*() {
    return *_ptr; // OK
}

const ValueType& Vector::Iterator::operator*() const {
    return *_ptr; // OK
}

ValueType* Vector::Iterator::operator->() {
    return _ptr;
}

const ValueType* Vector::Iterator::operator->() const {
    return _ptr;
}

// Prefix increment
Vector::Iterator Vector::Iterator::operator++() {
    //cout << ".....start Prefix Iterator" << "\n";
    _ptr++;
    return *this;
}

// Postfix increment
Vector::Iterator Vector::Iterator::operator++(int) {
    //cout << ".....start Postfix Iterator" << "\n";
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

bool Vector::Iterator::operator==(const Iterator& other) const {
    return _ptr == other._ptr; // OK
}

bool Vector::Iterator:: operator!=(const Iterator& other) const {
    return _ptr != other._ptr; // OK
}

//! Получить итератор на начало вектора
Vector::Iterator Vector::begin() {
    //return Iterator(_data);
    return Iterator(&_data[0]); // Так красивше
}
//! Получить итератор на элемент вектора, следующий за последним
Vector::Iterator Vector::end() {
    //return Iterator(_data + _size);
    return Iterator(&_data[_size]);  // Так красивше
}