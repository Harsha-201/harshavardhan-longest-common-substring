#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip> // For better formatting

// Global 2D vector for memoization
std::vector<std::vector<int>> memo;

// Function to find the longest common substring using recursion with memoization
int longestCommonSubstring(std::string &str1, std::string &str2, int m, int n, int &maxLength, int currentLength) {
    // Base case
    if (m == 0 || n == 0) {
        return 0;
    }
    
    // Check if already computed
    if (memo[m][n] != -1) {
        return memo[m][n];
    }

    // If characters match, increment the length of the current substring
    if (str1[m - 1] == str2[n - 1]) {
        currentLength = longestCommonSubstring(str1, str2, m - 1, n - 1, maxLength, currentLength + 1);
        maxLength = std::max(maxLength, currentLength + 1);
        memo[m][n] = currentLength + 1;
        return memo[m][n];
    } else {
        // If characters don't match, reset the current length and recursively call for both possibilities
        longestCommonSubstring(str1, str2, m - 1, n, maxLength, 0);
        longestCommonSubstring(str1, str2, m, n - 1, maxLength, 0);
        memo[m][n] = 0;
        return memo[m][n];
    }
}

// Function to print the detailed lookup table
void printDetailedLookupTable(const std::string &str1, const std::string &str2, int rows, int cols) {
    std::cout << "\nDetailed Lookup Table (Memoization Matrix):\n";
    
    // Print the header
    std::cout << "    "; // Space for the top left corner
    for (int j = 0; j <= cols; ++j) {
        if (j == 0)
            std::cout << "   "; // Align the first column properly
        else
            std::cout << std::setw(3) << str2[j - 1];
    }
    std::cout << "\n";

    // Print the matrix with row labels
    for (int i = 0; i <= rows; ++i) {
        if (i == 0)
            std::cout << "   "; // First cell for the header row
        else
            std::cout << " " << str1[i - 1] << " "; // Print the row label

        // Print the memoization values
        for (int j = 0; j <= cols; ++j) {
            if (memo[i][j] == -1) {
                std::cout << std::setw(3) << "0"; // Empty cells are shown as 0
            } else {
                std::cout << std::setw(3) << memo[i][j];
            }
        }
        std::cout << std::endl;
    }
}

// Function to find one of the longest common substrings
std::string findLongestCommonSubstring(std::string &str1, std::string &str2, int maxLength) {
    for (int i = 0; i <= str1.length(); ++i) {
        for (int j = 0; j <= str2.length(); ++j) {
            if (memo[i][j] == maxLength) {
                return str1.substr(i - maxLength, maxLength);
            }
        }
    }
    return "";
}

int main() {
    // Input strings from the user
    std::string str1, str2;
    std::cout << "Enter the first string: ";
    std::cin >> str1;
    std::cout << "Enter the second string: ";
    std::cin >> str2;

    // Ensure the strings are of the same length
    if (str1.length() != str2.length()) {
        std::cerr << "Error: The two strings must be of the same length!" << std::endl;
        return 1;
    }

    int m = str1.length();
    int n = str2.length();

    // Initialize the memoization table with -1
    memo.resize(m + 1, std::vector<int>(n + 1, -1));

    int maxLength = 0;

    // Find the longest common substring using recursion with memoization
    longestCommonSubstring(str1, str2, m, n, maxLength, 0);

    // Print the detailed lookup table
    printDetailedLookupTable(str1, str2, m, n);

    // Output one of the longest common substrings
    std::string result = findLongestCommonSubstring(str1, str2, maxLength);
    std::cout << "\nThe longest common substring is: \"" << result << "\" with length " << maxLength << std::endl;

    return 0;
}
