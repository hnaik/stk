#include <fstream>
#include <iostream>

#include "stk/opt/knapsack/input.h"
#include "stk/opt/knapsack/solver.h"

int main(int argc, char** argv)
{
    bool allow_multiple{false};
    std::string solver_type{"zero_one"};
    if(argc < 2) {
        std::cerr << "need an input file\n";
        return EXIT_FAILURE;
    } else if(argc == 3) {
        allow_multiple = true;
        solver_type = "bkp";
    }

    namespace ks = stk::opt::knapsack;

    std::ifstream ifs{argv[1]};

    using value_type = int;

    ks::solver_factory<value_type> factory{solver_type, "txt"};
    std::shared_ptr<ks::solver<value_type>> solver = factory.solver_handle();
    std::shared_ptr<ks::input<value_type>> input = factory.input_handle();

    input->allow_multiple(allow_multiple);
    input->read(ifs);

    std::cout << *input << "\n";

    const auto solution = solver->solve(*input);

    std::cout << solution << "\n";

    return EXIT_SUCCESS;
}
