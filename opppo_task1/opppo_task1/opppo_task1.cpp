#include "../opppo_task1.core/Parser.h"

int main()
{
    std::cout << "Text command parsing with .txt file" << std::endl;

    try
    {
        Parser::ParseTxt("parsed.txt");
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Warning: " << e.what() << std::endl;
        return -1;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Warning: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}