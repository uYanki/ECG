
#include <fstream>
#include <iostream>
#include <queue>

template <typename T>
void tophat(T arr[], size_t len, size_t wnd_size, std::ostream& out) {
    T* buffer = new T[len - wnd_size];

    std::deque<T> q;
    for (int i = 0; i < len; ++i) {
        if (i >= wnd_size) {
            if (i == wnd_size) {
                for (int j = 0; j < wnd_size; ++j)
                    buffer[j] = arr[j] - q.front();
            } else {
                buffer[i] = arr[i] - q.front();
            }
            if (arr[i - wnd_size] == q.front()) q.pop_front();
        }

        while (!q.empty() && q.back() > arr[i]) q.pop_back();
        q.push_back(arr[i]);
    }

    buffer[len - 1] = arr[len - 1] - q.front();

    len -= wnd_size * 2;

    for (int i = wnd_size; i < len; ++i)
        out << (buffer[i] - buffer[i - wnd_size]) * buffer[i] - buffer[i + wnd_size] << ",";

    delete[] buffer;
}

#define fs 250
#define Tr 30  // R波宽度(25~40ms)
#define DATA_SRC 1

int main() {
#if DATA_SRC == 1
#include "ecg_normal.h"
    std::ofstream outFile("ecg_normal_tophat.txt");
#elif DATA_SRC == 2
#include "ecg_happy.h"
    std::ofstream outFile("ecg_happy_tophat.txt");
#elif DATA_SRC == 3
#include "ecg_fear.h"
    std::ofstream outFile("ecg_fear_tophat.txt");
#endif

    tophat(arr, sizeof(arr) / sizeof(int), fs * Tr / 1000 + 1, outFile);
    // tophat(arr, sizeof(arr) / sizeof(int), fs * Tr / 1000 + 1, std::cout);
    outFile.close();

    return 0;
}
