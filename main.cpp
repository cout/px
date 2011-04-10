#include <cstdlib>

void *PParseAlloc(void *(*mallocProc)(size_t));
void PParseFree(void *p, void (*freeProc)(void*));

int main()
{
  void * parser = PParseAlloc(std::malloc);
  PParseFree(parser, std::free);
}

