class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> trailing(n);

        // Count trailing zeros in each row
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = n - 1; j >= 0; j--) {
                if (grid[i][j] == 0) cnt++;
                else break;
            }
            trailing[i] = cnt;
        }

        int ans = 0;

        for (int i = 0; i < n; i++) {
            int need = n - 1 - i;
            int j = i;

            // Find first row that can satisfy current position
            while (j < n && trailing[j] < need) {
                j++;
            }

            if (j == n) return -1;

            // Bring row j to position i using adjacent swaps
            while (j > i) {
                swap(trailing[j], trailing[j - 1]);
                j--;
                ans++;
            }
        }

        return ans;
    }
};