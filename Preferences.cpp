/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Preferences.cpp
 * Author: martin
 * 
 * Created on 25. Juni 2017, 16:44
 */

#include "Preferences.h"
#include "FileIO.h"

using namespace std;

Preferences *Preferences::_pThis = 0;

Preferences& Preferences::instance() {
    if( !_pThis ) {
        _pThis = new Preferences();
    }
    return *_pThis;
}

bool Preferences::getMruListPath( string& path ) {
    checkPreferencesRead();
    return getValue( "mrulistpath", path );
}

bool Preferences::getValue( const std::string& key, std::string& value ) const {
    for( auto itr = _preferences.begin(); itr != _preferences.end(); itr++ ) {
        const string& pref = *itr;
        int n = pref.find( key );
        if( n != string::npos ) {
            n = pref.find( "=" );
            if( n != string::npos ) {
                value = pref.substr( n + 1 );
                return true;
            }
        }
    }
    return false;
}

void Preferences::checkPreferencesRead() {
    if( _preferences.empty() ) {
        readPreferences();
    }
}

void Preferences::readPreferences() {
    FileIO::instance().readFile( PREFERENCES_PATHNFILE, _preferences );
}

Preferences::Preferences() {
}

Preferences::~Preferences() {
}

