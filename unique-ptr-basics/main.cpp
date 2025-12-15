#include <iostream>
#include <memory>
#include <utility>

class Resource
{
  public:
    explicit Resource(int id) : id_(id) { std::cout << "Resource " << id_ << " acquired\n"; }

    ~Resource() { std::cout << "Resource " << id_ << " released\n"; }

    void
    use() const
    {
        std::cout << "Using resource " << id_ << "\n";
    }

  private:
    int id_;
};

// Factory function: returns ownership
std::unique_ptr<Resource>
make_resource(int id)
{
    return std::make_unique<Resource>(id);
}

// Takes ownership explicitly
void
consume_resource(std::unique_ptr<Resource> res)
{
    std::cout << "Consuming resource\n";
    res->use();
    // res is destroyed here
}

// Borrows resource (no ownership transfer)
void
inspect_resource(const Resource& res)
{
    std::cout << "Inspecting resource\n";
    res.use();
}

int
main()
{
    std::cout << "=== create resource ===\n";
    auto r1 = make_resource(1);

    std::cout << "\n=== borrow resource ===\n";
    inspect_resource(*r1);

    std::cout << "\n=== move ownership ===\n";
    auto r2 = std::move(r1);

    if (!r1) {
        std::cout << "r1 no longer owns the resource\n";
    }

    std::cout << "\n=== transfer ownership to function ===\n";
    consume_resource(std::move(r2));

    if (!r2) {
        std::cout << "r2 no longer owns the resource\n";
    }

    std::cout << "\n=== end of program ===\n";
    return 0;
}
