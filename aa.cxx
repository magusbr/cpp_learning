#include <iostream>
#include <string>
#include <cstddef>

using namespace std;

typedef enum days {SUN, MON, TUE, WED, THU, FRI, SAT} days;

inline days operator+ (days d)
{
    return static_cast<days>((static_cast<int>(d)+1) % 7);
}

ostream& operator<<(ostream& out, days d)
{
    switch(d)
    {
        case SUN: out << "SUN"; break;
        case MON: out << "MON"; break;
        case TUE: out << "TUE"; break;
        case WED: out << "WED"; break;
        case THU: out << "THU"; break;
        case FRI: out << "FRI"; break;
        case SAT: out << "SAT"; break;
    }

    return out;
}

template<class T> T sum (T x, T y)
{
    return x + y;
};

int main(int argc, char** argv)
{
    string i = sum(string("a"), string("b"));
    int j = sum(2, 3);
    cout << "teste: " << i << endl;

    days d = SAT;
    days e = +d;
    cout << e << endl;

    int* ptr = new int(nullptr);
}