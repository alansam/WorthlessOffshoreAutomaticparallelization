
#include <iostream>
#include <iomanip>
#include <string>
#include <numeric>
#include <cctype>
#include <clocale>

using namespace std::literals::string_literals;

void isspace_ctype(void);
void isspace_locale(void);

int main(int argc, char const * argv[argc]) {

  isspace_ctype();
  isspace_locale();

  return 0;
}

void isspace_ctype(void) {
  std::cout << "function: "s << __func__ << std::endl;

  std::string words { "a quick brown fox jumps over the lazy dog"s };
  std::cout << "string: "s << words << std::endl;
  //  count of spaces in the string
  auto spaces =
  std::accumulate(words.begin(), words.end(), 0,
                  [](auto c1, auto c2) {
    auto cr = c1 + (std::isspace(c2) ? 1 : 0);
#ifdef AS_DEBUG__
    std::cout << c1 << ' ' << c2 << ' ' << cr << '\n';
#endif
    return cr;
  });
  std::cout << "spaces: "s << spaces << '\n' << std::endl;
}

void isspace_locale(void) {
  std::cout << "function: "s << __func__ << std::endl;

  auto try_with = [](wchar_t c_, char const * loc) {
    std::wcout << L"isspace('"
               << c_
               << L"', locale(\""
               << loc
               << L"\")) returned "
               << std::boolalpha
               << std::isspace(c_, std::locale(loc))
               << L'\n';
  };

   wchar_t const EM_SPACE = L'\u2003'; // Unicode character 'EM SPACE'
  try_with(EM_SPACE, "C");
  try_with(EM_SPACE, "en_US.UTF8");
  try_with(L' ', "C");
  try_with(L' ', "en_US.UTF8");
  std::cout << std::endl;
}
