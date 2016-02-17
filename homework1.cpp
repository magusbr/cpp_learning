/* Convert this program to C++
* change to C++ io
* change to one line comments
* change defines of constants to const
* change array to vector<>
* inline any short function
*/

#include <iostream>
#include <algorithm>
#include <vector>

namespace homework1
{

using namespace std;

// const instead of #define
const int N = 40;

// inlined template sum function will need += operator from class T
// will sum initial value from T with values from vector<T>
template<class T>
inline void sum(T& accum, vector<T>& d)
{
    // C++11 range-based for loop
    for(auto i : d)
        accum += i;
}

int main()
{
    // declarations
    // from array to vector
    int accum = 0;
    vector<int> data(N);

    // i variable declared locally
    for(int i = 0; i < N; ++i)
        data[i] = i;

    // size is not needed, since it is inside class
    sum(accum, data);

    // C++ IO
    cout << "sum is " << accum << endl;

    return 0;
}




} //namespace
