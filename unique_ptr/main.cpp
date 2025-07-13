#include <iostream>
#include <memory>

class Resource {
public:
    explicit Resource(const std::string& name) : name_(name) {
        std::cout << "Resource '" << name_ << "' acquired\n";
    }
    ~Resource() {
        std::cout << "Resource '" << name_ << "' released\n";
    }
    void use() const {
        std::cout << "Using resource '" << name_ << "'\n";
    }
private:
    std::string name_;
};

// Function that takes ownership of a Resource
void processResource(std::unique_ptr<Resource> res) {
    if (res) {
        std::cout << "Processing the resource...\n";
        res->use();
    } else {
        std::cout << "No resource to process.\n";
    }
    // When 'res' goes out of scope here, the Resource it owns will be automatically deleted.
}

// Function that takes a reference to a Resource (does not take ownership)
void inspectResource(const Resource& res) {
    std::cout << "Inspecting the resource...\n";
    res.use();
}

// g++ -std=c++11 main.cpp -o /tmp/smart_pointers && /tmp/smart_pointers
int main() {
    // Create a unique_ptr owning a Resource
    std::unique_ptr<Resource> myResource(new Resource("File"));

    // Pass ownership to processResource. After this call, myResource will be empty.
    processResource(std::move(myResource));
    std::cout << "After processResource, myResource is " << (myResource ? "not null" : "null") << "\n";

    // Create a new unique_ptr
    std::unique_ptr<Resource> anotherResource(new Resource("Database Connection"));

    // Pass a reference to inspectResource. Ownership remains with anotherResource.
    if (anotherResource) {
        inspectResource(*anotherResource);  // Dereference a pointer to get a reference
        anotherResource->use();             // anotherResource still owns the object
    }

    return 0;
}