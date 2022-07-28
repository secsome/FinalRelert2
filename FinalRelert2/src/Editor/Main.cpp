#include <Always.h>

#include <Conquer.h>
#include <Init.h>
#include <Uninit.h>

HINSTANCE ProgramInstance;
DWORD MainThreadId;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    ProgramInstance = hInstance;
    MainThreadId = GetCurrentThreadId();
    Init_Global();

    Log_Begin();

    if (!Setup_Mutex())
        return 0;

    if (Init_Parse_Command_Line(__argc, __argv))
    {
        Init_Random();
        Init_Keys();

        //new MFCD(R"(C:\Users\30270\Desktop\TerminatorV1.6\expandmo89.mix)", &PKey::FastKey);

        Init_MixFiles();
        Init_Language();
        if (Init_Check())
        {
            // Init App
        }

        Uninit_MixFiles();
    }

    Log_Close();

    return 0;
}