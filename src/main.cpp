#include "Image.cpp"

using namespace std;

int main(){


   TestOne();
    TestTwo(); //Failed
    TestThree();
    TestFour();
    TestFive(); //Failed
    TestSix();
    TestSeven();
    TestNine();
    TestTen();

    cout << "Running Test 8..." << endl;
    TestEight();

    cout << "Test results: " << testPassRate << " / 10" << endl;
}
