class Solution:
    def isPalindrome(self, x: int) -> bool:
        # Negative numbers are not palindromes
        # Numbers ending in 0 are not palindromes unless the number is 0
        if x < 0 or (x % 10 == 0 and x != 0):
            return False

        reversed_half = 0

        # Reverse only the second half of the number
        while x > reversed_half:
            digit = x % 10
            reversed_half = reversed_half * 10 + digit
            x = x // 10

        # Even length: x == reversed_half
        # Odd length: x == reversed_half // 10
        return x == reversed_half or x == reversed_half // 10