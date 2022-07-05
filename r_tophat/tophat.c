
#include <stdio.h>

#include <assert.h>
#include <stdlib.h>

#include "linklist.h"

void tophat(ElemType arr[], size_t len, size_t wnd_size, FILE* out) {
    assert(len >= wnd_size * 2);

    ElemType* buffer = malloc(len * sizeof(ElemType));

    pLinkList q = linklist_create();

    for (int i = 0; i < len; ++i) {
        if (i >= wnd_size) {
            if (i == wnd_size) {
                for (int j = 0; j <= wnd_size; ++j)
                    buffer[j] = arr[i] - linklist_front(q);
            } else {
                buffer[i] = arr[i] - linklist_front(q);
            }
            if (arr[i - wnd_size] == linklist_front(q)) {
                linklist_pop_front(q);
            }
        }

        while (!linklist_is_empty(q) && linklist_back(q) > arr[i])
            linklist_pop_back(q);

        linklist_push_back(q, arr[i]);
    }

    buffer[len - 1] = arr[len - 1] - linklist_front(q);

    for (int i = wnd_size; i < len - wnd_size; ++i)
        fprintf_s(out, "%d,", (buffer[i] - buffer[i - wnd_size]) * (buffer[i] - buffer[i + wnd_size]));

    free(buffer);
    linklist_destroy(q);
}

#define fs 250
#define Tr 30  // R波宽度(25~40ms)
#define DATA_SRC 1

int main() {
#if DATA_SRC == 1
#include "ecg_normal.h"
    FILE* outFile = fopen("ecg_normal_tophat_c.txt", "w");
#elif DATA_SRC == 2
#include "ecg_happy.h"
    FILE* outFile = fopen("ecg_happy_tophat_c.txt", "w");
#elif DATA_SRC == 3
#include "ecg_fear.h"
    FILE* outFile = fopen("ecg_fear_tophat_c.txt", "w");
#endif

    tophat(arr, sizeof(arr) / sizeof(int), fs * Tr / 1000 + 1, outFile);
    fclose(outFile);

    return 0;
}
