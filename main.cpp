#include "model.h"

int main(const int argc, const char** argv) {
  Args file_args = {0, ParsingStatus::kGood, false, '\n', ""};

  ParseArg(argc, argv, file_args);

  if (HandleError(file_args.status)) ReadFile(file_args);
}