  #define SYS_CONFIG_FILE "/etc/file.conf"
  #include <string>
  #include <algorithm>
  #include <vector>
  #include <cctype>
  #include <iostream>
  #include <fstream>

  using namespace std;

  void zliczanieCzasu() {
    string::size_type posBeginIdx, posEndIdx;
    string::size_type ipos=0;
    string            sLine, sValue;
    string            sKeyWord;
    string sError;
    const string      sDelim( ":" );

    ifstream myInputFile(SYS_CONFIG_FILE, ios::in);
    if( !myInputFile )
    {
       sError = "File SYS_CONFIG_FILE could not be opened";
       //return sError; // ERROR
        return;
    }

    while( getline(myInputFile,sLine) )
    {
       if( sLine.empty() );                     // Ignore empty lines
       else
       {
          posEndIdx = sLine.find_first_of( sDelim );
          sKeyWord  = sLine.substr( ipos, posEndIdx ); // Extract word
          posBeginIdx = posEndIdx + 1;  // Beginning of next word (after ':')
       }
    }
  }
