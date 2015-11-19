#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

unsigned long cryptTable[0x500];

/*
 * 创建一个长度为0x500（10进制数：1280）的cryptTable[0x500]
 */
void prepareCryptTable() {
    unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;
    unsigned long tmp1, tmp2;

    for (index1 = 0; index1 < 0x100; ++index1) {
        for (index2 = index1, i = 0; i < 5; ++i, index2 += 0x100) {
            seed = (seed * 125 + 3) % 0x2AAAAB;
            tmp1 = (seed & 0xFFFF) << 0x10;
            seed = (seed * 125 + 3) % 0x2AAAAB;
            tmp2 = (seed & 0XFFFF);

            cryptTable[index2] = (tmp1 | tmp2);
        }
    }
}

/*
 * 暴雪的Hash算法, One-Way Hash，得到与原来字符串相同的哈希值几乎不可能 
 */
unsigned long HashString(string fileName, unsigned long dwHashType) {
    string key(fileName);
    unsigned long seed1 = 0x7FED7FED;
    unsigned long seed2 = 0xEEEEEEEE;
    int ch;

    for (auto k : key) {
        k = toupper(k);
        seed1 = cryptTable[(dwHashType << 8) + k] ^ (seed1 + seed2);
        seed2 = k + seed1 + seed2 + (seed2 << 5) + 3;
    }
    return seed1;
}



int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "Usage: ./CryptTable arg" << endl;
        return -1;
    }

    unsigned long ulHashValue;

    // 初始化数组
    prepareCryptTable();

    for (int i = 0; i < 0x500; ++i) {
        if (i % 10 == 0) {
            cout << endl;
        } else {
            cout << setw(12) << left << hex << showbase << cryptTable[i];
        }
    }
    
    ulHashValue = HashString(argv[1], 0);
    cout << ulHashValue << endl;

    ulHashValue = HashString(argv[1], 1);
    cout << ulHashValue << endl;

    ulHashValue = HashString(argv[1], 2);
    cout << ulHashValue << endl;
    return 0;
}
