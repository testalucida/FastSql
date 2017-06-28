/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileIO.cpp
 * Author: martin
 * 
 * Created on 25. Juni 2017, 09:40
 */

#include "FileIO.h"

using namespace std;

FileIO *FileIO::_pThis = 0;

FileIO& FileIO::instance() {
    if( !_pThis ) {
        _pThis = new FileIO();
    }
    return *_pThis;
}


void FileIO::getPathNormalized( string path ) const {
    //sicherstellen, dass der Pfad mit "/" endet
    unsigned char lastpos = path.size() - 1;
    char last = path.at( lastpos ); 
    
    if( last == '\\' ) {
        path.replace( lastpos, 1, "/" );
    }
    if( last != '/' )  {
        path.append( "/" );
    }
}

bool FileIO::readFile( const string& pathnfile, vector<string>& lines ) const {
    ifstream in( pathnfile );
    if( in.is_open() ) {
        string line;
        while( getline( in, line ) ) {
            lines.push_back( line );
        }
        in.close();
        return true;
    }
    return false;
}

 bool FileIO::writeFile( const string &pathnfile, const vector<string>& lines ) const {
     ofstream out( pathnfile );
     if( out.is_open() ) {
         for_each( lines.begin(), lines.end(), [&]( const string& line ) {
             out.write( line.c_str(), line.size() );
         });
         out.close();
         return true;
     }
     return false;
 }

FileIO::FileIO() {
}


FileIO::~FileIO() {
}

