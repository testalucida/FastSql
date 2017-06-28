#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include "DialogStore.h"
#include "Mru.h"
#include "MruStore.h"
#include "std.h"

using namespace std;

int main() {
//    const MruList& mruList = MruStore::instance().getMruList();
//    MruStore::instance().addMru("/home/martin/projects/cpp/FastSql/testsql/myquery_3.sql");
//    MruStore::instance().saveMruList();
//    const MruList& mruList2 = MruStore::instance().getMruList();
    
    const char *pLocale = setlocale( LC_ALL, "" );
    
    DialogStore::instance().addDialog( 100, 100 );
  
    return Fl::run();
}