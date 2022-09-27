#include <iostream>
#include <random> // header chứa mt19937 và mt19937_64
using namespace std;

mt19937 rng;
mt19937 rng_64;

int main() {
    // in ra 10 số ngẫu nhiên KHÔNG DẤU 32 bit
    for (int i = 0; i < 10; ++i) cout << rng() << endl;

    // in ra 10 số ngẫu nhiên KHÔNG DẤU 64 bit
    for (int i = 0; i < 10; ++i) cout << rng_64() << endl;
    return 0;
}
