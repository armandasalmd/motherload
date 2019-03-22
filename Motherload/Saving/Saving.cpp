
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Map.h"
#include <archive/tmpdir.hpp>
#include <archive/text_iarchive.hpp>
#include <archive/text_oarchive.hpp>
#include <serialization/base_object.hpp>
#include <serialization/utility.hpp>
#include <serialization/list.hpp>
#include <serialization/assume_abstract.hpp>
#include <property_tree/ptree.hpp>
#include <property_tree/json_parser.hpp>
#include <modelObject>
#include <models>

using property_tree::ptree;
using property_tree::read_json;
using property_tree::write_json;
//pulls functions from BOOST library

struct ReadWrite // Contains our json conversion tools 
{

    void ReadWrite() {
    // Converts inputs to JSON
    ptree pt;
    pt.put ("test", "test");
    std::ostringstream buf; 
    write_json (buf, pt, false);
    std::string json = buf.str();

    // Checks output
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);
    std::string foo = pt2.get<std::string> ("testtest"); // checks to see if inputs are combined correctly
    }

    std::string map2json (const std::mapGet()<std::string, std::string>& mapGet()) { // Uses BOOST functions to convert strings to JSON format (Cleaner in SQL)
    ptree pt; 
    for (auto& entry: map) 
        pt.put (entry.first, entry.second);
    std::ostringstream buf; 
    write_json (buf, pt, false); 
    return buf.str();
    }

    
   Save_State(){;
    Save_State(int _d, int _m, float _s) : 
        degrees(_d), minutes(_m), seconds(_s)
   }
}


struct Update  // Provides a method of communicating to the database in order to update an existing row
{
    int Update()
    {
        StderrLog log;
        Database db("localhost", "root", "", "modelObject", &log); // MySQL specific
        if (!db.Connected())
        {
            printf("Database not connected - exiting\n"); // Console check for Bug testing table
            exit(-1);
        }
        Query q(db);
        q.execute("Update mapData set name = 'Save num+1' where num=>1");
    }
}

struct Load // Provides a method of communicating to the database in order to read an existing row
{
    int Load()
    {
        StderrLog log;
        Database db("localhost", "root", "", "modelObject", &log); // MySQL specific
        if (!db.Connected())
        {
            printf("Database not connected - exiting\n"); // Console check for Bug testing table
            exit(-1);
        }
        Query q(db);
        q.get_result("select * from MapID"); // Selects MapID table
        while (q.fetch_row())
        {
            long num = q.getval();
            std::string name = q.getstr();
            printf("#%ld: %s\n", num, name.c_str());
        }
        q.free_result(); // Frees table for PlayerID lookup

                Query q(db);
        q.get_result("select * from PlayerID"); // Selects PlayerID table
        while (q.fetch_row())
        {
            long num = q.getval();
            std::string name = q.getstr();
            printf("#%ld: %s\n", num, name.c_str());
        }
        q.free_result(); // frees Database for use
    }
}

struct Save // Creates public Save struct 
{
    int Save()
    {
        StderrLog log;
        Database db("localhost", "root", "", "modelObject", &log); // MySQL specific
        if (!db.Connected())
        {
            printf("Database not connected - exiting\n"); // Console check for Bug testing table
            exit(-1);
        }
        Query q(db);
        q.get_result(
            "select playerID.name,mapID.name,SaveID.amount from saves as x" // Feeds SQL codes to SQLite table
            "insert player = playerID.num, getMap = MapID"); // Inserts MapID data from 
        while (q.fetch_row()) // Iterates through rows 
        {
            std::string playerID = q.getstr();
            std::string mapID= q.getstr();
            long value = q.getval();
            printf("%s saved %ld \n",
                SaveID.c_str(),
                amount,
                (amount == 1) ? "" : "s",
                SaveID.c_str());
        }
        q.free_result(); // Frees table for other uses
}
