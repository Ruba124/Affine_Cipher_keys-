
#include <iostream>
#include <string>
using namespace std;
int find_inverse(int a, int b);

int main()
{
    int a, b;
    cout << "Enter a and b: ";
    cin >> a >> b;
    cout << "The inverse of " << a << " modulo " << b << " is: " << find_inverse(a, b) << endl;
    return 0;
}

int find_inverse(int a, int b)
{
for(int i = 1; i > 0; i++)
{

    if((i * a) % b == 1)
    {
        return i;
        
    }

}
return -1;

}