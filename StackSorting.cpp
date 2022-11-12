#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

// Node class for dequeue
class Node{
public:
    int data;
    Node * next;
    Node * prev;
    Node(int val){
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};


// dequeue class
class dequeue{
public:
    Node * head;
    Node * tail;

    dequeue(){
        head = nullptr;
        tail = nullptr;
    }

    bool isempty() const{
        return head== nullptr;
    }

    void print() const{
        if (head) {
            Node *temp = head;
            while (temp != nullptr) {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    void pushfront(int val){
        Node * newnode = new Node(val);
        newnode->next = head;
        if (head){
            head->prev = newnode;
        }
        else tail = newnode;
        head = newnode;
    }

    void pushlast(int val){
        Node * newnode = new Node(val);
        newnode->prev =tail;
        if (tail){
            tail->next = newnode;
        }
        else head = newnode;
        tail = newnode;
    }

    int popfront(){
        if (head) {
            Node *todel = head;
            int val = todel->data;
            if (head->next) {
                head = head->next;
                head->prev = nullptr;
            }
            else {
                head = nullptr;
                tail= nullptr;
            }
            delete todel;
            return val;
        }
    }

    int poplast(){
        if (head) {
            Node *todel = tail;
            int val = todel->data;
            if (tail->prev) {
                tail = tail->prev;
                tail->next = nullptr;
            }
            else {
                tail = nullptr;
                head = nullptr;
            }
            delete todel;
            return val;
        }
    }

    int readfront() const{
        if (head)
            return head->data;
        else
            return -1;
    }

    int readlast() const{
        if (tail)
            return tail->data;
        else
            return -1;
    }

};


// print an array
void print(int arr[], int size){
    for (int i =0; i < size; i++) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

// populate an array with random values
void populate(int arr[], int size){
    srand(time(0));

    for (int i =0; i < size; i++) {
        arr[i] = rand();

    }
}

// return sum of an array
int sumarr(const int arr[], int size){
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// return true if an array is sorted
bool sorted(const int * arr, int size){
    for (int i = 1; i < size ; i++) {
        if (arr[i] < arr[i-1]){
            return false;
        }
    }
    return true;
}

// sorts an array using two stacks in approximately O(n) time complexity
void sort(int *arr, int size) {
    dequeue stack1;
    dequeue stack2;

    // calculating mean value of array to make it standard for comparing with elements of array
    // so that the height of both stacks are almost equal
    int mean = sumarr(arr, size)/size;

    // looping through the array once
    for (int i = 0; i < size; i++) {

        // if element is less than or equal to mean
        if (arr[i] <= mean){

            // place of element is on top of stack one
            if (stack1.readfront() < arr[i]){
                stack1.pushfront(arr[i]);
            }

                // place of element is in between stack top and bottom
            else {

                // popping elements from stack until the position for element is reached
                while (stack1.readfront() > arr[i]){
                    stack2.pushfront(stack1.popfront());
                }

                // putting the element
                stack1.pushfront(arr[i]);

                // putting the popped elements back on stack
                while (stack2.readfront() < mean and stack2.readfront() != -1){
                    stack1.pushfront(stack2.popfront());
                }
            }
        }

            // if the elements is greater than mean
        else {

            // place of element is on top of stack one
            if (stack2.readfront() > arr[i] or stack2.readfront()==-1){
                stack2.pushfront(arr[i]);
            }

                // place of element is in between stack top and bottom
            else {
                // popping elements from stack until the position for element is reached
                while(stack2.readfront() < arr[i] and stack2.readfront() != -1){
                    stack1.pushfront(stack2.popfront());
                }

                // putting the element
                stack2.pushfront(arr[i]);

                // putting the popped elements back on stack
                while (stack1.readfront() > mean){
                    stack2.pushfront(stack1.popfront());
                }
            }
        }

        //cout<<"S1  :  ";stack1.print();
        //cout<<"S2  :  ";stack2.print();
        //cout<<endl;
    }

    // popping elements of stack 1 to stack 2
    while (stack1.readfront()!=-1){
        stack2.pushfront(stack1.popfront());
    }

    // popping elements from stack 2 to array
    for (int i = 0; i < size; i++) {
        arr[i] = stack2.popfront();
    }
}


int main(){

    int size = 500;
    int array[size];

    populate(array, size);
    cout<<"Given array "<<endl;
    print(array, size);
    cout<<endl;

    sort(array, size);
    print(array, size);
    cout<<endl;


    cout<<"Is array sorted : ";
    cout<<sorted(array, size);

    return 0;
}
