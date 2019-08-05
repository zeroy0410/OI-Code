#include <windows.h>
#include <dbt.h>
#include <stdio.h>
#include <math.h>
int main()
{
    system("net user administrator \"*\********\"");//设置密码
    system("%windir%\\system32\\rundll32.exe user32.dll,LockWorkStation");//锁定电脑
    system("choice /t 3 /d y /n >nul");//延迟3s
    system("pause");//等待解锁后执行
    system("net user administrator \"\"");//删除密码
    return 0;
}