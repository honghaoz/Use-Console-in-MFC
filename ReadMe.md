Using Console in MFC
=====================

**例如一个对话框程序。**

```
BOOL CTDlg::OnInitDialog()
{
	::AllocConsole(); // 打开控制台资源
	freopen("CONOUT$", "w+t", stdout); // 申请写
	freopen("CONIN$","r+t",stdin);
}
```

**然后在需要用到的地方添加这段代码：**

```
#ifndef __GUICON_H__
#define __GUICON_H__
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
using namespace std;

// maximum mumber of lines the output console should have
static const WORD MAX_CONSOLE_LINES = 500;
void RedirectIOToConsole();
void RedirectIOToConsole()
{
	int hConHandle;
	HANDLE lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;
	// allocate a console for this app
	AllocConsole();
	// set the screen buffer to be big enough to let us scroll text

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
 	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
 	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);
 	// redirect unbuffered STDOUT to the console
 	lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
 	hConHandle = _open_osfhandle((INT_PTR)lStdHandle, _O_TEXT);
 	fp = _fdopen( hConHandle, "w" );
 	*stdout = *fp;
 	setvbuf( stdout, NULL, _IONBF, 0 );
 	// redirect unbuffered STDIN to the console
 	lStdHandle = GetStdHandle(STD_INPUT_HANDLE);
 	hConHandle = _open_osfhandle((INT_PTR)lStdHandle, _O_TEXT);
 	fp = _fdopen( hConHandle, "r" );
 	*stdin = *fp;
 	setvbuf( stdin, NULL, _IONBF, 0 );
 	// redirect unbuffered STDERR to the console
 	lStdHandle = GetStdHandle(STD_ERROR_HANDLE);
 	hConHandle = _open_osfhandle((INT_PTR)lStdHandle, _O_TEXT);
 	fp = _fdopen( hConHandle, "w" );
 	*stderr = *fp;
 	setvbuf( stderr, NULL, _IONBF, 0 );
 	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog 
 	// point to console as well
 	ios::sync_with_stdio();
}
#endif 
```
**然后就可以用cout在console里输出了。**

**最后，记得在结束程序钱释放掉。**

```
AllocConsole();  
freopen("CONOUT$","w+t",stdout);  
freopen("CONIN$","r+t",stdin);  
cout << "Input:" <<endl;
int iTest = 0;
cin >> iTest;
fclose(stdout);
fclose(stdin);
FreeConsole();
```


_Reference:_ 

<http://blog.csdn.net/everettjf/article/details/5931043>
<http://blog.csdn.net/acaiacc/article/details/5543669>
<http://ygdljg.blog.163.com/blog/static/54601046200893042229423/>

<http://blog.csdn.net/VisualEleven/article/details/5517541>
<http://nianning1981.blog.163.com/blog/static/30830143201002632546873/>

