#pragma once
#include <fstream>
#include <iostream>
#include <string>


enum class ParsingStatus {
  kHelp,
  kGood,
  kNoInt,
  kNoChar,
  kNoCorrect,
  kNoValue,
  kNoTail,
};

struct Args {
  int64_t lines;
  ParsingStatus status;
  bool is_tail;
  char delimiter;
  std::string path_to_file;
};

void ParseArg(const int argc, const char** argv, Args& file_args);

bool HandleError(const ParsingStatus& status);

void ReadFile(const Args& file_args);