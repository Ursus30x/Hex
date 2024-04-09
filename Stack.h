
/*
    Nazewnictwo oraz struktura stosu jest inspirowana stl_stack, 
    a jej opis brany jest z strony https://cplusplus.com/reference/stack/stack/
*/

typedef unsigned int SIZE;

#include <iostream>

template <typename T> class Stack{
    template <typename DataType> struct StackItem{
        DataType data;
        StackItem *next;
    };
    SIZE stackSize;
    StackItem <T> *topItem;
public:
    Stack();
    Stack(const Stack <T> &org);
    bool empty() const;
    SIZE size() const;
    void printStack() const;
    const T& top() const;
    T& top();
    void push(const T &data);
    void push(T &&data);
    void pop();
    
    ~Stack();
};

template <typename T>
Stack<T>::Stack(){
    stackSize = 0;
    topItem = nullptr;
}

template <typename T>
Stack<T>::Stack(const Stack <T> &org )
: stackSize(org.stackSize), topItem(new StackItem <T>){
    StackItem <T> *ptr = topItem;
    StackItem <T> *orgPtr = org.topItem;
    for(std::size_t i = 0;i<stackSize;i++){
        ptr->data = orgPtr->data;
        
        ptr->next = new  StackItem <T>;
        ptr = ptr->next;
        orgPtr = orgPtr->next;
    }
}

template <typename T>
void Stack<T>::printStack() const{
    if(stackSize == 0)return;
    StackItem <T> *ptr = topItem;
    while(ptr != nullptr){
        printf("%d ",ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}


template <typename T>
bool Stack<T>::empty() const{
    return !stackSize;
}

template <typename T>
SIZE Stack<T>::size() const{
    return stackSize;
}

template <typename T>
const T& Stack<T>::top() const{
    return topItem->data;
}

template <typename T>
T& Stack<T>::top(){
    return topItem->data;
}

template <typename T>
void Stack<T>::push(const T &data){
    stackSize++;
    if(topItem == nullptr){
        topItem = new StackItem <T>;
        topItem->data = data;
        topItem->next = nullptr;
        return;
    }

    StackItem <T> *newTop = new StackItem <T>;
    newTop->data = data;
    newTop->next = topItem;
    
    topItem = newTop;
}

template <typename T>
void Stack<T>::push(T &&data){
    stackSize++;
    if(topItem == nullptr){
        topItem = new StackItem <T>;
        topItem->data = std::move(data);
        topItem->next = nullptr;
        return;
    }

    StackItem <T> *newTop = new StackItem <T>;
    newTop->data = std::move(data);
    newTop->next = topItem;
    
    topItem = newTop;
}

template <typename T>
void Stack<T>::pop(){
    if(topItem == nullptr)return;
    stackSize--;
    StackItem <T> *temp = topItem;
    topItem = topItem->next;
    delete temp;
}


template <typename T>
Stack<T>::~Stack(){
    if(stackSize == 0)return;

    StackItem <T> *tempPtr;
    while(topItem->next != nullptr){
        tempPtr = topItem->next;
        delete topItem;
        topItem = tempPtr;
    }

    delete topItem;

}
