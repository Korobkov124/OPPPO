#include "Animal.h"

class Fish : public Animal
{
public:
    enum placeEnum
    {
        placeEnumDefault = 0,
        river = 1,
        lake = 2,
        sea = 3
    };

    placeEnum livingPlace = placeEnumDefault;

    void PrintObj() override;

    bool MatchObj(std::vector<std::string> command) override;

    static void AddToArray(std::vector<std::string>& tokens, std::vector<std::unique_ptr<Animal>>& array);
};