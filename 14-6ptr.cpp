#include <vector>
#include <cstring>
#include "ptr.h"

using std::istream;
using std::ostream;
using std::back_inserter;
using std::copy;
using std::strlen;
using std::cout;
using std::cin;
using std::endl;

// Ch. 14 Function definitions
//Function definitions
template <class T> T* clone (const T* tp)
{
    return tp->clone();
}

template<>
Vec<char>* clone(const Vec<char>* vp)
{
    return new Vec<char>(*vp);
}

