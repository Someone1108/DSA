class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = (int)nums.size();
        int ans = 0;

        for (int l = 0; l < n; l++) {
            unordered_map<int,int> evenFreq, oddFreq;
            int distinctEven = 0, distinctOdd = 0;

            for (int r = l; r < n; r++) {
                int x = nums[r];
                if (x % 2 == 0) {
                    int &f = evenFreq[x];
                    if (f == 0) distinctEven++;
                    f++;
                } else {
                    int &f = oddFreq[x];
                    if (f == 0) distinctOdd++;
                    f++;
                }

                if (distinctEven == distinctOdd) {
                    ans = max(ans, r - l + 1);
                }
            }
        }

        return ans;
    }
};