#include <iostream>
using namespace std;
class Apple{
public:
    Apple(){
        cout << "Apple()" << endl;
    }
    ~Apple(){
        cout << "~Apple()" << endl;
    }
};
int main(){
    cout << "main() begin!" << endl;
    {
        Apple apple; 
    }
    cout << "main() end!" << endl;
}
