#include<iostream>
using namespace std;

const int TABLE_SIZE=10;

struct Entry {
    string name;
    string phone;
    bool isOccupied;
};

Entry hashTable[TABLE_SIZE];

int hashFunction(string name)
{
    int sum=0;
    for(char c : name)
    {
        sum+=c;
    }
    return sum % TABLE_SIZE;
}
void insert(string name,string phone)
{
    int index = hashFunction(name);
    
    //LinearProbing if collosion happens
    while(hashTable[index].isOccupied)
    {
        index=(index+1)%TABLE_SIZE;
    }

    hashTable[index].name = name;
    hashTable[index].phone = phone;
    hashTable[index].isOccupied=true;

    cout<<"Inserted : "<<name<<"->"<<phone<<endl;
}
void search(string name)
{
    int index=hashFunction(name);
    int startIndex= index;

    while(hashTable[index].isOccupied)
    {
        if(hashTable[index].name==name)
        {
            cout<<"Found:"<<name<<"->"<<hashTable[index].phone<<endl;
            return;
        }
        index=(index+1)%TABLE_SIZE;
        if(index==startIndex) break;
    }
    cout<<"Not found\n";
}
void display()
{
    cout<<"\n Telephone Directory:\n";
    for(int i=0;i<TABLE_SIZE;i++)
    {
        if(hashTable[i].isOccupied){
            cout<<i<<":"<<hashTable[i].name<<"->"<<hashTable[i].phone<<endl;
        }else
        {
            cout<<i<<":Empty\n";
        }
    }
}
int main()
{
    insert("Akshad","1234");
    insert("Anisha","1234");
    insert("vansh","1234");
    display();
    search("Anisha");
    search("Akshad"); // Not present

    // Show all entries
    display();
}