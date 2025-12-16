
#include <iostream>
#include <string>
using namespace std;
const string Samon_base = "AEIOUFGHLMNPRSTVK";
const string Samon_with_space = " AEIOUFGHLMNPRSTVK";
string affine_encrypt(string message, int a, int b, string alphabet);
int cal_gcd(int a, int b);
int find_mod_inverse(int a, int m);
string affine_decrypt(string cipher_text, int a_inv, int b, string alphabet);
int wrap_a(int a, int m);

int main()
{ int a, b,a_1, b_1,c;
int count = 0;
bool exit = false;
    string active_samon;
  cout << "--- Affine Cipher (Samoan) ---" << endl;
  cout<< "Part A"<<endl;
  cout<< "The Samoan alphabet has 17 letters (A, E, I, O, U, F, G, H, L, M, N, P, R, S, T, V, K) and an optional space character to use if the keys are not coprime with 17." << endl;
  cout<< "The message is E TAUA LENEI GALUEGA"<<endl;
  cout << "The keys are 17, 13" << endl;
  a_1 = 17;
  b_1 = 13;
  while(!exit){
    if ( count == 0){
        a = a_1;
        b = b_1;
       
    }
    else if ( count ==1){
         cout<< "----------------------------------"<<endl;
         cout<< "Part B"<<endl;
         cout<< "Now it's your turn to try! "<<endl;
         cout << "You can enter your own keys and message to see the encryption and decryption process." << endl;
         cout << "if u want to exit the program enter 0 ,if u dont  want to exit enter any other number   " << endl;
         cin >> c;
            if ( c == 0) {
                exit = true;
                break;}
          cout << "Enter two keys (a b):  " << endl;
        cin >> a >> b;}
    else if (count > 1){
         cout << "if u want to exit the program enter 0 ,if u dont  want to exit enter any other number   " << endl;
         cin >> c;
            if ( c == 0) {
                exit = true;
                break;}
        cout << "Enter two keys (a b):  " << endl;
        cin >> a >> b;
    }
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
        count++;
        continue;
    }
    string message;
    if (count == 0)
    {
        message = "E TAUA LENEI GALUEGA";
    }
    else if (count >= 1){
    cout << "Enter your message: " << endl;
   
    cin.ignore();
    getline(cin, message);}
    string encrypted_message =  affine_encrypt(message, wrap_a(a, active_samon.length()), b, active_samon);
    cout << "Encrypted message: " << encrypted_message << endl;
    cout<<"Decryption part "<<endl;
    int mod_inverse = find_mod_inverse(wrap_a(a, active_samon.length()), active_samon.length());
    if (mod_inverse == -1) {
        cout << "Modular inverse does not exist, decryption not possible." << endl;
        return 1;
    }
    string decrypted_message = affine_decrypt(encrypted_message, mod_inverse, b, active_samon);
   cout << "Decrypted message: " << decrypted_message << endl;
    count++;
}

    return 0;
    

}
int wrap_a(int a, int m){
    // Wrap 'a' to be within the range of 0 to m-1
    if(a > 0) return a;
    a = (a % m + m);
    return a;
}

int cal_gcd(int a, int b)
{ if( a < 0){
    a = wrap_a(a, b);
}
    int r;
  while (b != 0)
  { r = a % b;
    a = b;
    b = r;
  }
  return a;
}
int find_mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No modular inverse exists
}
string affine_encrypt(string message, int a, int b, string alphabet) {
    string cipher_text = "";
    int m = alphabet.length(); // Get the modulo (m) from the alphabet size
    cout<<"The encryption formela is  ("<< a << "x + " << b << ") mod " << m << endl;

    for (char c : message) {
        // 1. Find the position of the character in the alphabet
       size_t index = alphabet.find(toupper(c));

        // 2. Check if the character exists in the alphabet
        if (index != string::npos) {
            // Apply Affine Cipher Formula: (ax + b) % m
            // We use 'long long' for the multiplication to prevent overflow before the modulo
            long long math_val = (long long)a * index + b;
            if(math_val < 0){
                math_val = wrap_a(math_val, m);
            }
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
string affine_decrypt(string cipher_text, int a_inv, int b, string alphabet) {
    string decrypted_text = "";
    int m = alphabet.length(); // Get the modulo (m) from the alphabet size
   cout<<"The decryption formela is  ("<< a_inv << "(x - " << b << ")) mod " << m << endl;
    for (char c : cipher_text) {
        // 1. Find the position of the character in the alphabet
        size_t index = alphabet.find(toupper(c));

        // 2. Check if the character exists in the alphabet
        if (index != string::npos) {
            // Apply Affine Decryption Formula: a_inv * (x - b) % m
            long long math_val = (long long)a_inv * (index - b ); 
            int decrypted_index = ((math_val % m) + m) % m; // Ensure positive modulo

            // Append the new decrypted character
            decrypted_text += alphabet[decrypted_index];
        } 
        else {
            // 3. If not found (like a space), keep it unchanged
            decrypted_text += c;
        }
    }
    
    return decrypted_text;
}