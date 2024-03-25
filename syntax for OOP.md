### Inheritance and Abstract class
```cpp
class animal {
public:
    int weight;
    animal(int _weight) : weight(_weight) {}
    virtual void eat() = 0; // set 0 so the class becomes abstract class and the method must be implemented by child class
    // if there's an implementation then the child class can choose implement it or not
    // virtual void eat() {cout << "animal eat" << endl;}
};
class bird {
public:
    int fly_time;
    bird(int _fly_time) : fly_time(_fly_time) {}
    virtual void fly() {
        cout << "fly " << fly_time << " secs" << endl;
    }
};
class duck : public animal, public bird { // the syntax for inherits multiple classes
public:
    duck(int _weight, int _fly_time) : animal(_weight), bird(_fly_time) {}
    void eat() override {
        cout << "duck eat" << endl;
    }
};

int main() {
   duck d(3, 10);
   d.eat();
   d.fly();
}
```
