### Inheritance and Abstract class
```cpp
class animal {
private:
    int weight;
public:
    animal(int _weight) : weight(_weight) {}
    virtual void eat() = 0; // set 0 so the class becomes abstract class and the method must be implemented by child class
    // if there's an implementation then the child class can choose implement it or not
    // virtual void eat() {cout << "animal eat" << endl;}
    virtual int get_weight() {
        return weight;
    }
};
class bird {
public:
    int fly_time;
    bird(int _fly_time) : fly_time(_fly_time) {}
    virtual void fly() {
        cout << "fly " << fly_time << " secs" << endl;
    }
};
// the syntax for inherits multiple classes
class duck : public animal, public bird { // when inherits as public, all parent class's access right kept not changed(private still private, public still public etc)
public:
    duck(int _weight, int _fly_time) : animal(_weight), bird(_fly_time) {}
    void eat() override {
        cout << "duck eat" << endl;
    }
};

// will print:
// duck eat
// fly 10 secs
// 3
int main() {
   duck duck_instance(3, 10);
   duck_instance.eat();
   duck_instance.fly();
   cout << duck_instance.get_weight() << endl;
}
```
