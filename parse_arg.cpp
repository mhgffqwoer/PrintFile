#include "model.h"

void InItSymbol(const std::string& value, Args& file_args) {
  if (value.length() == 1) {
    file_args.delimiter = value[0];
  } else if (value.length() == 2) {
    switch (value[1]) {
      case 'n':
        file_args.delimiter = '\n';
        break;

      case 't':
        file_args.delimiter = '\t';
        break;

      case 'b':
        file_args.delimiter = '\b';
        break;

      case '0':
        file_args.delimiter = '\0';
        break;

      default:
        file_args.delimiter = value[1];
        break;
    }
  } else {
    file_args.status = ParsingStatus::kNoChar;
    file_args.delimiter = '\n';
  }
}

void InItArg(const std::string& name_arg, const std::string& value,
             Args& file_args) {
  if ((name_arg == "-t") || (name_arg == "--tail")) {
    file_args.is_tail = true;

  } else if ((name_arg == "-l") || (name_arg == "--lines")) {
    try {
      file_args.lines = std::stoi(value);
    } catch (...) {
      file_args.status = ParsingStatus::kNoInt;
    }

  } else if ((name_arg == "-d") || (name_arg == "--delimiter")) {
    InItSymbol(value, file_args);

  } else {
    file_args.status = ParsingStatus::kNoCorrect;
  }
}

void ParseArg(const int argc, const char** argv, Args& file_args) {
  for (int i = 1; i < argc; i++) {
    std::string arg = std::string(argv[i]);
    std::string value;
    std::string name_arg;

    if ((i == 1) && ((arg == "--help") || (arg == "-h"))) {
      file_args.status = ParsingStatus::kHelp;
      return;
    }

    if ((arg.length() == 2) && (arg[0] == '-')) {
      if (arg != "-t") {
        if ((i + 1) < argc) {
          name_arg = arg;
          value = std::string(argv[i + 1]);
          i++;
        } else {
          file_args.status = ParsingStatus::kNoValue;
          return;
        }
      } else {
        name_arg = arg;
      }
    } else if ((arg.length() > 2) && (arg[0] == '-')) {
      if (arg != "--tail") {
        int flag = arg.find("=");
        name_arg = arg.substr(0, flag);
        value = arg.substr(flag);
      } else {
        name_arg = arg;
      }
    } else {
      file_args.path_to_file = arg;
      continue;
    }

    InItArg(name_arg, value, file_args);
  }

  if (file_args.is_tail && !file_args.lines &&
      file_args.status != ParsingStatus::kNoInt) {
    file_args.status = ParsingStatus::kNoTail;
  }
}
