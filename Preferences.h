/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Preferences.h
 * Author: martin
 *
 * Created on 25. Juni 2017, 16:44
 */

#ifndef PREFERENCES_H
#define PREFERENCES_H

#include "std.h"

static const std::string PREFERENCES_PATHNFILE = "/home/martin/projects/cpp/FastSql/preferences/Preferences.txt";

class Preferences {
public:
    static Preferences& instance();
    
    bool getMruListPath( std::string& path );
    
    virtual ~Preferences();
private:
    Preferences();
    void readPreferences();
    bool getValue( const std::string& key, std::string& value ) const;
    void checkPreferencesRead();
private:
    static Preferences *_pThis;
    std::vector<std::string> _preferences;
};

#endif /* PREFERENCES_H */

