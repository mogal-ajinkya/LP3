#include<bits/stdc++.h>
using namespace std;

void fibonacciIterative(int n) {
    int first = 0, second = 1, next;
    cout << "Iterative Fibonacci series up to " << n << " terms: ";
    
    if (n >= 1) cout << first << " ";
    if (n >= 2) cout << second << " ";
    
    for (int i = 3; i <= n; i++) {
        next = first + second;
        cout << next << " ";
        first = second;
        second = next;
    }
    cout << endl;
}

int fibonacciMemo(int n, vector<int> &memo) {
    if (n <= 1)
        return n;
    if (memo[n] != -1)
        return memo[n];
    memo[n] = fibonacciMemo(n - 1, memo) + fibonacciMemo(n - 2, memo);
    return memo[n];
}

void printFibonacciRecursive(int n) {
    vector<int> memo(n + 1, -1); 
    cout << "Recursive Fibonacci series up to " << n << " terms (optimized recursive): ";
    for (int i = 0; i < n; i++) {
        cout << fibonacciMemo(i, memo) << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of terms: ";
    cin >> n;
    
    fibonacciIterative(n);
    printFibonacciRecursive(n);
    
    return 0;
}
