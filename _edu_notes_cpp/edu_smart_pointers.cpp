Smart pointers ��� ����������

��� ��������� ������ � ������ ������� ������������� ��� ���������� C++ �������������, ������� ���� ������� �� ����� ����������, �� ������� �� ���������, ���� ��� ������ ������� �� new-delete.


����, ������������ �++ �����, ��� ������ ����� �����������. ���������� ������. � ��� �����, ��� ���� ���-�� ������� new, ����������� ������ ���� ��������������� delete. �� ������ ����������� � ������� ����� ���� �������, ��������, ���������� ��������:

    - ������ ������;
    - ��������������� �������� ���������, ���� ��������� � ������������������ ������� ������;
    - �������� ��� ���������� �������;

������ � �������� �� ��� ��������, ���� ��������� �� �������� 24/7, ���� ���, �� ����������, �� ��������� � �����. ��� ��������������� �������� ��������� �� �������������� ������� �������, �������� ������ ����� ��� ������ ����� �� ���������� ������� (�� �� ��������� � ��� �). ��� ��������� �������� ����� ��������� ������ ���, ��� ������. ������ (���� ����� ���� � �� ������), ���� ��� ���������� ���� ������, �� ���-�� � ��� �� ��������� ����� ��������, ������������ ���������� ���������� ������. ������ ������� �� �����������, �� ��������, ��� �� �������� 1 �� ������ ������� � ���������� ������. ����� �� ����������� ������ ����� ��������� ����� 1024, ����� ������� ������ ��������� ��� ������ delete ������� ����� 1024 ���� ������, �� ������ � �� ������. ��� ������ ������ delete ��� �������, ��� ������ �� ������� �� �� ������. ����� ����� ����� ��������, ���� ��������� ����������� ��������� ��������� ���� ������, � ���� ��������� ����� ���������.

��������

���������� ������� ���������� ��������� ����������� ��������� ��������, ���������� RAII. �� ����, ��� ��������� ������-���� �������, ��� �������������� � ������������, �, ��������� � ��� � �������, ��������� ����������� � �����������. �������� ����� ���� ��� ������, � ������� ����, ������� ����������, � � ����� ������ ���� ������. ��� ���������� ������:

        class VideoBuffer 
        {
            int *myPixels;
        public:
            VideoBuffer() 
            {
                pixels = new int[640 * 480];
            }
            void makeFrame() 
            { /* �������� � ������� */ }

            ~VideoBuffer() 
            {
                delete [] pixels;
            }
        };
        int game() 
        {
            VideoBuffer screen;
            screen.makeFrame();
        }


��� ������: �� ������ �� ������� ��� �� ����� ���������� �� ������������ ������, ��� ��� ��� ������� screen ��������� ����������, ������� � ���� ������� ��������� ����������������� � ���� ������ ��������. �������, ����� �������� � ���:

        int game() 
        {
            int *myPixels = new int[640 * 480];
            // ��������
            delete [] pixels;
        }


� ��������, ������� �������, �� ���������� ���� ����� ���:

        int game() 
        {
            int *myPixels = new int[640 * 480];
            // ��������
            if (someCondition)
                return 1;        
            // �������� ������    
            if (someCondition)
                return 4;        
            // ����������
            delete [] pixels;
        }

�������� � ������ ����� ������ �� ������� ������ delete [], ���� �������� �����-���� �������������� ������� ���������������. � ���� ��������� ������ �����, ���� ��� ���������� � ������ ������ �������? �������� �� ���� ���� ����� ��� ������� � �������. �������� �������� ���������, ���� �� � �������� ������� ������� ����������: �������������, ��� ������� �� ����� ����� ����������, �� � ����� �������� �������� ��������.
��, ����� ������������ RAII, � ������������� ���������������� ������, � ����������� �����������. � ����� ���� ������ ������ ����� ����������� �� ������� ������������ ������:

        class Foo 
        {
            int *data1;
            double *data2;
            char *data3;
        
            public:
            Foo() 
            {
                data1 = new int(5);
                ...
            }
            ~Foo() 
            {
                delete data1;
                ...
            }
        }


������ �����������, ��� ����� �� 3, � 30, � ������ � ����������� �������� ��� ���� ��� �������� delete. � ���� �� �������� ������� ����� ����, �� ������� ��� ����� � �����������, �� ����������� ����� �����������. � ����� ���������� �����, ����������� ���������� ���������\������������ ������, �� ��� � ���������, ��� �� ���� ��������� �������.
������� ������������ ������������ ����� ���������: ��� �������, ������� ������ ��������� �� ����������� �������������� ������� ������ ������������� ����. ������ ��� ������������� ������� ������ �� ������ �� ������� ���������.
������� ���������� ��, ��� ��� �������� � �++, ����� �������� � ������ ��������� ���������������� ����� ����� ����������.
���������� smart pointer

        // ����� ������ ������ ���������
        template <typename T>
        class smart_pointer 
        {
            T *m_obj;
        public:
            // ������ ��� �� �������� ����� ������
            smart_pointer(T *obj)
                : m_obj(obj)
            { }
            // �� ������ �� ������� ��������� ���� ������ �� ���������
            ~smart_pointer() 
            {
                delete m_obj;
            }
            // ������������� ���������
            // ��������. ��������� ���������� � ������ ���� T ����������� "���������"
            T* operator->() { return m_obj; }
            // � ������� ������ ��������� �� ����� ������������ ��������� � �������� ������ ��
            // ������, ������� �� ������
            T& operator* () { return *m_obj; }
        }
        
        int test 
        {
            // ������ myClass �� �������� ������ ���������
            smart_pointer<MyClass> pMyClass(new MyClass(/*params*/);    
            // ���������� � ������ ������ MyClass ����������� ���������
            pMyClass->something();    
            // ��������, ��� ��� ������ ������ ���� ������� ������ ��� � ostream
            // ��� ������� ����� �� ���������� ������ �������� ������ �� ������,
            // ������� ������ ���� ������� �� �����
            std::cout << *pMyClass << std::endl;    
            // �� ������ �� ������ ������ MyClass ����� ������
         }

�������, ��� ��� ����� ������� �� ����� ����������� (��������, ��� ������� � ��� ������?), �� �� � ������ ���� ��������� ������ RAII. �� ����� ���� ��� ��, ��� � ������� ��������� (��������� ������������� ����������), ������ ��� �� ����� ���������� �� ������������ ������: ��� ����� ������� �������������. �� ������� � ������������� ���������� ����� �������� const, ������������ ������������ ������, �� ������� ��������� ���������.
������, ���� �� ������, ��� ��������� ������������ ������������, ��� ������������� ����� ����������, ���������� �� ���������� ����������. ���� ��� �� �������� ��� ����, �� ��� �����, ���������� ������������ �� � �����-������ ����� ��������� ����������, ������, ��� ������ �����������.
����, ���� �����-��������:

    boost::scoped_ptr
    std::auto_ptr
    std::tr1::shared_ptr (�� �� std::shared_ptr � C++11, ���� boost::shared_ptr �� boost)

    boost::scoped_ptr

�� ��������� � ���������� boost.
���������� ������� � ��������, ����������� ���������� �����, �� ����������� ������������, ���� �� ���: ���� ������� �� ����� ���� ���������� (�� ���� � ���� ��������� ����������� ����������� � �������� ������������). ������ �� �������:

        #include <boost/scoped_ptr.hpp>
        int test() 
        {
            boost::scoped_ptr<int> p1(new int(6));
            boost::scoped_ptr<int> p2(new int(1));    
            p1 = p2; // ������!
        }


��� � �������, ���� �� ���� ��������� ������������, �� � p1 � p2 ����� ��������� �� ���� � �� �� ������� ������. � �� ������ �� ������� ��� ��������. ��� �����? ����� �� �����. ��������������, ���� ������� ������ ���������� � � �������.
����� ����� �� �����? ������� ��������� ��� ��� ���������-������� ��� �����-���� ������, ������� ���������� ����������� � ������ ������� � ��������� � �����, ����� �������� ���� �� �������� ���� �� ������ ���������� ������� ��������.

��������� �������� �����.
std::auto_ptr

����-���� ���������� ������� �����������, � ���� �� �� ���� � ����������� ���������� (���� � C++11 ����� ��� deprecated). � ���� ���� �������� ������������ � �����������-����������, �� �������� ��� ��������� ��������.
�������:

        #include <memory>
        int test() 
        {
            std::auto_ptr<MyObject> p1(new MyObject);
            std::auto_ptr<MyObject> p2;    
            p2 = p1;
        }


������ ��� ������������ � p2 ����� ������ ��������� �� MyObject (������� �� ��������� ��� p1), � � p1 �� ����� ������. �� ���� p1 ������ �������. ��� ��� ���������� ��������� �����������. ������, �������� ����������� ��������� ����� �� �������.
����� ��� �����? �� �������� � ��� ���� �������, ������� ������ ��������� �����-�� ������:

        std::auto_ptr<MyObject> giveMeMyObject();

��� ��������, ��� ������� ������� ����� ������ ���� MyObject � ������ ��� ��� � ������������. �������� ������, ���� ��� ������� ���� �������� ������ ������ (�������� Factory): �� �������, ��� ���� ����� (Factory) �� ������ � ���� ��� ���� ��������� �� ����� ������. ������ ��� � ��������� �� ���� ����.

� ���� ����� ��������� ��������� auto_ptr ������ ������������ � ����������� STL. �� � ��� ���� shared_ptr.
    std::shared_ptr (�++11)

����� ��������� � ��������� ������. ��� ��� ������. ��� ������, ��� ���-�� ���� ����� ����������, ������� ������ ���������� ����������, ������� ��������� �� ������. ���� ��� ���������� ���������� ������ ����, �� ������ ������������. ������� ���������������� ��� ������ ������ ���� ��������� ����������� ���� ��������� ������������. ��� �� � shared_ptr ���� �������� ���������� � bool, ��� � ����� ���� ��� ��������� ��������� ����������, �� �������� �� ������������ ������.

        #include <memory> // ���� <tr1/memory> ��� ������������, ��� �� �������������� C++11
        #include <iostream>
        int test() 
        {
            std::shared_ptr<MyObject> p1(new MyObject);
            std::shared_ptr<MyObject> p2;    
            p2 = p1;    
            if (p2)
            {
                std::cout << "Hello, world!\n";
            }
        }

������ � p2 � p1 ��������� �� ���� ������, � ������� ������ ����� 2, �� ������ �� ������ ������� ����������, � ������ ������������. �� ����� ���������� ���� ��������� � �������:

        int test(std::shared_ptr<MyObject> p1) 
        {
            // ������ ���-��
        }

��������, ���� �� ��������� ��������� �� ������, �� ������� �� ����� ��������. �� ������ ���� �������, ��� ������ MyObject ����� ���, ���� ����� ����������� ������� test.

����, smart pointers ��� ������, �� ���� � ������.
��-������ ��� ��������� �������, �� � ����� � ��� �������� ��������� ������ ���������� ���� ������ ��������.
��-������ ��� boiler-plate, ��������

        std::tr1::shared_ptr<MyNamespace::Object> ptr = std::tr1::shared_ptr<MyNamespace::Object>(new MyNamespace::Object(param1, param2, param3))

��� �������� ����� ������ ��� ������ ��������, ��������:

        #define sptr(T) std::tr1::shared_ptr<T>

���� ��� ������ typedef.

�-�������, ���������� �������� ����������� ������. ������������� �� ����� �� ����, ����� �� ����������� ������. ��� �� �������� ���������������� boost::weak_ptr, boost::intrusive_ptr � ��������� ��� ��������.

������, smart pointers ���������� ������ ������� � ������ ������� � ����� ��++ for real programmers�.
