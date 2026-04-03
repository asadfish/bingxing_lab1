#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

int N, M;
int REPEAT = 1000;

// 动态数组
int **A;
int *B;
long long *ans1;
long long *ans2;
int *arr;

// 生成矩阵
void Matrix() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (i + j) % 10 + 1;
        }
    }
}

// 生成向量
void Vector() {
    for (int i = 0; i < N; i++) {
        B[i] = i % 10 + 1;
    }
}

// 生成求和数组
void Array() {
    for (int i = 0; i < M; i++) {
        arr[i] = i % 100 + 1;
    }
}

// 问题1：平凡算法
void Ordinary1(long long res[]) {
    for (int j = 0; j < N; j++) {
        res[j] = 0;
    }

    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            res[j] += 1LL * A[i][j] * B[i];
        }
    }
}

// 问题1：cache优化
void Better1(long long res[]) {
    for (int j = 0; j < N; j++) {
        res[j] = 0;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            res[j] += 1LL * A[i][j] * B[i];
        }
    }
}

// 问题2：平凡算法
long long Ordinary2() {
    long long sum = 0;
    for (int i = 0; i < M; i++) {
        sum += arr[i];
    }
    return sum;
}

// 问题2：优化算法
long long Better2() {
    long long sum1 = 0, sum2 = 0;
    int i;
    for (i = 0; i + 1 < M; i += 2) {
        sum1 += arr[i];
        sum2 += arr[i + 1];
    }
    long long sum = sum1 + sum2;
    if (i < M) sum += arr[i];
    return sum;
}

// 检查两个数组是否一样
bool check(long long a[], long long b[]) {
    for (int i = 0; i < N; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

int main() {
    cout << "请输入N和M：";
    cin >> N >> M;

    // 动态申请矩阵 A
    A = new int*[N];
    for (int i = 0; i < N; i++) {
        A[i] = new int[N];
    }

    // 动态申请其他数组
    B = new int[N];
    ans1 = new long long[N];
    ans2 = new long long[N];
    arr = new int[M];

    Matrix();
    Vector();
    Array();

    // 正确性检查
    Ordinary1(ans1);
    Better1(ans2);

    long long s1 = Ordinary2();
    long long s2 = Better2();

    cout << "正确性检查：" << endl;
    cout << "矩阵内积结果是否一致：";
    if (check(ans1, ans2)) cout << "Yes" << endl;
    else cout << "No" << endl;

    cout << "求和结果是否一致：";
    if (s1 == s2) cout << "Yes" << endl;
    else cout << "No" << endl;

    cout << endl;
    cout << "矩阵内积前5项结果：" << endl;
    for (int i = 0; i < 5 && i < N; i++) {
        cout << ans1[i] << " ";
    }
    cout << endl;

    cout << "求和结果：" << s1 << endl;

    // 测试Q1平凡算法时间
    clock_t start1 = clock();
    for (int k = 0; k < REPEAT; k++) {
        Ordinary1(ans1);
    }
    clock_t end1 = clock();
    double time1 = (double)(end1 - start1) / CLOCKS_PER_SEC;

    // 测试Q1优化算法时间
    clock_t start2 = clock();
    for (int k = 0; k < REPEAT; k++) {
        Better1(ans2);
    }
    clock_t end2 = clock();
    double time2 = (double)(end2 - start2) / CLOCKS_PER_SEC;

    // 测试Q2平凡算法时间
    clock_t start3 = clock();
    long long temp1 = 0;
    for (int k = 0; k < REPEAT; k++) {
        temp1 = Ordinary2();
    }
    clock_t end3 = clock();
    double time3 = (double)(end3 - start3) / CLOCKS_PER_SEC;

    // 测试Q2优化算法时间
    clock_t start4 = clock();
    long long temp2 = 0;
    for (int k = 0; k < REPEAT; k++) {
        temp2 = Better2();
    }
    clock_t end4 = clock();
    double time4 = (double)(end4 - start4) / CLOCKS_PER_SEC;

    cout << endl;
    cout << "求和测试结果：" << temp1 << " " << temp2 << endl;

    cout << fixed << setprecision(6);
    cout << endl;
    cout << "测试结果：" << endl;
    cout << "Q1平凡算法时间： " << time1 << " s" << endl;
    cout << "Q1优化算法时间： " << time2 << " s" << endl;
    cout << "Q2平凡算法时间： " << time3 << " s" << endl;
    cout << "Q2优化算法时间： " << time4 << " s" << endl;

    // 释放内存
    for (int i = 0; i < N; i++) {
        delete[] A[i];
    }
    delete[] A;
    delete[] B;
    delete[] ans1;
    delete[] ans2;
    delete[] arr;

    return 0;
}