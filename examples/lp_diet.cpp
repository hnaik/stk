#include <iostream>
#include <limits>

#include "stk/ds/matrix.h"
#include "stk/opt/model.h"
#include "stk/opt/result.h"

int main()
{
    namespace opt = stk::opt;

    opt::basic_model<double> model;
    model.set_name("hello world");

    stk::ds::matrix<double> constraints = {
        // clang-format off
            410.0, 24.0, 26.0, 730.0,   //
            420.0, 32.0, 10.0, 1190.0,  //
            560.0, 20.0, 32.0, 1800.0,  //
            380.0, 4.0, 19.0, 270.0,    //
            320.0, 12.0, 10.0, 930.0,   //
            320.0, 15.0, 12.0, 820.0,   //
            320.0, 31.0, 12.0, 1230.0,  //
            100.0, 8.0, 2.5, 125.0,     //
            330.0, 8.0, 10.0, 180.0     //
        // clang-format on
    };
    constraints.reshape(9, 4);
    model.set_constraints(constraints);

    stk::ds::vector<double> costs{2.49, 2.89, 1.50, 1.89, 2.09,
                                  1.99, 2.49, 0.89, 1.59};

    model.set_costs(costs);

    opt::basic_model<double>::bounds_container bounds{
        {"c", {1800.0}, {2200.0}},
        {"p", {91.0}, {std::numeric_limits<double>::infinity()}},
        opt::bounds<double>{"f", {0.0}, {65.0}},
        opt::bounds<double>{"s", {0.0}, {1779.0}},
    };

    model.set_bounds(bounds);
    model.set_constraint_names({"h", "c", "h", "f", "m", "p", "s", "m", "i"});

    std::cout << model << "\n";

    return EXIT_SUCCESS;
}
