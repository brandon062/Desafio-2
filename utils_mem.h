#ifndef UTILS_MEM_H
#define UTILS_MEM_H
#include <cstddef>

namespace memtrack {
extern size_t g_alloc, g_local, g_iters;
inline void reset() { g_alloc = g_local = g_iters = 0; }
inline void addAlloc(size_t b) { g_alloc += b; }
inline void addLocal(size_t b) { g_local += b; }
inline void addIter(size_t c) { g_iters += c; }
void printReport();
}
#endif

