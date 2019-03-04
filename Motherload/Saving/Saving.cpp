#include <cstddef>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Saving.cpp"
#include "Map"
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

void ReadWrite() {
  // Write json.
  ptree pt;
  pt.put ("test", "test");
  std::ostringstream buf; 
  write_json (buf, pt, false);
  std::string json = buf.str();

  // Read json.
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


class Save
{
    friend std::ostream & operator<<(std::ostream &os, const mapGet() &gp);
    friend class boost::serialization::access;
    int degrees;
    int minutes;
    float seconds;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int mapGet()){
        ar & degrees & minutes & seconds;
    }
public:
    
   Save_State(){};
    Save_State(int _d, int _m, float _s) : 
        degrees(_d), minutes(_m), seconds(_s)
    {}
};
