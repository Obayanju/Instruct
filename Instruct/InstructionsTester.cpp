#include <iostream>
#include "instructions.h"
using namespace std;

int main()
{
    /*unsigned char mCode[] = { 0x55, 0x8B, 0xEC, 0x5d, 0XC3 };
    cout << "About to Execute the machine code ...\n";
    void* ptr = mCode;
    void (*f)(void);
    f = (void (*)(void)) ptr;
    f();
    cout << "\nThere and back again!" << endl;
    return 0;*/
    InstructionsClass code;
    code.PushVariable(10);
    code.PopAndStore(11);
    code.PushVariable(10);
    code.PushVariable(11);
    code.PopPopAddPush();
    code.PopAndWrite(); // Should print 4000
    code.Finish();
    code.Execute();
    cout << "Success!";
    return 0;
}
