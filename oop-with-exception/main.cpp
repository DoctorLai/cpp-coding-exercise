/**
This example creates two classes A and B, where class B is a member of class A.
And in the constructor of class A, it prints a message and throws an exception.
So what would be the output?

B's constructor called.
A's constructor called.
B's destructor called.
Caught exception: Exception in A's constructor

If an exception leaves a constructor, the object’s destructor does not run, because the object never finished
construction. But destructors for already-constructed members/base-subobjects do run.
*/

#include <iostream>
#include <stdexcept>

class B
{
  public:
    B() { std::cout << "B's constructor called." << std::endl; }
    ~B() { std::cout << "B's destructor called." << std::endl; }
};

class A
{
  private:
    B b; // Member of class B
  public:
    A()
    {
        std::cout << "A's constructor called." << std::endl;
        throw std::runtime_error("Exception in A's constructor");
    }
    ~A() { std::cout << "A's destructor called." << std::endl; }
};

int
main()
{
    try {
        A a; // Attempt to create an instance of A
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}
