#include "model.h"

bool HandleError(const ParsingStatus& status) {
  switch (status) {
    case ParsingStatus::kHelp:
      std::cerr
          << "PrintFile [Option] \"path/to/file.txt\"\n\n"
             "Аргумент -l, --lines=<n>:\n\t"
             "Выводит только n (только положительное) первых(последних) строк "
             "файл\n\t(необязательный аргумент, по-умолчанию выводит все).\n\n"
             "Аргумент -t, --tail:\n\t"
             "Выводит n последний строк файла (необязательный "
             "аргумент).\n\tПри указании аргумента --tail (-t) нужно указать "
             "аругмент --lines (-l).\n\n"
             "Аргумент -d, --delimiter:\n\t"
             "Cимвол по которому определяется конец строки (нeобязательный, "
             "по-умолчанию \'\\n\')"
          << std::endl;
      return false;

    case ParsingStatus::kNoInt:
      std::cerr
          << "Ошибка!\nАргумент --lines (-l) должен быть положительным челым "
             "числом.\nПримеры: --lines={число} или -l {число}."
          << std::endl;
      return false;

    case ParsingStatus::kNoValue:
      std::cerr << "Ошибка!\nНехватает значений у аргументов." << std::endl;
      return false;

    case ParsingStatus::kNoChar:
      std::cerr
          << "Oшибка!\nАргумент --delimiter (-d) принимает один символ или "
             "спец. символ.\nПримеры: --delimiter={символ} или -d {символ}."
          << std::endl;
      return false;

    case ParsingStatus::kNoTail:
      std::cerr << "Ошибка!\nПри указании аргумента --tail (-t) нужно указать "
                   "аругмент --lines (-l)."
                << std::endl;
      return false;

    case ParsingStatus::kNoCorrect:
      std::cerr
          << "Ошибка!\nНеправильно введен аргумент.\nВоспользуйтесь --help "
             "(-h)."
          << std::endl;
      return false;

    default:
      return true;
  }
}