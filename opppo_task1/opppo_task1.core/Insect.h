#include <string>
#include <vector>

#include "Animal.h"

class Insect : public Animal
{
public:
    float size = 0;

    std::string dateOfOpening;

    void PrintObj() override;

    bool MatchObj(std::vector<std::string> command) override;

    static void AddToArray(std::vector<std::string>& tokens, std::vector<std::unique_ptr<Animal>>& array);
};