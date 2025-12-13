
#include <iostream>
#include <string>
using namespace std;
const string Samon_base = "AEIOUFGHLMNPRSTVK";
const string Samon_with_space = " AEIOUFGHLMNPRSTVK";
string affine_encrypt(string message, int a, int b, string alphabet);
int cal_gcd(int a, int b);

int main()
{ int a, b;
    string active_samon;
  cout << "--- Affine Cipher (Samoan) ---" << endl;
    cout << "Enter two keys (a b):  " << endl;
    cin >> a >> b;
    if( cal_gcd(a, 17) == 1){
        active_samon = Samon_base;
        cout << "Using Samoan alphabet without space." << endl;
    }
    else if( cal_gcd(a, 18) == 1){
        active_samon = Samon_with_space;
        cout << "Using Samoan alphabet with space in the beginning." << endl;
    }
    else{
        cout << "Key 'a' is not valid. It must be coprime with " << 17 << " or " << 18 << "." << endl;
        return 1;
    }
    cout << "Enter your message: " << endl;
    string message;
    cin.ignore();
    getline(cin, message);
    string encrypted_message =  affine_encrypt(message, a, b, active_samon);
    cout << "Encrypted message: " << encrypted_message << endl;
   

return 0;
}

int cal_gcd(int a, int b)
{ int r;
  while (b != 0)
  { r = a % b;
    a = b;
    b = r;
  }
  return a;
}
string affine_encrypt(string message, int a, int b, string alphabet) {
    string cipher_text = "";
    int m = alphabet.length(); // Get the modulo (m) from the alphabet size

    for (char c : message) {
        // 1. Find the position of the character in the alphabet
        size_t index = alphabet.find(c);

        // 2. Check if the character exists in the alphabet
        if (index != string::npos) {
            // Apply Affine Cipher Formula: (ax + b) % m
            // We use 'long long' for the multiplication to prevent overflow before the modulo
            long long math_val = (long long)a * index + b;
            int encrypted_index = math_val % m;

            // Append the new encrypted character
            cipher_text += alphabet[encrypted_index];
        } 
        else {
            // 3. If not found (like a space), keep it unchanged
            cipher_text += c;
        }
    }
    
    return cipher_text;
}