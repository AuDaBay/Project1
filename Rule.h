#ifndef PROJECT1_RULE_H
#define PROJECT1_RULE_H
#include "Predicate.h"
#include <vector>
using namespace std;
class Rule
{
public:
    void setHead(Predicate head);
    void addBody(Predicate body);
    string toString();

    vector<Predicate> bodyPredicates;
    Predicate headPredicate;


};
#endif //PROJECT1_RULE_H
