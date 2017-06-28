/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MruStore.cpp
 * Author: martin
 * 
 * Created on 24. Juni 2017, 19:51
 */

#include "MruStore.h"
#include "FileIO.h"
#include "Preferences.h"

using namespace std;

MruStore *MruStore::_pThis = 0;

MruStore& MruStore::instance() {
    if( !_pThis ) {
        _pThis = new MruStore();
    }
    return *_pThis;
}

const MruList& MruStore::getMruList() {
    //den Pfad der MRU-Datei von den Preferences holen:
    string pathnfile;
    getMruListPath( pathnfile );
    
    //wenn der Pfad sich geändert hat, müssen wir die Liste neu einlesen:
    if( pathnfile != _mruList.path ) {
        _mruList.queries.clear();
        _mruList.path = pathnfile;
    }
    
    if( _mruList.queries.size() < 1 ) { 
        pathnfile.append( MRULIST );
        vector<string> lines;
        FileIO::instance().readFile( pathnfile, lines );
        for_each( lines.begin(), lines.end(), [&]( string &line ) {
            Mru mru;
            getMruFromString( line, mru );
            _mruList.queries.push_back( mru );
        });
    }
    
    return _mruList;
}
    
void MruStore::getMruListPath( string& path ) const {
    Preferences::instance().getMruListPath( path );
    
    //sicherstellen, dass der Pfad mit "/" endet
    FileIO::instance().getPathNormalized( path );
}

void MruStore::getMruFromString( const std::string& line, Mru& mru ) {
    int n = line.find_last_of( '/') ;
    if( n == string::npos ) {
        n = line.find_last_of( '\\' );
    }
    
    mru.querypath = line.substr( 0, ++n);
    
    string queryfile = line.substr( n );
    n = queryfile.find_last_of( '.' );
    mru.queryname = queryfile.substr( 0, n );
    mru.appendix = queryfile.substr( n );
}

void MruStore::addMru( const std::string& pathnfile ) {
    Mru mru;
    getMruFromString( pathnfile, mru );
    _mruList.queries.push_back( mru );
}

void MruStore::saveMruList() {
    //den Pfad der MRU-Datei von den Preferences holen:
    string pathnfile;
    getMruListPath( pathnfile );
    
    vector<string> lines;
    for_each( _mruList.queries.begin(), _mruList.queries.end(), [&lines]( Mru& mru ) {
        string line( mru.querypath );
        line.append( mru.queryname ).append( mru.appendix );
        lines.push_back( line );
    });
    
    FileIO::instance().writeFile( pathnfile, lines );
}

MruStore::MruStore() {
}


MruStore::~MruStore() {
}

