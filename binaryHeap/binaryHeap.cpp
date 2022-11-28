#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct DynamicArray {

    int size{};
    int capacity{ 1 };
    T* array = new T[capacity];

    void insert(T data) {
        if (size == capacity) {

            capacity *= 2;

            T* tmp_array = new T[capacity];

            for (int i = 0; i < size; i++)
                tmp_array[i] = array[i];

            delete[] array;
            array = tmp_array;

        }

        array[size] = data;
        size++;

    }

    T* get(int index) {

        if (index < size) {
            return &array[index];
        }
        else {
            throw out_of_range("Błędny zakres");
        }

    }

    T operator[](int index) {
        if (index < size) {
            return array[index];
        }
        else {
            throw out_of_range("Błędny zakres");
        }
    }

    void change(int index, T newData) {

        if (index < size) {
            array[index] = newData;
        }
        else {
            throw out_of_range("Błędny zakres");
        }

    }

    void swap(int i1, int i2) {
        T tmp = array[i1];
        array[i1] = array[i2];
        array[i2] = tmp;
    }

    void clear() {
        delete[] array;
        size = 0;
        capacity = 10;
        array = new T[capacity];
    }

    void remove() {
        --size;
    }

    string str(string(*func)(T so), int k) {

        if (k == -1 || k > size)
            k = size;

        string s = "Actual size : " + to_string(size) + "\nCapacity : " + to_string(capacity) + "\n";

        for (int i = 0; i < k; i++) {
            s += func(array[i]);
        }

        s += '\n';

        return s;

    }

    int getSize() {
        return size;
    }
};

struct simple_object {

    string first_name;
    string second_name;
    int age;

    friend ostream& operator<<(ostream& os, simple_object so);

};

string so_str(simple_object so) {
    return "First name: " + so.first_name + "; second name: " + so.second_name + "; age: " + to_string(so.age) + "\n";
}


int simple_object_comparator(simple_object* so1, simple_object* so2) {
    if (so1->age == so2->age)
        return 0;
    else if (so1->age < so2->age)
        return -1;
    else if (so1->age > so2->age)
        return 1;
}

ostream& operator<<(ostream& os, simple_object so) {
    os << "First name: " << so.first_name << "; second name: " << so.second_name << "; age: " << so.age << "\n";
    return os;
}



template <typename T>
struct BinaryHeap {
    DynamicArray<T>* heap_array = new DynamicArray<T>();

    int parent(int i) {
        i++;
        return (i >> 1) - 1;
    }
    int left_child(int i) {
        i++;
        return (i << 1) - 1;
        //return i * 2 - 1;
    }
    int right_child(int i) {
        i++;
        return (i << 1) ;
    }

    void insert(T data, int (*func)(T*, T*)) {
        heap_array->insert(data);
        int el_index = heap_array->getSize() - 1;

        //cout << heap_array->array[el_index];
        //cout << heap_array->get(el_index);
        //cout << &heap_array[el_index];
        //cout << func(heap_array->get(el_index), heap_array->get(parent(el_index)));

        //while (func(heap_array->get(el_index), heap_array->get(parent(el_index))) == 1 && el_index > 0) {
        //    heap_array->swap(el_index, parent(el_index));
        //    el_index = parent(el_index);
        //}
        heapUp(el_index, func);
    }

    void heapUp(int el_index, int (*func)(T*, T*)) {
        if (func(heap_array->get(el_index), heap_array->get(parent(el_index))) == 1 && el_index > 0) {
            heap_array->swap(el_index, parent(el_index));
            heapUp(parent(el_index), func);
        }
        //while (func(heap_array->get(el_index), heap_array->get(parent(el_index))) == 1 && el_index > 0) {
        //    heap_array->swap(el_index, parent(el_index));
        //    el_index = parent(el_index);
        //}
    }

    string str(string(*func)(T), int k=-1) {
        return heap_array->str(func, k);
    }

    void clear() {
        heap_array->clear();
    }

    T poll(int (*func)(T*, T*)) {
        if (heap_array->getSize() == 0)
            throw std::invalid_argument("nie istnieje");

        T max_element = *heap_array->get(0);
        heap_array->change(0, *heap_array->get(heap_array->getSize() - 1));
        heap_array->remove();
        heapDown(0, func);
        return max_element;
    }

    void heapDown(int el_index, int (*func)(T*, T*)) {
        int l_child_index = left_child(el_index);
        int r_child_index = right_child(el_index);

        if (l_child_index < heap_array->getSize() && r_child_index < heap_array->getSize()) {
            if (func(heap_array->get(l_child_index), heap_array->get(r_child_index)) == 1)
            {
                if (func(heap_array->get(l_child_index), heap_array->get(el_index)) == 1) {
                    heap_array->swap(l_child_index, el_index);
                    heapDown(l_child_index, func);
                }
            }
            else if(func(heap_array->get(l_child_index), heap_array->get(r_child_index)) == -1) {
                if (func(heap_array->get(r_child_index), heap_array->get(el_index)) == 1) {
                    heap_array->swap(r_child_index, el_index);
                    heapDown(r_child_index, func);
                }
            }
        }
        else if (l_child_index < heap_array->getSize()) {
            if (func(heap_array->get(l_child_index), heap_array->get(el_index)) == 1) {
                heap_array->swap(l_child_index, el_index);
                heapDown(l_child_index, func);
            }
        }
        else if (r_child_index < heap_array->getSize()) {
            if (func(heap_array->get(r_child_index), heap_array->get(el_index)) == 1) {
                heap_array->swap(r_child_index, el_index);
                heapDown(r_child_index, func);
            }
        }

        //int l_child_index = left_child(el_index);
        //int r_child_index = right_child(el_index);

        //int largest;
        //if (l_child_index < heap_array->getSize() && func(heap_array->get(l_child_index), heap_array->get(el_index)) == 1)
        //    largest = l_child_index;
        //else
        //    largest = el_index;

        //if (r_child_index < heap_array->getSize() && func(heap_array->get(r_child_index), heap_array->get(largest)) == 1)
        //    largest = r_child_index;

        //if (el_index != largest) {
        //    heap_array->swap(el_index, largest);
        //    heapDown(largest, func);
        //}
    }
};


int main()
{
    int (*cmp)(simple_object *, simple_object *) = simple_object_comparator;


    //BinaryHeap<simple_object>* bh = new BinaryHeap<simple_object>();
    //bh->insert({ "Krystian", "Szabat", 21 }, simple_object_comparator);
    //bh->insert({ "Krystian", "Szabat", 19 }, simple_object_comparator);
    //bh->insert({ "Krystian", "Szabat", 69 }, simple_object_comparator);
    //bh->insert({ "Krystian", "Szabat", 5 }, simple_object_comparator);
    //bh->insert({ "Krystian", "szabat", 1 }, simple_object_comparator);
    //bh->insert({ "Krystian", "Szabat", 6 }, simple_object_comparator);
    //bh->insert({ "Krystian", "Szabat", 10 }, simple_object_comparator);
    //bh->insert({ "Krystian", "Szabat", 99 }, simple_object_comparator);
    //bh->insert({ "Krystian", "Szabat", 19 }, simple_object_comparator);
    //bh->insert({ "Krystian", "Szabat", 56 }, simple_object_comparator);
    //bh->clear();
    //try {
    //    bh->poll(cmp);
    //}
    //catch (const std::invalid_argument& e) {
    //    cout << "eoo";
    //}
    //bh->poll(cmp);
    //bh->poll(cmp);
    //bh->poll(cmp);
    //bh->poll(cmp);
    //bh->poll(cmp);
    //bh->poll(cmp);
    //bh->poll(cmp);
    //bh->poll(cmp);
    //bh->poll(cmp);
    //bh->poll(cmp);
//    try {
//    bh->poll(cmp);
//}
//catch (const std::invalid_argument& e) {
//    cout << "eoo";
//}
    //bh->poll(cmp);
//        try {
//    bh->poll(cmp);
//}
//catch (const std::invalid_argument& e) {
//    cout << "eoo";
//}
//    cout << bh->str(so_str);


    const int MAX_ORDER = 7;
    BinaryHeap<simple_object>* bh = new BinaryHeap<simple_object>();
    srand(time(NULL));

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o);
        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            bh->insert({ "krkud", "edsfsf", rand() % 300 }, cmp);
        }
        clock_t t2 = clock();
        cout << "\nCzas dodawania: " << static_cast<double>(t2 - t1) / CLOCKS_PER_SEC << '\n';
        cout << bh->str(so_str, 10);

        t1 = clock();

        for (int i = 0; i < n; i++) {
            simple_object so = bh->poll(cmp);
        }

        t2 = clock();

        cout << "\nCzas usuwania: " << static_cast<double>(t2 - t1) / CLOCKS_PER_SEC << '\n';
        cout << bh->str(so_str);

        bh->clear();
    }

    delete bh;
}
