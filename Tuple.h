

#ifndef PROJECT1_TUPLE_H
#define PROJECT1_TUPLE_H
#include <vector>
#include <string>
using namespace std;

class Tuple {
public:
    vector<string> values;
    bool operator< (const Tuple & other) const
    {
        return values < other.values;
    }
};


#endif //PROJECT1_TUPLE_H
