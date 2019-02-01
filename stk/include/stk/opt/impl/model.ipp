#include <istream>

namespace stk::opt {

template <typename T>
void basic_model<T>::solve()
{
/* Reference:
 * (1997) The Simplex Method. In: Linear Programming. Springer Series in
 * Operations Research and Financial Engineering. Springer, New York, NY
 */

}

template<typename T>
void basic_model<T>::read(std::istream& is)
{
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const model<T>& m)
{
    static constexpr const char* dashed_line = "\
================================================================================\
";
    os << dashed_line << "\n"
       << std::left << std::setfill(' ') << std::setw(80) << m.name() << "\n"
       << dashed_line << "\n"
       << "objective: \n"
       << m.objective() << "\ncosts: \n"
       << m.costs() << "\n\nconstraints: \n"
       << m.constraints() << "\n"
       << dashed_line << "\n";

    return os;
}
} // namespace std::opt
