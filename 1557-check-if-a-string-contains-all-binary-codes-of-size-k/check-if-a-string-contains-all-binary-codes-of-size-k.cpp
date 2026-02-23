class Solution {
public:
    bool hasAllCodes(string s, int k) {
        int n = (int)s.size();
        int need = 1 << k;                 // 2^k
        if (n - k + 1 < need) return false; // not enough windows

        vector<char> seen(need, 0);
        int mask = need - 1;               // keeps last k bits
        int val = 0, count = 0;

        for (int i = 0; i < n; i++) {
            val = ((val << 1) & mask) | (s[i] - '0');

            if (i >= k - 1) { // window size k formed
                if (!seen[val]) {
                    seen[val] = 1;
                    count++;
                    if (count == need) return true;
                }
            }
        }
        return false;
    }
};