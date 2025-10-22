#include "utils_mem.h"
#include <cstdio>

namespace memtrack {
size_t g_alloc = 0, g_local = 0, g_iters = 0;
void printReport() {
    std::printf("[Métricas] alloc=%zu bytes, local=%zu bytes, iter=%zu\n",
                g_alloc, g_local, g_iters);
}
}
