#include <iostream>
#include <cassert>
#include "smart_ptr.h"

struct Test
{
    int x;
    Test(int v) : x(v) { std::cout << "Test(" << x << ") constructed\n"; }
    ~Test() { std::cout << "Test(" << x << ") destroyed\n"; }
};

int
main()
{
    std::cout << "--- Testing SharedPtr ---\\n";
    {
        SharedPtr<Test> sp1(new Test(10));
        assert(sp1->x == 10);
        assert(sp1.use_count() == 1);

        {
            SharedPtr<Test> sp2 = sp1;
            assert(sp2->x == 10);
            assert(sp1.use_count() == 2);
            assert(sp2.use_count() == 2);
        }
        assert(sp1.use_count() == 1);
    }
    std::cout << "SharedPtr test passed.\n";

    std::cout << "--- Testing MakeShared ---\\n";
    {
        SharedPtr<Test> sp = MakeShared<Test>(20);
        assert(sp->x == 20);
        assert(sp.use_count() == 1);
    }
    std::cout << "MakeShared test passed.\n";

    std::cout << "--- Testing WeakPtr ---\\n";
    {
        SharedPtr<Test> sp = MakeShared<Test>(30);
        WeakPtr<Test> wp = sp;
        assert(!wp.expired());

        SharedPtr<Test> sp2 = wp.lock();
        assert(sp2);
        assert(sp2->x == 30);
        assert(sp.use_count() == 2);

        sp2 = nullptr; // release one reference
        assert(sp.use_count() == 1);

        sp = nullptr; // release last reference
        assert(wp.expired());
        assert(wp.lock().get() == nullptr);
    }
    std::cout << "WeakPtr test passed.\n";

    return 0;
}
