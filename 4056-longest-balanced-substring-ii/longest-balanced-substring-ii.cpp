class Solution {
public:
    // ---------- fast hash (prevents unordered_map hacks/TLE) ----------
    struct SplitMix64 {
        static uint64_t splitmix64(uint64_t x) {
            x += 0x9e3779b97f4a7c15ULL;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
            x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
            return x ^ (x >> 31);
        }
        size_t operator()(uint64_t x) const {
            static const uint64_t FIXED_RANDOM =
                chrono::steady_clock::now().time_since_epoch().count();
            return (size_t)splitmix64(x + FIXED_RANDOM);
        }
    };

    // longest run of same char (balanced with 1 distinct char)
    int longestOne(const string& s) {
        int ans = 1, cur = 1;
        for (int i = 1; i < (int)s.size(); i++) {
            if (s[i] == s[i-1]) cur++;
            else cur = 1;
            ans = max(ans, cur);
        }
        return ans;
    }

    // ---------- O(n) without hashing for 2-char case ----------
    int longestTwoArray(const string& s, char x, char y, char ban) {
        int n = (int)s.size();
        int OFFSET = n;
        int W = 2 * n + 1;

        vector<int> firstPos(W, 0);
        vector<int> seenVer(W, 0);
        int ver = 1;

        int diff = 0;
        int ans = 0;

        auto reset = [&](int idx) {
            ver++;
            diff = 0;
            int id = diff + OFFSET;
            seenVer[id] = ver;
            firstPos[id] = idx;
        };

        reset(-1);

        for (int i = 0; i < n; i++) {
            if (s[i] == ban) {
                reset(i);
                continue;
            }

            if (s[i] == x) diff++;
            else if (s[i] == y) diff--;

            int id = diff + OFFSET;
            if (seenVer[id] != ver) {
                seenVer[id] = ver;
                firstPos[id] = i;
            } else {
                ans = max(ans, i - firstPos[id]);
            }
        }
        return ans;
    }

    // ---------- 3-char case (needs map), but with fast hash ----------
    int longestThree(const string& s) {
        unordered_map<uint64_t, int, SplitMix64> first;
        first.reserve(s.size() * 2);
        first.max_load_factor(0.7f);

        int d1 = 0; // prefA - prefB
        int d2 = 0; // prefA - prefC
        int ans = 0;

        auto key = [&](int a, int b) -> uint64_t {
            return (uint64_t)(uint32_t)a << 32 | (uint32_t)b;
        };

        first[key(0, 0)] = -1;

        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == 'a') { d1++; d2++; }
            else if (s[i] == 'b') { d1--; }
            else { d2--; } // 'c'

            uint64_t k = key(d1, d2);
            auto it = first.find(k);
            if (it == first.end()) first.emplace(k, i);
            else ans = max(ans, i - it->second);
        }
        return ans;
    }

    int longestBalanced(string s) {
        int ans = 0;
        ans = max(ans, longestOne(s));
        ans = max(ans, longestTwoArray(s, 'a', 'b', 'c'));
        ans = max(ans, longestTwoArray(s, 'a', 'c', 'b'));
        ans = max(ans, longestTwoArray(s, 'b', 'c', 'a'));
        ans = max(ans, longestThree(s));
        return ans;
    }
};