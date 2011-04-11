#include "parser/Parser.hpp"
#include "context/Context.hpp"

#include <cstdio>
#include <iostream>

int main()
{
  try
  {
    Parser p;

    PParseTrace(stdout, "|-| ");
    p.parse_stream(std::cin);

    std::cout << p.root()->to_string() << std::endl;

    Context context;
    std::cout << p.root()->eval(&context)->to_string() << std::endl;
  }
  catch(std::exception const & ex)
  {
    std::cout << ex.what() << std::endl;
    return 1;
  }
  catch(...)
  {
    std::cout << "Unknown exception" << std::endl;
    return 1;
  }
}

