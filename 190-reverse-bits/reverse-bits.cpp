class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        n = (n >> 16) | (n << 16);
        n = ((n & 0xFF00FF00u) >> 8)  | ((n & 0x00FF00FFu) << 8);
        n = ((n & 0xF0F0F0F0u) >> 4)  | ((n & 0x0F0F0F0Fu) << 4);
        n = ((n & 0xCCCCCCCCu) >> 2)  | ((n & 0x33333333u) << 2);
        n = ((n & 0xAAAAAAAAu) >> 1)  | ((n & 0x55555555u) << 1);
        return n;
    }
};
