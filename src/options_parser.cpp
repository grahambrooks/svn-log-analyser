#include <list>
#include <ostream>
#include "options_parser.hpp"

options_parser::options_parser() : output(std::cout){}

options_parser::options_parser(std::ostream& output) : output(output) {
  std::list<std::string> items;
}

void options_parser::parse(int argc, const char * argv[], command_options& options) {

  boost::program_options::options_description opts("Options");
 
  add_visible_options(opts);

  boost::program_options::options_description hidden("Hidden options");
  
  add_hidden_options(hidden);

  boost::program_options::options_description cmdline_options;
  cmdline_options.add(opts).add(hidden);

  boost::program_options::positional_options_description p;
  p.add("input-file", -1);
  
  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(cmdline_options).positional(p).run(), vm);
  boost::program_options::notify(vm);

  if (vm.count("help")) {
    output << opts << "\n";
  }

  if (vm.count("format")) {
    const string_vector& formats = vm["format"].as<std::vector<std::string> >();

    options.format = formats[0];
  }
  
  if (vm.count("input-file")) {
    const std::vector<std::string>& files = vm["input-file"].as<std::vector<std::string> >();

    for(std::vector<std::string>::const_iterator i = files.begin(); i != files.end(); ++i) {
      options.input_files.push_back(*i);
    }
  }
}

void options_parser::add_visible_options(boost::program_options::options_description& opts) {
  opts.add_options()
    ("help,h", "Produce help message") 
    ("format,f", boost::program_options::value< std::vector<std::string> >(), "Specify the output format (csv)") 
    ;
}

void options_parser::add_hidden_options(boost::program_options::options_description& opts) {
 opts.add_options()
    ("input-file", boost::program_options::value< std::vector<std::string> >(), "input file")
    ;
}
