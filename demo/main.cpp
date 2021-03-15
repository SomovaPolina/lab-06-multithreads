#include <enumeration.hpp>
#include "logging.hpp"
#include <thread>
#include <csignal>
#include <nlohmann/json.hpp>
void sig_handler_exit(int sig)
{
  create_file_json();
  exit(sig);
}

int main(int argc, char *argv[]) {
  signal(SIGINT, &sig_handler_exit);
  std::cin.tie(NULL);
  init();
  unsigned thread_count;
  if (argc == 1) {thread_count = std::thread::hardware_concurrency();} else
  if (argc == 2) {thread_count = boost::lexical_cast<unsigned>(argv[1]);}
  else if (argc == 3)
  {thread_count = boost::lexical_cast<unsigned>(argv[1]);
    getFilename() = boost::lexical_cast<std::string>(argv[2]);
  } else throw std::runtime_error("Wrong parameters!");

  BOOST_LOG_TRIVIAL(trace) << "  THREADS COUNT: " << thread_count;
  BOOST_LOG_TRIVIAL(info) << "  THREADS COUNT: " << thread_count;
  std::vector<std::thread> threads;
  threads.reserve(thread_count);
  for (unsigned i = 0; i < thread_count; ++i) {
    threads.emplace_back(enumeration);
  }
  for (std::thread &thr : threads) {
    thr.join();
  }
  return 0;
}