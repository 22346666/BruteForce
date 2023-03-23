#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <set>
using namespace std;
using namespace chrono;

void generate_password(vector <string>& passwords, string alphabet, int length, int ammount);
string generate_set(string alphabet);
void crack_password(const vector<string> & passwords, string alphabet);
void launch(string alphabet, int length, int ammount);

int main()
{
    launch("abcdefg", 4, 1);
    launch("abcdefg1234567890-=\][';/.,", 4, 1);
    launch("qwertyuiop[]';lkjhgfdsa/.,mnbvcxz1234567890-=\\", 20, 5);
}

 void generate_password(vector <string>& passwords, string alphabet, int length, int ammount)
{
    random_device generator;
    mt19937 engine(generator());
    uniform_int_distribution<> distributor(0, alphabet.length()-1);
    for (int i{}; i < ammount; i++) {
        string password = "";
        for (int j{}; j < length; j++) {
            password += alphabet[distributor(engine)];
        }
        passwords.push_back(password);
        password = "";
    }
}

 string generate_set (string alphabet)
 {
     set<char> unique_chars;
     string output = "";
     for (auto s : alphabet) {
         unique_chars.insert(s);
     }
     for (auto s : unique_chars) {
         output += s;
     }
     return output;
 }

void crack_password(const vector<string>& passwords, string alphabet)
{
    string trying = "";
    int i = 0;
    auto start = high_resolution_clock::now();
    for (auto s : passwords) {
        while (trying != s) {
            if (i == s.size()) {
                i = 0;
                trying = "";
            }
            trying += s[i];
            i++;
        }
        
    }
    //cout << trying << "=" << s;
    if (passwords.size() == 1) {
        cout << "  Password cracked!\n";
    }
    else {
        cout << "  Passwords cracked!\n";
    }
    auto end = high_resolution_clock::now();
    auto summ = duration_cast<microseconds>(end - start);
    cout << summ.count() << " microseconds is passed" << endl;
}

void launch(string alphabet, int length, int ammount)
{
    string alphabet_set = generate_set(alphabet);
    vector<string> passwords;
    generate_password(passwords, alphabet_set, length, ammount);
    crack_password(passwords, alphabet_set);
}
