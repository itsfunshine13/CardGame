# CardGame

## Setting Up Build Software
1. Python (2.7, 3.4+)
   Python Download Site: https://www.python.org/downloads/
  - This is needed if you make changes to cardList.xls in which you'll need to regenerate cardData.json file.
  - If regenerating the file run:
    /CardGame/CPP/CardData/python genCardData.py --file cardList.xls
  - For more info run
    genCardData.py --help
2. Cygwin64
  Cygwin Download Site: https://cygwin.com/
  1. Run the default install but you will also need to install "make"
  2. Search for "make" in the search tab
  3. Expand devel
  4. Search for "The GNU version of the 'make' utility'". The Package name should just be "make"
  5. Go to the cygwin bin directory and verify that the application "make" exists
     Example Path:
       C:\cygwin64\bin
3. Update Environment Variables
   1. In the windows search bar, search for and click on "Edit the system environment variables"
   2. In the System Properties window, click on "Environment Variables"
   3. In the Environment Variables window, under 'System variables' pane, highlight 'Path', then click Edit
   4. Check if the path for Python and Cygwin bin is listed
      Example Path for Python:
        C:\Python310
      Example Path for Cygwin:
        C:\cygwin64\bin

## Building
Open a powershell or command prompt window in /CardGame/CPP/ and run 'make'
Or open powershell or command prompt window anywhere and cd to the downloaded code.

Example: If the downloaded code was put in C:\ run the following
'cd C:\CardGame\CPP\'
'make'

## Executables After Build
/CardGame/CPP/cardgame.exe

## Run the game
Run cardgame.exe 
