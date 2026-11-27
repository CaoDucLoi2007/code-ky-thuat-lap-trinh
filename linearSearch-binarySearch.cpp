#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <ctime>

using namespace std;
using namespace std::chrono;

int linearSearch(const vector<int>& a, int target, long long& comparisons) {
    comparisons = 0;
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        comparisons++;
        if (a[i] == target) {
            return i;
        }
    }
    return -1;
}

int binarySearch(const vector<int>& a, int target, long long& comparisons) {
    comparisons = 0;
    int left = 0;
    int right = static_cast<int>(a.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        comparisons++;
        if (a[mid] == target) {
            return mid;
        }

        comparisons++;
        if (a[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    mt19937 rng(static_cast<unsigned int>(time(nullptr)));

    int n = 100000;
    cout << "Nhap n (nhap 0 de mac dinh 100000): ";
    int inputN;
    if (cin >> inputN && inputN > 0) {
        n = inputN;
    }

    int mode;
    cout << "Chon che do du lieu:\n";
    cout << "  1. Nhap mang tu ban phim\n";
    cout << "  2. Sinh mang ngau nhien (bien ngau nhien)\n";
    cout << "Lua chon: ";
    cin >> mode;

    vector<int> a(n);
    if (mode == 1) {
        cout << "Nhap " << n << " phan tu:\n";
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
    } else {
        uniform_int_distribution<int> dist(1, n * 10);
        for (int i = 0; i < n; ++i) {
            a[i] = dist(rng);
        }
        cout << "Da sinh ngau nhien " << n << " phan tu trong [1, " << n * 10 << "].\n";
    }

    int targetMode;
    cout << "Chon gia tri can tim:\n";
    cout << "  1. Nhap gia tri target\n";
    cout << "  2. Chon ngau nhien 1 phan tu co trong mang (bien ngau nhien)\n";
    cout << "  3. Chon ngau nhien 1 gia tri khong co trong mang (truong hop xau nhat)\n";
    cout << "Lua chon: ";
    cin >> targetMode;

    int target = 0;
    if (targetMode == 1) {
        cout << "Nhap target: ";
        cin >> target;
    } else if (targetMode == 2) {
        uniform_int_distribution<int> idxDist(0, n - 1);
        target = a[idxDist(rng)];
    } else {
        target = n * 10 + 999;
    }
    cout << "Gia tri can tim (target) = " << target << "\n";

    long long linComparisons = 0;
    auto linStart = high_resolution_clock::now();
    int linPos = linearSearch(a, target, linComparisons);
    auto linEnd = high_resolution_clock::now();
    auto linNs = duration_cast<nanoseconds>(linEnd - linStart).count();

    vector<int> sortedA = a;
    auto sortStart = high_resolution_clock::now();
    sort(sortedA.begin(), sortedA.end());
    auto sortEnd = high_resolution_clock::now();
    auto sortNs = duration_cast<nanoseconds>(sortEnd - sortStart).count();

    long long binComparisons = 0;
    auto binStart = high_resolution_clock::now();
    int binPos = binarySearch(sortedA, target, binComparisons);
    auto binEnd = high_resolution_clock::now();
    auto binNs = duration_cast<nanoseconds>(binEnd - binStart).count();

    cout << "\n==================== KET QUA ====================\n";
    cout << "[Linear Search]\n";
    cout << "  Vi tri (mang goc): " << linPos << (linPos == -1 ? " (Khong thay)" : "") << "\n";
    cout << "  So phep so sanh : " << linComparisons << "\n";
    cout << "  Thoi gian       : " << linNs << " ns (" << linNs / 1e6 << " ms)\n";

    cout << "\n[Binary Search - tren mang da sap xep]\n";
    cout << "  Vi tri (mang sort): " << binPos << (binPos == -1 ? " (Khong thay)" : "") << "\n";
    cout << "  So phep so sanh  : " << binComparisons << "\n";
    cout << "  Thoi gian search : " << binNs << " ns (" << binNs / 1e6 << " ms)\n";
    cout << "  Thoi gian sort   : " << sortNs << " ns (" << sortNs / 1e6 << " ms)\n";
    cout << "  Tong (sort+search): " << (sortNs + binNs) << " ns (" << (sortNs + binNs) / 1e6 << " ms)\n";

    return 0;
}