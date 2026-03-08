#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;


template <typename T>
class Deque {
public:
    
    Deque() {}
    
    bool Empty () const {
        return head.empty() && tail.empty();
    }
    
    size_t Size() const {
        return head.size() + tail.size();
    }
    
    void PushFront (const T& d) {
        tail.push_back(d);
    }
    
    void PushBack (const T& d) {
        head.push_back(d);
    }
    
    T& operator[](size_t index) {
        if(index >= tail.size()) {
            return head[index - tail.size()];
        }
        return tail[tail.size() - 1 - index];
    }
    
    const T& operator[](size_t index) const {
        if(index >= tail.size()) {
            return head[index - tail.size()];
        }
        return tail[tail.size() - 1 - index];
    }
    
    T& At (size_t index) {
        if(index >= head.size() + tail.size()) {
            throw out_of_range("lol");
        }
        if(index >= tail.size()) {
            return head[index - tail.size()];
        }
        return tail[tail.size() - 1 - index];
    }
    
    const T& At (size_t index) const {
        if(index >= head.size() + tail.size()) {
            throw out_of_range("lol");
        }
        if(index >= tail.size()) {
            return head[index - tail.size()];
        }
        return tail[tail.size() - 1 - index];
    }
    
    void PrintDeque() {
        for(auto it = tail.end() - 1; it >= tail.begin(); it--) {
            cout << *it << ' ';
        }
        for(const auto& x : head) {
            cout << x << ' ';
        }
        cout << endl;
    }
    
    const T& Front() const {
        if(tail.empty()) {
            return head.front();
        }
        return tail.back();
    }
    
    T& Front() {
        if(tail.empty()) {
            return head.front();
        }
        return tail.back();
    }
    
    const T& Back() const {
        if(head.empty()) {
            return tail.front();
        }
        return head.back();
    }
    
    T& Back() {
        if(head.empty()) {
            return tail.front();
        }
        return head.back(); 
    }
    
    
    
private:
    vector<T> tail;
    vector<T> head;
    
};

int main() {
    
    Deque<int> d;
    d.PushFront(2);
    d.PushFront(1);
    d.PushBack(3);
    d.PushBack(4);
    d.PrintDeque();
    
    
  //cout << d.Front() << endl;
  //cout << d.Back() << endl;
  
  //cout << d[0] << " " << endl;
  //cout << d[1] << " " << endl;
  //cout << d[2] << " " << endl;
  //cout << d[3] << " " << endl;
  
  
  cout << d.At(0) << " " << endl;
  cout << d.At(3) << " " << endl;
  //cout << d.At(5) << " " << endl;
  cout << d.At(1) << " " << endl;
    
    

    
    return 0;
}






