#ifndef PROJECT1_PARAMETER_H
#define PROJECT1_PARAMETER_H
#include <string>
using namespace std;
/*enum class type{
    ID,
    STRING
};*/
class Parameter
{
public:
    void setString(string input);
    string getVal();
    //type paraType = type::ID;
    //type getType();
private:
    string parameter;



};
#endif //PROJECT1_PARAMETER_H
