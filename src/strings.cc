#include <strings.h>
#include <windows.h>

int ffs(int i) {
    ULONG index, mask = (ULONG)i;
    UCHAR isNonzero = _BitScanForward(&index, mask);
    if (isNonzero)
        return index + 1;
    else
        return 0;
}
