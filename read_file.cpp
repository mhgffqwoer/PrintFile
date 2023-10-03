#include "model.h"

void ReadFile(const Args& file_args) {
  std::ifstream file(file_args.path_to_file);

  if (!file.is_open()) {
    std::cerr << "Невозможно открыть файл.";
    return;
  }

  char ch;
  int64_t cnt_lines = file_args.lines;
  if (file_args.is_tail) [[unlikely]] {
    file.seekg(-1, std::ios::end);
    int64_t start = 0;
    int64_t pos = file.tellg();
    int64_t i = 1;
    while ((i <= pos) && cnt_lines) {
      file.seekg(-i, std::ios::end);
      if (file.get() == file_args.delimiter) {
        start = -i;
        cnt_lines--;
      }
      i++;
    }

    file.seekg(start, std::ios::end);

    while (file.get(ch)) {
      std::cout << ch;
    }

  } else {
    char ch;
    while (file.get(ch) && cnt_lines) {
      if (ch == file_args.delimiter) {
        cnt_lines--;
      }
      std::cout << ch;
    }
  }
}