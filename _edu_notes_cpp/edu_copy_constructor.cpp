APR-2015.

Technical questions on the interview. Varian Medical oy

- copy constructor. What is it and why it is ezxist?
http://geeksquiz.com/copy-constructor-in-cpp/

Copy constructor. 


The "copy constructor" is a constructor which creates an object by initializing it with an object of the same class, which has been created previously. The copy constructor is used to:

- Initialize one object from another of the same type.
- Copy an object to pass it as an argument to a function.
- Copy an object to return it from a function.

If a "copy constructor" is not defined in a class, the compiler itself defines one. 
If the class has pointer variables and has some dynamic memory allocations, then it is a must to have a copy constructor. 

The most common form of copy constructor is shown here:

class_name (const class_name &obj) 
{
   // body of constructor
}


______________________
Думаю, главный вопрос, при изучении любой темы по программированию – Зачем?  И на него надо отвечать в первую очередь, а потом уже показывать, как и когда надо применять  те или иные инструменты программирования.

Конструктор копирования нужен нам для того, чтобы создавать "реальные" копии объектов класса, а не побитовую копию объекта. Иногда это принципиально важно. Такую "реальную" копию объекта надо создавать в нескольких случаях:

- когда мы передаем объект в какую-либо функцию в виде параметра;
- когда какая-либо функция должна вернуть объект класса в результате своей работы;
- когда мы в главной функции один объект класса инициализируем другим объектом класса.

Например, мы передаем объект в функцию в виде параметра. Функция будет работать не с самим переданным объектом, а с его побитовой копией. Допустим в конструкторе класса, при создании объекта, выделяется определенный объем памяти, а деструктор класса эту память освобождает. Указатель побитовой копии объекта будет хранить тот же адрес памяти, что и оригинальный объект. И, когда при завершении работы функции и уничтожении побитовой  копии объекта, сработает деструктор, он обязательно освободит память,  которая была занята объектом-оригиналом. В придачу, еще и при завершении работы программы, деструктор сработает повторно и попытается еще раз освободить этот объем памяти, что неизбежно приведет к ошибкам программы. Та же участь постигнет и память, выделенную для указателя объекта, если будет удаляться побитовая копия возвращаемого функцией объекта, и побитовая копия при инициализации объекта класса другим объектом.

Чтобы избежать этих проблем и ошибок существует конструктор копирования. Его работа заключается в том, чтобы создать реальную копию объекта со своей личной выделенной динамической памятью. Синтаксис конструктора копирования следующий:

className (const className & object)
{
    // copy constructor code;
}

Рассмотрим простой пример.

В нем создадим класс, который будет содержать обычный конструктор, конструктор копирования и деструктор. В этом примере будут описаны все три случая для которых надо применять конструктор копирования.  Для того, чтобы пример не был слишком большим, мы не будем заставлять конструкторы выделять память, а деструктор освобождать память. Пропишем в них только вывод определенного сообщения на экран. Таким образом, можно будет посмотреть, сколько раз сработают конструкторы и деструктор. Как вы понимаете, если бы деструктор освобождал память, то количество его вызовов не должно превышать количество вызовов конструкторов.

Пример:

#include <iostream>
using namespace std;

class SomeClass
{
    int *ptr; // pointer to a memory allocation
public:

    SomeClass() //  конструктор
    {
        cout << "\nThis is usual constructor\n";
    }
    SomeClass(const SomeClass &obj)
    {
        cout << "\nThis is a COPY constructor\n";
    }
    ~SomeClass()
    {
        cout << "\nI am destroyer!!!!\n";
    }
};

void funcShow(SomeClass object)
{
    cout << "\nFunction takes object as a parameter\n";
}

SomeClass funcReturnObject()
{
    SomeClass object;
    cout <<   "\nFunction returns an object\n";
    return object;
}

int main()
{
    setlocale(LC_ALL,"rus");

    cout << "1 ~~~~~~~Create a object of a class\n";
    SomeClass obj1;

    cout << "2 ~~~~~~~Pass the object to function\n";
    funcShow(obj1);

    cout << "3 - 4 ~~~this function returns an object\n";
    funcReturnObject();

    cout << "5 ~~~~~~~init an object at time of creation\n";
    SomeClass obj2 = obj1;

}

В строках 4 — 21 определен класс. Обычный конструктор, строки 9 — 12, будет автоматически вызваться при создании новых объектов класса. А конструктор копирования, строки 13 — 16, будет автоматически вызваться при создании копии объекта. Деструктор, строки 17 — 20, вызывается всякий раз когда удаляется либо объект, либо его копия. Ниже определены две функции "funcShow()" и "funcReturnObject()". Первая принимает объект в виде параметра, вторая при вызове во-первых создает новый объект (тут сработает обычный конструктор), а во-вторых возвращает объект (тут сработает конструктор копирования т.к. при возврате объекта из функции создается его временная копия).

Вот какую картинку мы увидим при запуске программы:
1 ~~~~~~~Create a object of a class
This is usual constructor

2 ~~~~~~~Pass the object to function
This is a COPY constructor
Function takes object as a parameter
I am destroyer!!!!

3 - 4 ~~~this function returns an object
This is usual constructor
Function returns an object
This is a COPY constructor
I am destroyer!!!!
I am destroyer!!!!

5 ~~~~~~~init an object at time of creation
This is a COPY constructor
I am destroyer!!!!
I am destroyer!!!!

Пойдем по порядку. В первом блоке сработал обычный конструктор — это произошло при создании объекта класса obj1. Второй блок отображает работу функции funcShow(). Так как при передаче объекта в функцию создается его копия и сработал конструктор копирования. А при завершении работы функции эта копия уничтожается и срабатывает деструктор. Блок 3 — 4 показывает, что при создании нового объекта в функции funcReturnObject() сработал обычный конструктор, а при возврате объекта — конструктор копирования. Деструктор, как положено отработал дважды — для оригинала объекта и для копии. И наконец в пятом блоке срабатывает конструктор копирования при инициализации нового объекта класса. Затем дважды деструктор  - один уничтожает копию объекта пятого блока, второй уничтожает объект из первого блока. Ну как-то так. В итоге количество вызовов деструктора совпадает с вызовами конструкторов.

А теперь попробуйте закомментировать конструктор копирования в определении класса и запустите программу.  Вы увидите, что конструктор сработает только дважды, а деструктор, рад стараться, отработает пять раз. И если бы он освобождал память — это неизбежно  привело бы к ошибке программы.


