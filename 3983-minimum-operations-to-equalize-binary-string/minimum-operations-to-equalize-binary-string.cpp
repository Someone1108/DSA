class Solution {
public:
    bool can(int t, int n, int z, int k) {
        long long total = 1LL * t * k;

        // parity must match
        if ((total - z) % 2 != 0) return false;

        // minimum total flips needed:
        // every initial 0 must be flipped odd times -> at least 1 each
        if (total < z) return false;

        // maximum total flips possible with correct parity
        long long mx;
        if (t % 2 == 0) {
            // zeros: max odd <= t-1, ones: max even <= t
            mx = 1LL * z * (t - 1) + 1LL * (n - z) * t;
        } else {
            // zeros: max odd <= t, ones: max even <= t-1
            mx = 1LL * z * t + 1LL * (n - z) * (t - 1);
        }

        return total <= mx;
    }

    int minOperations(string s, int k) {
        int n = s.size();
        int z = 0;
        for (char c : s) {
            if (c == '0') z++;
        }

        if (z == 0) return 0;

        // special case: must flip all bits every time
        if (k == n) {
            if (z == n) return 1;   // all 0 -> all 1 in one move
            return -1;              // mixed string can never become all 1
        }

        for (int t = 1; t <= n; t++) {
            if (can(t, n, z, k)) return t;
        }

        return -1;
    }
};