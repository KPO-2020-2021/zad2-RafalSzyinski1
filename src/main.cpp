#include "complex.h"
#include "database.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Open program with flag (trudny | latwy)" << std::endl;
        std::cerr << "Example: " << argv[0] << " latwy" << std::endl;

        return -1;
    }

    std::string diff = argv[1];
    database db(diff);

    if (!db.is_open())
    {
        std::cerr << "Can't open file" << std::endl;
        return -1;
    }

    while(!db.eof())
    {
        if (!db.next_equation())
            continue;


        db.print_equation();
        complex<double> answer = db.get_answer();
        complex<double> user_answer;

        int i;
        for (i = 1; i < 4; ++i)
        {
            std::cout << "Give the answer " << i << ": ";

            try
            {
                std::cin >> user_answer;

            }
            catch (std::exception& e)
            {
                std::cout << e.what() << std::endl;
                std::cout << "Try again" << std::endl;

                std::cin.clear();
                while (std::cin.get() != '\n')
                    continue;

                continue;
            }

            break;
        }

        if (user_answer == answer)
            std::cout << "Good answer" << std::endl;
        else
            std::cout << "Wrong answer. Correct: " << answer << std::endl;
    }

    return 0;
}