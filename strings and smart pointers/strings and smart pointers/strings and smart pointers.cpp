#include <iostream>
#include <memory>
using namespace std;

// Класс, имитирующий unique_ptr
template <typename T>
class MyUniquePtr
{
private:
    T* ptr;

public:
    // Конструктор по умолчанию
    MyUniquePtr() : ptr(nullptr) {}

    // Конструктор, принимающий указатель
    explicit MyUniquePtr(T* p) : ptr(p) {}

    // Конструктор копирования (запрещен)
    MyUniquePtr(const MyUniquePtr& other) = delete;

    // Оператор присваивания (запрещен)
    MyUniquePtr& operator=(const MyUniquePtr& other) = delete;

    // Перемещающий конструктор
    MyUniquePtr(MyUniquePtr&& other) noexcept
    {
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    // Перемещающий оператор присваивания
    MyUniquePtr& operator=(MyUniquePtr&& other) noexcept
    {
        if (this != &other)
        {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Деструктор
    ~MyUniquePtr()
    {
        delete ptr;
    }

    // Оператор разыменования
    T& operator*() const
    {
        return *ptr;
    }

    // Оператор доступа к члену
    T* operator->() const
    {
        return ptr;
    }

    // Получение сырого указателя
    T* get() const
    {
        return ptr;
    }

    // Проверка на пустоту
    bool operator!() const
    {
        return ptr == nullptr;
    }

    // Передача владения
    void reset(T* p = nullptr)
    {
        delete ptr;
        ptr = p;
    }

    // Передача владения
    T* release()
    {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }
};

// Класс, имитирующий shared_ptr
template <typename T>
class MySharedPtr
{
private:
    T* ptr;
    int* ref_count;

public:
    // Конструктор по умолчанию
    MySharedPtr() : ptr(nullptr), ref_count(nullptr) {}

    // Конструктор, принимающий указатель
    explicit MySharedPtr(T* p) : ptr(p), ref_count(new int(1)) {}

    // Конструктор копирования
    MySharedPtr(const MySharedPtr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        (*ref_count)++;
    }

    // Оператор присваивания
    MySharedPtr& operator=(const MySharedPtr& other)
    {
        if (this != &other)
        {
            if (--(*ref_count) == 0)
            {
                delete ptr;
                delete ref_count;
            }
            ptr = other.ptr;
            ref_count = other.ref_count;
            (*ref_count)++;
        }
        return *this;
    }

    // Перемещающий конструктор
    MySharedPtr(MySharedPtr&& other) noexcept
    {
        ptr = other.ptr;
        ref_count = other.ref_count;
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    // Перемещающий оператор присваивания
    MySharedPtr& operator=(MySharedPtr&& other) noexcept
    {
        if (this != &other)
        {
            if (--(*ref_count) == 0)
            {
                delete ptr;
                delete ref_count;
            }
            ptr = other.ptr;
            ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    // Деструктор
    ~MySharedPtr()
    {
        if (--(*ref_count) == 0)
        {
            delete ptr;
            delete ref_count;
        }
    }

    // Оператор разыменования
    T& operator*() const
    {
        return *ptr;
    }

    // Оператор доступа к члену
    T* operator->() const
    {
        return ptr;
    }

    // Получение сырого указателя
    T* get() const
    {
        return ptr;
    }

    // Проверка на пустоту
    bool operator!() const
    {
        return ptr == nullptr;
    }

    // Получение количества ссылок
    int use_count() const
    {
        return *ref_count;
    }

    // Передача владения
    void reset(T* p = nullptr)
    {
        if (--(*ref_count) == 0)
        {
            delete ptr;
            delete ref_count;
        }
        ptr = p;
        ref_count = (p != nullptr) ? new int(1) : nullptr;
    }
};

// Класс для тестирования
class TestClass
{
public:
    int value;

    TestClass(int v) : value(v)
    {
        cout << "TestClass конструктор, вызываемый со значением: " << v << endl;
    }

    ~TestClass()
    {
        cout << "TestClass деструктор вызывается со значением: " << value << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    // Тестирование MyUniquePtr
    cout << "MyUniquePtr тест:" << endl;
    MyUniquePtr<TestClass> uniquePtr1(new TestClass(10));
    cout << "uniquePtr1 значение: " << uniquePtr1->value << endl;

    MyUniquePtr<TestClass> uniquePtr2(move(uniquePtr1));
    cout << "uniquePtr2 значение: " << uniquePtr2->value << endl;
    // uniquePtr1 is now invalid and should not be used

    uniquePtr2.reset(new TestClass(20));
    cout << "uniquePtr2 значение: " << uniquePtr2->value << endl;

    // Тестирование MySharedPtr
    cout << "MySharedPtr тест:" << endl;
    MySharedPtr<TestClass> sharedPtr1(new TestClass(30));
    cout << "sharedPtr1 значение: " << sharedPtr1->value << endl;
    cout << "sharedPtr1 количество использований: " << sharedPtr1.use_count() << endl;

    MySharedPtr<TestClass> sharedPtr2(sharedPtr1);
    cout << "sharedPtr2 значение: " << sharedPtr2->value << endl;
    cout << "sharedPtr1 количество использований: " << sharedPtr1.use_count() << endl;
    cout << "sharedPtr2 количество использований: " << sharedPtr2.use_count() << endl;

    MySharedPtr<TestClass> sharedPtr3 = sharedPtr2;
    cout << "sharedPtr3 значение: " << sharedPtr3->value << endl;
    cout << "sharedPtr1 количество использований: " << sharedPtr1.use_count() << endl;
    cout << "sharedPtr2 количество использований: " << sharedPtr2.use_count() << endl;
    cout << "sharedPtr3 количество использований: " << sharedPtr3.use_count() << endl;

    sharedPtr1.reset(new TestClass(40));
    cout << "sharedPtr1 значение: " << sharedPtr1->value << endl;
    cout << "sharedPtr1 количество использований: " << sharedPtr1.use_count() << endl;
    cout << "sharedPtr2 количество использований: " << sharedPtr2.use_count() << endl;
    cout << "sharedPtr3 количество использований: " << sharedPtr3.use_count() << endl;

    return 0;
}
