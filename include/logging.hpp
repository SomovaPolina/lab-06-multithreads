// Copyright 2021 Polinka <zagigalka_60@mail.ru>
#ifndef INCLUDE_LOGGING_HPP_
#define INCLUDE_LOGGING_HPP_
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/expressions/attr_fwd.hpp>
#include <boost/log/expressions/attr.hpp>
#include <string>

//BOOST_LOG_ATTRIBUTE_KEYWORD(timeline, "Timeline", attrs::timer::value_type);
const unsigned ten_MiB = 10 * 1024 * 1024;
void init()
{
  const std::string format = "%TimeStamp% <%Severity%> (%ThreadID%): %Message%";
  auto sink_to_file_trace = boost::log::add_file_log(
      boost::log::keywords::file_name = "logs/trace/log_trace_%N.log",
      boost::log::keywords::rotation_size = ten_MiB,
      boost::log::keywords::format = format);
  sink_to_file_trace->set_filter(
      boost::log::trivial::severity == boost::log::trivial::trace);

  auto sink_to_file_info = boost::log::add_file_log(
      boost::log::keywords::file_name = "logs/info/log_info_%N.log",
      boost::log::keywords::rotation_size = ten_MiB,
      boost::log::keywords::format = format);
  sink_to_file_info->set_filter(
      boost::log::trivial::severity == boost::log::trivial::info);

  auto sink_to_console = boost::log::add_console_log(
      std::cout,
      boost::log::keywords::format = format);
  sink_to_console->set_filter(
      boost::log::trivial::severity == boost::log::trivial::info);

  boost::log::add_common_attributes();
}
#endif  // INCLUDE_LOGGING_HPP_
