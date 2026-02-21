class Solution {
public:
    int countPrimeSetBits(int left, int right) {
        // primes possible for popcount up to 20
        bool isPrimeCount[21] = {false};
        int primes[] = {2,3,5,7,11,13,17,19};
        for (int p : primes) isPrimeCount[p] = true;

        int ans = 0;
        for (int x = left; x <= right; x++) {
            int bits = __builtin_popcount((unsigned)x);
            if (isPrimeCount[bits]) ans++;
        }
        return ans;
    }
};