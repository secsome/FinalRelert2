#include <Always.h>

#include <Conquer.h>
#include <Init.h>
#include <Uninit.h>

#include <CApp.h>
#include <LanguageManager.h>

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

        Init_MixFiles();
        Init_Language();
        if (Init_Check())
        {
            if (LanguageManager::Current.Load("FinalRelert2.csf"))
                CApp::Run();
            else
                ::MessageBox(NULL, "Cannot load FinalRelert2.csf!", "Error", MB_OK);
        }

        Uninit_MixFiles();
    }

    Log_Close();

    return 0;
}
