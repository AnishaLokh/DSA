#include <iostream>
#include <cmath>
using namespace std;

#define MAX 100

struct Entry {
    string name;
    long number;
    bool isFilled = false;
};

int main() {
    Entry hashtable[MAX] = {}; // Initialize the hash table
    int n;

    cout << "Enter number of entries in telephone directory: ";
    cin >> n;

    string names[n];
    long numbers[n];

    cout << "Enter the name and number:\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ": ";
        cin >> names[i] >> numbers[i];
    }

    // Multiplicative Hash Function
    const float A = 0.618033; // Recommended value (golden ratio)
    for (int i = 0; i < n; i++) {
        float temp = numbers[i] * A;
        int index = floor(MAX * (temp - floor(temp)));

        // Linear probing in case of collision
        while (hashtable[index].isFilled) {
            index = (index + 1) % MAX;
        }

        hashtable[index].name = names[i];
        hashtable[index].number = numbers[i];
        hashtable[index].isFilled = true;
    }

    cout << "\n\n-----------------------HASH TABLE---------------------------\n";
    cout << "LOC\tNUMBER\t\tNAME\n";
    for (int i = 0; i < MAX; i++) {
        if (hashtable[i].isFilled) {
            cout << i << "\t" << hashtable[i].number << "\t" << hashtable[i].name << endl;
        }
    }

    return 0;
}
