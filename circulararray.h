#include <iostream>
#include <string>
using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    unsigned int capacity;
    int back, front;
    
public:
    CircularArray();
    CircularArray(int _capacity);
    virtual ~CircularArray();
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    void pop_front();
    void pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void clear();
    T &operator[](int);
    //CircularArray<T> &operator=(CircularArray<T>);
    void sort();
    //T divide(T start, T end);
    bool is_sorted();
    void reverse();
    string to_string(string sep=" ");

private:
    int next(int);
    int prev(int);
};

template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    this->front = this->back = -1;
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = ""; 
    for (int i = 0; i < size(); i++)
        result += std::to_string((*this)[i]) + sep;
    return result;    
}

template <class T>
void CircularArray<T>::push_front(T data){
    if(is_empty()){
        front=back=0;
        array[front]=data;
        return;
    }/*
    else if(is_full()){
        //hacer resize (agregar x espacios extra) y mover los elementos hacia adelante
        auto new_array = new CircularArray<T>(capacity+5);//me decidí por 5 espacios extra
        new_array->front=new_array->back=0;
        new_array[front]=data;
        for(int i=1; i<size(); i++){
            new_array->push_back(array[i]);
        }
        array=new_array;
        delete new_array;
        //return new_array;
    }*/
    else{
        for(int i=back;i>front-1;i--){
            array[next(i)]=array[i];
        }
        array[front]=data;
        back=next(back);
        return;
    }
}
template <class T>
void CircularArray<T>::push_back(T data){
    if (is_empty()){
        front=back=0;
        array[back]=data;
        return;
    }/*
    else if(is_full()) {
        //hacer resize (agregar x espacios extra) y agregar el elemento
        auto new_array = new CircularArray<T>(capacity+5);
        new_array->front=new_array->back=0;
        new_array[back]=data;
        for(int i=size()-2;i>-1;i--){
            new_array->push_front(array[i]);
        }
        array=new_array;
        delete new_array;
        //return new_array;
    }*/
    else {
        array[next(back)] = data;
        back = next(back);
    }
}
template <class T>
void CircularArray<T>::insert(T data, int pos){
    if(is_empty()){
        front=back=0;
        array[front]=data;
        return;
    }
    else if(is_full()){
        //por hacer
        //hacer resize (agregar x espacios extra) y mover los elementos correspondientes hacia adelante
        return;
    }
    else{
        //mover los elementos correspondientes hacia adelante
//        for(int i=back;i>front-1;i--){
//            array[next(i)]=array[i];
//        }
//        array[front]=data;
//        back=next(back);
//        return;
    }
}
template <class T>
void CircularArray<T>::pop_front(){
    for(int i=front;i<back;i++){
        array[i]=array[next(i)];
    }
    array[back]= T(NULL);
    back= prev(back);
}
template <class T>
void CircularArray<T>::pop_back(){
    array[back]= T(NULL);
    back= prev(back);
}
template <class T>
bool CircularArray<T>::is_full(){
    return !is_empty() && front == next(back);
}
template <class T>
bool CircularArray<T>::is_empty(){
    return back == -1;//probar si se puede cambiar front por back
}
template <class T>
int CircularArray<T>::size(){
    if(is_empty()){
        return 0;
    }
    else if(front == back){
        return 1;
    }
    else{
        return (back+1 - front) ;
    }
}
template <class T>
void CircularArray<T>::clear(){
    for(int i=0; i<size()-1; i++){
        pop_front(array[i]);
    }
}
template <class T>
T &CircularArray<T>::operator[](int i){
    return this->array[i];
}/* pensé que tenia que sobrecargar el operador = para alguans partes, pero no me funcionó
template <class T>
CircularArray<T> &CircularArray<T>::operator=(CircularArray<T> other){
    auto new_array = new CircularArray<T>(other.capacity);
    for(int i=1; i<size(); i++){
        new_array->push_back(other[i]);
    }
    delete this;
    return new_array;
//    if (this->capacity() == other.capacity()){
//        for(int i=0; i<capacity; i++){
//            this[i]=other[i];
//        }
//        return this;
//    }
//    else if(this->capacity() == other.capacity()){
//
//    }
}*/
/*
template <class T>
T CircularArray<T>::divide(T start, T end){ //solo es para el quicksort
    T left;
    T right;
    T pivot;
    T temp;

    pivot = array[start];
    left = start;
    right = end;

    // Mientras no se cruzen los índices
    while (left < right) {
        while (array[right] > pivot) {
            right--;
        }

        while ((left < right) && (array[left] <= pivot)) {
            left++;
        }

        // Si todavía no se cruzan los indices seguimos intercambiando
        if (left < right) {
            temp = array[left];
            array[left] = array[right];
            array[right] = temp;
        }
    }

    // Los índices ya se han cruzado, ponemos el pivot en el lugar que le corresponde
    temp = array[right];
    array[right] = array[start];
    array[start] = temp;

    // La nueva posición del pivot
    return right;
}*/
template <class T>
void CircularArray<T>::sort(){
    if (size()==1){
        return;
    }
    else if (is_empty()){
        return;
    }
    else{ //quicksort (no funcionó)
        /*T pivot;
        if (front < back) {
            pivot = divide(front, back);

            // Ordeno la lista de los menores
            sort(front, pivot - 1);

            // Ordeno la lista de los mayores
            sort(pivot + 1, back);
        }*/
        //insertion sort
        for(int i=1; i<size(); i++)
        {
            T temp = array[i];
            int j = i-1;
            while(j>=0 && temp <= array[j])
            {
                array[j+1] = array[j];
                j--;
            }
            array[j+1] = temp;
        }
    }
}
template <class T>
bool CircularArray<T>::is_sorted(){
    for(int i=front;i<back;i++) {
        if (array[i] > array[next(i)]) {
            return false;
        }
    }
    return true;
}
template <class T>
void CircularArray<T>::reverse(){
    throw exception("No me sale :´( F");
//    auto new_array = new CircularArray<T>(capacity);
//    //auto new_array = new T[capacity];
//    for(int i=size()-1;i>-1;i--){
//        new_array->push_back(array[i]);
//    }
//    clear();
//    for(int j=0; j<new_array->size()-1; j++){
//        push_front(new_array[j]);
//    }
    //array=new_array;
    //return new_array;
}
