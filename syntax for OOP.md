### Inheritance and Abstract class, and Polymophsim
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
    void fly() override {
        cout << "duck fly " << fly_time << " secs" << endl;
    }
};
class pigeon : public bird {
public:
    pigeon(int _fly_time) : bird(_fly_time) {}
    void fly() override {
        cout << "pigeon fly " << fly_time << " secs" << endl;
    }
};
int main() {
    // will print:
    // duck eat
    // duck fly 10 secs
    // 3
    duck duck_instance(3, 10);
    duck_instance.eat();
    duck_instance.fly();
    cout << duck_instance.get_weight() << endl;
    
    // polymorphism 
    pigeon pigeon(300);
    bird* bird_pointer = nullptr;
    
    // will print pigeon fly 300 secs
    bird_pointer = &pigeon;
    bird_pointer -> fly();

    // will print duck fly 10 secs
    bird_pointer = &duck_instance;
    bird_pointer -> fly();
}
```
### interface
C++ doesn't have an interface like in Java, so declare all methods to virtual makes it to be an 'interface'.
