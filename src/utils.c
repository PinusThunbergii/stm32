#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif

void soft_break_point()
{
    __asm__("BKPT");
}

#ifdef __cplusplus
}
#endif