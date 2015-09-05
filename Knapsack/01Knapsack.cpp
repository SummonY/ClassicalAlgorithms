#include <iostream>

using namespace std;

const int object_num = 10;
const int knapsack_weight = 50;

struct Object {
    int value;
    int weight;
};

class Knapsack {
private:
    int capacity;
    int value;

public:
    Knapsack(int c, int v) : capacity(c), value(v) {}

    int get_max_value(Object obj[], int result[]) {       // 获取背包最大价值
        int max_value, i, j;
        int value[object_num + 1][knapsack_weight + 1];

        for (i = 0; i <= object_num; ++i) {
            value[i][0] = 0;
        }
        for (j = 0; j <= knapsack_weight; ++j) {
            value[0][j] = 0;
        }

        for (i = 1; i <= object_num; ++i) {
            for (j = 1; j <= knapsack_weight; ++j) {
                if (obj[i - 1].weight > j) {
                    value[i][j] = value[i - 1][j];
                } else {
                    value[i][j] = max(value[i - 1][j], (value[i - 1][j - obj[i - 1].weight] + obj[i - 1].value));
                }
            }
        }
        
        int knapWeight = knapsack_weight;
        for (i = object_num; i > 0; --i) {
            if (value[i][knapWeight] > value[i - 1][knapWeight]) {
                result[i - 1] = 1;
                knapWeight = knapWeight - obj[i - 1].weight;
            } else {
                result[i - 1] = 0;
            }
        }
        max_value = value[object_num][knapsack_weight];

        return max_value;
    }
    
};


int main()
{
    Object obj[object_num];
    for (int i = 0; i < object_num; ++i) {
        obj[i].value = i + 10;
        obj[i].weight = i + 5;
    }
    for (int i = 0; i < object_num; ++i) {
        cout << "weight = " << obj[i].weight << " value = " << obj[i].value << endl;
    }

    Knapsack knapsack(50, 0);
    int result[object_num];
    int maxValue;
    
    maxValue = knapsack.get_max_value(obj, result);

    cout << "背包最大值: " << maxValue << endl;
    
    for (int i = 0; i < object_num; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
