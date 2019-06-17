#include <iostream>

using namespace std;

class Box {
    private:
        double width;
    public:
        friend void printWidth(Box box); 
        friend class B; 
        void setWidth(double width_) {
            this->width = width_;
        }
};

class B {
    public:
        void printWidth(Box box) {
            cout << box.width << endl;
        }
};


void printWidth(Box box) {
    cout << box.width << endl;
}

int main() {
    Box box;
    B b;
    box.setWidth(100.0);
    printWidth(box);
    b.printWidth(box);
    return 0;
}
