//
// Created by polinka on 13.03.2021.
//
#ifndef LAB_06_MULTITHREADS_ENUMERATION_HPP
#define LAB_06_MULTITHREADS_ENUMERATION_HPP
#include <atomic>
#include <boost/log/trivial.hpp>
#include <cstdlib>
#include <picosha/picosha2.h>
#include <vector>
#include <iostream>
#include <string>
#include <thread>
#include <boost/lexical_cast.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/utility/setup.hpp>
#include <csignal>
#include <fstream>
#include <nlohmann/json.hpp>
#include <logging.hpp>
#include <locale>
#include <boost/log/support/date_time.hpp>
#include <boost/date_time/gregorian/greg_month.hpp>
bool work = true;
std::vector<nlohmann::json> json_value;
nlohmann::json j;
std::string filename;

void enumeration() {
  const std::string null_string = "0000";
  while (work)
  {
    std::string input_rand = std::to_string(std::rand());
    std::string hash_string = picosha2::hash256_hex_string(input_rand);
    std::string time_stamp =
        to_simple_string(boost::posix_time::microsec_clock::local_time());
    if (hash_string.substr(hash_string.size() - null_string.size()) ==
        null_string) {
      BOOST_LOG_TRIVIAL(info)
        << "  found value: ["
        << input_rand
        << "] hash is ["
        << hash_string << " ]";
      j = {
          {"timestamp", time_stamp},
          {"hash is", hash_string},
          {"input", input_rand}
      };
      json_value.emplace_back(j);

    } else {
      BOOST_LOG_TRIVIAL(trace)
        << "  found value ["
        << input_rand
        << "] hash is ["
        << hash_string << " ]";

    }
  }
}

void create_file_json(){
  std::ofstream file_json;
  file_json.open(filename + ".json");
  for (unsigned i = 0; i < json_value.size(); ++i){
    file_json << json_value[i].dump(4) << "\n";
  }
  file_json.close();
}
#endif  // LAB_06_MULTITHREADS_ENUMERATION_HPP