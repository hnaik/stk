#include <fstream>
#include <iostream>

#include <unordered_map>
#include <variant>

#include <getopt.h>
#include <unistd.h>

#include "stk/opt/knapsack/input.h"
#include "stk/opt/knapsack/model.h"
#include "stk/opt/knapsack/model_factory.h"

struct program_options {
    bool verbose = false;
    std::string solver_name;
    std::string input_path;
};

program_options parse_args(int argc, char** argv);

int main(int argc, char** argv)
{
    const auto options = parse_args(argc, argv);

    namespace ks = stk::opt::knapsack;

    if(options.verbose) {
        std::cout << options.input_path << "\n";
    }

    std::ifstream ifs{options.input_path};

    using value_type = int;

    ks::model_factory<value_type> factory{options.solver_name, "txt"};
    std::shared_ptr<ks::model<value_type>> model = factory.solver_handle();
    std::shared_ptr<ks::input<value_type>> input = factory.input_handle();

    if(argc == 4) {
        std::cout << "allowing multiple\n";
        input->allow_multiple(true);
    }
    input->read(ifs);

    if(options.verbose) {
        std::cout << *input;
    }

    const auto solution = model->solve(*input);

    std::cout << solution << "\n";

    return EXIT_SUCCESS;
}

program_options parse_args(int argc, char** argv)
{
    program_options options;

    static const char* opt_string = "siv";
    static const struct option long_opts[] = {
        {"solver-name", required_argument, nullptr, 's'},
        {"input-path", required_argument, nullptr, 'i'},
        {"verbose", no_argument, nullptr, 'v'}
        //
    };

    int idx;
    auto opt = getopt_long(argc, argv, opt_string, long_opts, &idx);

    while(opt != -1) {
        switch(opt) {
        case 's':
            options.solver_name = optarg;
            break;

        case 'v':
            options.verbose = true;
            break;

        case 'i':
            options.input_path = optarg;
            break;
        }

        opt = getopt_long(argc, argv, opt_string, long_opts, &idx);
    }

    return options;
}
