/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MruStore.h
 * Author: martin
 *
 * Created on 24. Juni 2017, 19:51
 */

#ifndef MRUSTORE_H
#define MRUSTORE_H

#include "std.h"
#include "Mru.h"

const std::string MRULIST = "mrulist.txt";

/**Aufbau der MRU-Datei:
    Pfadname/Queryfilename.<appendix>
 */

class MruStore {
public:
    static MruStore& instance();
    
    /**liest die MRU-Einträge aus der in den Preferences angegebenen
       Datei und liefert sie als eine Struktur vom Typ
       MruList zurück*/
    const MruList& getMruList();
    
    /**fügt der MRU-Liste einen MRU-Eintrag hinzu*/
    void addMru( const std::string& pathnfile );
    
    /**speichert die MRU-Liste in der in den Preferences angegebenen Datei*/
    void saveMruList();
    
    virtual ~MruStore();
    
private:
    MruStore();
    void getMruListPath( std::string& path ) const;
    void getMruFromString( const std::string& line, Mru& mru );
    
private:
    static MruStore *_pThis;
    
    MruList _mruList;

};

#endif /* MRUSTORE_H */

