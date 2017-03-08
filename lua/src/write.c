#include "write.h"
#include <Windows.h>

size_t clink_fwrite(const void * ptr, size_t size, size_t count, FILE * stream)
{
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hOut == INVALID_HANDLE_VALUE)
    return fwrite(ptr, size, count, stream);

  DWORD dwMode = 0;
  if (!GetConsoleMode(hOut, &dwMode))
    dwMode = ENABLE_VIRTUAL_TERMINAL_PROCESSING;

  DWORD dwTempMode = dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  if (dwTempMode != dwMode)
    SetConsoleMode(hOut, dwTempMode);
  size_t res = fwrite(ptr, size, count, stream);
  if (dwTempMode != dwMode)
    SetConsoleMode(hOut, dwMode);

  return res;
}
