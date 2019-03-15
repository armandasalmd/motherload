
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


class Save
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
    std::string foo = pt2.get<std::string> ("testtest");
    }

    std::string map2json (const std::mapGet()<std::string, std::string>& mapGet()) {
    ptree pt; 
    for (auto& entry: map) 
        pt.put (entry.first, entry.second);
    std::ostringstream buf; 
    write_json (buf, pt, false); 
    return buf.str();
    }
    public:
    
   Save_State(){;
    Save_State(int _d, int _m, float _s) : 
        degrees(_d), minutes(_m), seconds(_s)
   }
}


struct Update
{
    int Update()
    {
        StderrLog log;
        Database db("localhost", "root", "", "modelObject", &log); // MySQL specific
        if (!db.Connected())
        {
            printf("Database not connected - exiting\n");
            exit(-1);
        }
        Query q(db);
        q.execute("Update mapData set name = 'Save num+1' where num=>1");
    }
}

struct Load
{
    int Load()
    {
        StderrLog log;
        Database db("localhost", "root", "", "modelObject", &log); // MySQL specific
        if (!db.Connected())
        {
            printf("Database not connected - exiting\n");
            exit(-1);
        }
        Query q(db);
        q.get_result("select * from MapID");
        while (q.fetch_row())
        {
            long num = q.getval();
            std::string name = q.getstr();
            printf("#%ld: %s\n", num, name.c_str());
        }
        q.free_result();

                Query q(db);
        q.get_result("select * from PlayerID");
        while (q.fetch_row())
        {
            long num = q.getval();
            std::string name = q.getstr();
            printf("#%ld: %s\n", num, name.c_str());
        }
        q.free_result();
    }
}

struct Save
{
    int Save()
    {
        StderrLog log;
        Database db("localhost", "root", "", "modelObject", &log); // MySQL specific
        if (!db.Connected())
        {
            printf("Database not connected - exiting\n");
            exit(-1);
        }
        Query q(db);
        q.get_result(
            "select playerID.name,mapID.name,SaveID.amount from saves as x"
            "insert player = playerID.num, getMap = MapID");
        while (q.fetch_row())
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
        q.free_result();
}
