// QuestionableCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cassert>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

// TODO: You are going to compare the warnings & errors between Visual Studio and CppCheck.
//  Make sure you are using CppCheck 2.1 or greater
//
//  1. Create a Visual Studio Console project with this file as the only file
//  2. Compile it and check the warning and errors
//  3. Create a CppCheck project to analyze a Visual Studio project with this file.
//  4. In CppCheck Edit / Preferences / General Tab: Set Display error id in column "Id", Enable inline suppressions, and Check for inconclusive errors also
//  5. In CppCheck View, Select Check All to ensure all types of checks are enabled
//  6. In CppCheck Analyze, set the C++ Standard to C++17, and Enforce C++
//  7. Make sure to run the analysis
//  8. Save the results to a file (XML format)
//  9. Take a screen shot of the Visual Studio Error list (all errors, warnings, and messages)
//  10. Identify all messages from CppCheck NOT identified in Visual Studio.
//      For each message not in both:
//        Identify the risk as: RISK or NOT RISK
//        Identify which system (Visual Studio or CppCheck) found the issue
//        Provide a couple of sentences describing the issue found

class TypeManager
{
    std::set<int> typedefs;
    bool is_type(int type) const
    {
        if (typedefs.find(type) != typedefs.end())
        // BUG: Endless recursion. Calling is_type(type) inside itself 
        // with the exact same argument will cause a stack overflow.
            return is_type(type); // BUG: endless recursion
        return false;
    }
};

//Example of class with fixed endless recursion bug to protect the database by changing the return is_type(type); to return true;
//finding type inside the typedefs means the condition is met and the function would return 2.
class TypeManager2 {
    std::set<int> typedefs;

public:
    bool is_type(int type) const {
        // If the type is found in the set, return true
        if (typedefs.find(type) != typedefs.end()) {
            return true; 
        }
        
        return false;
    }
};

class NonCopyableContainer
{
    int internal_value;
    // WARNING: User-defined copy constructor that completely hides/disables 
    // the default constructor, and leaves 'internal_value' uninitialized upon copying.
    NonCopyableContainer(const NonCopyableContainer& other) {}
};

class MySpecialType
{
public:
    int MyVal = 1;

    // BUG: Violates the 'noexcept' specification. If an exception escapes 
    // a noexcept function, std::terminate() is called immediately.
    void DontThrow() noexcept
    {
        throw "Ha! I threw anyway!";
    }
};

void foo(int** output_pointer)
{
    int local_stack_value = 1;
    // BUG: Dangling pointer / Undefined Behavior. 
    // You are assigning the address of a local variable ('local_stack_value') to '*output_pointer'. 
    // When this function returns, 'local_stack_value' goes out of scope and the pointer becomes invalid.
    *output_pointer = &local_stack_value;
}

void work_with_arrays(int count)
{
    int buf[10];
    if (count == 1000)
    // BUG: Out-of-bounds array access (Buffer Overflow).
    // 'buf' only has 10 elements (0-9). Accessing index 1000 is severe undefined behavior.
        buf[count] = 0; // <- ERROR
}

//Example of method fixed for buffer overflow error by ensuring the count can't be more than the array size.
void work_with_arrays2(int count) { 
    int buf[10]; 
    
    // Check if the count is a valid index within the 0-9 range
    if (count >= 0 && count < 10) { 
        buf[count] = 0; 
    } 
}

void do_something_useless()
{
    int sum = 0;
    for (auto i = 0; i < 1000; ++i)
    {
        sum += i;
    }

    std::cout << "I summed up " << sum << " as the answer." << std::endl;
}

void vector_test()
{
    std::vector<int> items;
    items.push_back(1);
    items.push_back(2);
    items.push_back(3);
    std::vector<int>::iterator iter;
    for (iter = items.begin(); iter != items.end(); ++iter) {
        if (*iter == 2) {
            // BUG: Iterator invalidation. 
            // 'items.erase(iter)' invalidates the current iterator. 
            // Incrementing '++iter' in the loop header after erasing causes undefined behavior.
            // Correct way: iter = items.erase(iter); and skip '++iter' for that iteration.
            items.erase(iter);
        }
    }
}

int global_calculation_result;
bool my_function()
{
    global_calculation_result = 1 + 2;
    // WARNING: Implicit type conversion from 'int' (3) to 'bool' (true). 
    // This function returns 'true', not the integer 3.
    return global_calculation_result;
}

struct Token
{
    Token* next() { return nullptr; }
};

int foo(Token* tok)
    // BUG: Infinite loop / Null pointer dereference.
    // If 'tok' is not null, 'while (tok);' creates an infinite loop because 'tok' never changes.
    // If it did break, the next line tries to run, but the semicolon means it is outside the loop.
{
    while (tok);
    tok = tok->next();

    return 0;
}

int main()
{
    std::vector<int> counts{ 1, 2, 3, 5 };
    int x = 0;
    int y = 0;
    int z = 0;

    std::cout << "Welcome to the Questionable Code Test!" << std::endl;

    //do_something_useless();

    work_with_arrays(10);
    
    work_with_arrays2(10);

    // BUG: Using assignment '=' instead of comparison '=='.
    // This assigns 2 to 'z', evaluates to 2 (which is truthy), so the assert always passes.
    assert(z = 2);

    // BUG: This assertion will FAIL. 
    // 'my_function()' returns a boolean 'true' (which equals 1). 1 == 3 evaluates to false.
    assert(my_function() == 3);

    try
    {
        int x = 5;
        int y = 5;
        int z = 5;
        std::cout << "x + y + z = " << (x + y + z) << std::endl;
    }
    catch (...)
    {

    }

    int* dangling_output_ptr;
    // Passes the address of 'dangling_output_ptr'. Inside 'foo', 'dangling_output_ptr' gets assigned a dead local address.
    foo(&dangling_output_ptr);
    // Using 'dangling_output_ptr' here would now result in undefined behavior.

    // Triggers iterator invalidation bug.
    vector_test();

    MySpecialType myobject;
    std::cout << "myobject.MyVal = " << myobject.MyVal << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu