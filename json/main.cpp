#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/date_time.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <exception>
#include <cassert>

using namespace boost::property_tree;
using namespace boost;
using namespace std;

int main() {
		try {
//				std::stringstream ss;
				ptree pt;
				read_json("a.json", pt);

				BOOST_FOREACH(ptree::value_type &v, pt.get_child("particles")) {
						assert(v.first.empty());
						cout << v.second.data() << endl;
				}
				return 0;
				
		} catch (std::exception const& e) {
				cerr << e.what() << endl;
		}
		return 0;
}

