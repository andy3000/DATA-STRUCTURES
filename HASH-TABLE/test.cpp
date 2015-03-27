#include <string>
#include "HashTable.cpp"
#include "show10.cpp"

class TestData {
  public:
    TestData();
    void setKey(const string& newKey);
    string getKey() const;
    int getValue() const;
    static unsigned int hash(const string& str);

  private:
    string key;
    int value;
    static int count;
};

int TestData::count = 0;

TestData::TestData() : value(++count) {
}

void TestData::setKey(const string& newKey) {
    key = newKey;
}

string TestData::getKey() const {
    return key;
}

int TestData::getValue() const {
    return value;
}

unsigned int TestData::hash(const string& str) {
    unsigned int val = 0;

    for ( unsigned int i = 0; i < str.length(); ++i) {
	val += str[i];
    }

    return val;
}

int main()
{
	HashTable<int, string> test( 10 );
	
}
