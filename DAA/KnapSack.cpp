
#include <bits/stdc++.h>
using namespace std;

int knapsackUtil(vector<int>& wt, vector<int>& val, int ind, int W, vector<vector<int>>& dp) {
    if (ind == 0 || W == 0)        return 0;

    if (dp[ind][W] != -1)    return dp[ind][W];
    
    int notTaken = knapsackUtil(wt, val, ind - 1, W, dp);

    int taken = 0;
    if (wt[ind] <= W)
        taken = val[ind] + knapsackUtil(wt, val, ind - 1, W - wt[ind], dp);
    
    return dp[ind][W] = max(notTaken, taken);
}

int knapsack(vector<int>& wt, vector<int>& val, int n, int W) {
    vector<vector<int>> dp(n, vector<int>(W + 1, -1));
    return knapsackUtil(wt, val, n - 1, W, dp);
}

int main() {
    vector<int> wt = {1, 2, 4, 5};
    vector<int> val = {5, 4, 8, 6};
    int W = 5;
    int n = wt.size();
    cout << "The Maximum value of items the thief can steal is " << knapsack(wt, val, n, W);
    return 0;
}



// #include <bits/stdc++.h>
// using namespace std;

// // Function to solve the 0/1 Knapsack problem using dynamic programming
// int knapsack(vector<int>& wt, vector<int>& val, int n, int W) {
//     // Create a 2D DP table with dimensions n x W+1 and initialize it with zeros
//     vector<vector<int>> dp(n, vector<int>(W + 1, 0));

//     // Base condition: Fill in the first row for the weight of the first item
//     for (int i = wt[0]; i <= W; i++) {
//         dp[0][i] = val[0];
//     }

//     // Fill in the DP table using a bottom-up approach
//     for (int ind = 1; ind < n; ind++) {
//         for (int cap = 0; cap <= W; cap++) {
//             // Calculate the maximum value by either excluding the current item or including it
//             int notTaken = dp[ind - 1][cap];
//             int taken = INT_MIN;

//             // Check if the current item can be included without exceeding the knapsack's capacity
//             if (wt[ind] <= cap) {
//                 taken = val[ind] + dp[ind - 1][cap - wt[ind]];
//             }

//             // Update the DP table
//             dp[ind][cap] = max(notTaken, taken);
//         }
//     }

//     // The final result is in the last cell of the DP table
//     return dp[n - 1][W];
// }

// int main() {
//     vector<int> wt = {1, 2, 4, 5};
//     vector<int> val = {5, 4, 8, 6};
//     int W = 5;
//     int n = wt.size();

//     cout << "The Maximum value of items the thief can steal is " << knapsack(wt, val, n, W);

//     return 0;
// }





/*

The Branch and Bound Algorithm is a method used in combinatorial optimization 
problems to systematically search for the best solution. It works by dividing 
the problem into smaller subproblems, or branches, and then eliminating certain 
branches based on bounds on the optimal solution. This process continues until 
the best solution is found or all branches have been explored.

The idea is to simply store the results of subproblems so that we do not have 
to re-compute them when needed later. 
*/