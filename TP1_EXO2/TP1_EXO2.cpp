#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(string s, int left, int right) {

    if (left >= right)
        return true;

   
    if (s[left] != s[right])
        return false;

    
    return isPalindrome(s, left + 1, right - 1);
}

int main() {
    string word;
    cout << "Enter a word: ";
    cin >> word;

    if (isPalindrome(word, 0, word.length()-1))
        cout << "It is a palindrome.\n";
    else
        cout << "It is not a palindrome.\n";

    return 0;
}
