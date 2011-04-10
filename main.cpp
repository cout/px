#include <cstdlib>

void *ParseAlloc(void *(*mallocProc)(size_t));
void ParseFree(void *p, void (*freeProc)(void*));

int main()
{
  void * parser = ParseAlloc(std::malloc);
  ParseFree(parser, std::free);
}

