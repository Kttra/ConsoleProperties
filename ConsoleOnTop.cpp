/*  The purpose of this program is made to showcase how to edit the properties of the command window.
    The main OS this program will focus on is windows. However, the Clear command will explain how
    to clear the console for Linux and Apple devices.
*/
#include <windows.h>
#include <iostream>
#include <string>

void cls(HANDLE hConsole);
void AlwaysOnTop();
void SetWindow(int Width, int Height);
void Clear();
void NotAlwaysOnTop();

int main(){
    //Start of the program
    std::cout << "Program that changes the properties of the console window." << std::endl;
    std::string userInput;

    //Clear Feature (For different OS)
    std::cout << "Press enter for a multiplatform clear." << std::endl;
    getline(std::cin, userInput);
    Clear();

    //Clear Feature (Specific for windows)
    std::cout << "Press enter for a windows specific clear." << std::endl;
    getline(std::cin, userInput);
    HANDLE hStdout;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    cls(hStdout);

    //Always on top feature
    std::cout << "Press enter to see the always on top feature." << std::endl;
    getline(std::cin, userInput);
    AlwaysOnTop();

    //Turn off on top feature
    std::cout << "Press enter to disable the always on top feature." << std::endl;
    getline(std::cin, userInput);
    NotAlwaysOnTop();

    //Window size change
    std::cout << "Press enter to change the window size" << std::endl;
    getline(std::cin, userInput);
    SetWindow(80, 25);

    //Windows position change
    std::cout << "Press enter to change the window position" << std::endl;
    getline(std::cin, userInput);
    HWND consoleWindow = GetConsoleWindow();
    SetWindowPos( consoleWindow, 0, 1255, 50, 0, 0, SWP_NOSIZE | SWP_NOZORDER );

    //Exit program
    std::cout << "Press enter to terminate the program" << std::endl;
    getline(std::cin, userInput);
    return 1;
}

void AlwaysOnTop(){
    HWND consoleWindowHandle = GetConsoleWindow();

    if( consoleWindowHandle ){
        SetWindowPos(
            consoleWindowHandle, // window handle
            HWND_TOPMOST, // "handle to the window to precede
                        // the positioned window in the Z order
                        // OR one of the following:"
                        // HWND_BOTTOM or HWND_NOTOPMOST or HWND_TOP or HWND_TOPMOST
            0, 0, // X, Y position of the window (in client coordinates)
            0, 0, // cx, cy => width & height of the window in pixels
            SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW // The window sizing and positioning flags.
        );
        // OPTIONAL ! - SET WINDOW'S "SHOW STATE"
        ShowWindow(
            consoleWindowHandle, // window handle
            SW_NORMAL // how the window is to be shown
                    // SW_NORMAL => "Activates and displays a window.
                    // If the window is minimized or maximized,
                    // the system restores it to its original size and position.
                    // An application should specify this flag
                    // when displaying the window for the first time."
        );
    } else {
        std::cout << std::endl << "There is no console window associated with this app";
    }
}

void NotAlwaysOnTop(){
    HWND consoleWindowHandle = GetConsoleWindow();

    if( consoleWindowHandle ){
        SetWindowPos(
            consoleWindowHandle, // window handle
            HWND_NOTOPMOST, // "handle to the window to precede
                        // the positioned window in the Z order
                        // OR one of the following:"
                        // HWND_BOTTOM or HWND_NOTOPMOST or HWND_TOP or HWND_TOPMOST
            0, 0, // X, Y position of the window (in client coordinates)
            0, 0, // cx, cy => width & height of the window in pixels
            SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW // The window sizing and positioning flags.
        );
        // OPTIONAL ! - SET WINDOW'S "SHOW STATE"
        ShowWindow(
            consoleWindowHandle, // window handle
            SW_NORMAL // how the window is to be shown
                    // SW_NORMAL => "Activates and displays a window.
                    // If the window is minimized or maximized,
                    // the system restores it to its original size and position.
                    // An application should specify this flag
                    // when displaying the window for the first time."
        );
    } else {
        std::cout << std::endl << "There is no console window associated with this app";
    }
}

void SetWindow(int Width, int Height){ 
    _COORD coord; 
    coord.X = Width; 
    coord.Y = Height; 

    _SMALL_RECT Rect; 
    Rect.Top = 0; 
    Rect.Left = 0; 
    Rect.Bottom = Height - 1; 
    Rect.Right = Width - 1; 

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
    SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
} 

//Clearing console without system commands
void cls(HANDLE hConsole){
   COORD coordScreen = {0, 0};    // home for the cursor
   DWORD cCharsWritten;
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   DWORD dwConSize;

    // Get the number of character cells in the current buffer.

   if(!GetConsoleScreenBufferInfo(hConsole, &csbi))
      return;
   dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

   // Fill the entire screen with blanks.

   if(!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
      dwConSize, coordScreen, &cCharsWritten))
      return;

   // Get the current text attribute.

   if(!GetConsoleScreenBufferInfo( hConsole, &csbi))
      return;

   // Set the buffer's attributes accordingly.

   if(!FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
      dwConSize, coordScreen, &cCharsWritten))
      return;

   // Put the cursor at its home coordinates.

   SetConsoleCursorPosition(hConsole, coordScreen);
}

//Clear using system specific commands
void Clear(){
    #if defined _WIN32
        system("cls");
        //clrscr(); // including header file : conio.h
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
        //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
    #elif defined (__APPLE__)
        system("clear");
    #endif
}