#pragma once
#include <ostream>
#include <streambuf>
#include <string>

namespace c2py {

  // =============================================================================

  /**
   * @class indented_ostream
   * @brief A custom output stream that automatically indents each new line by a specified number of spaces.
   * 
   * This class is useful for formatting output with consistent indentation. It wraps around an existing 
   * `std::ostream` and ensures that every new line starts with a specified number of spaces.
   * 
   * Example usage:
   * @code
   *   auto out = indented_ostream{std::cout, 3}; // Indent all lines with 3 spaces
   *   out << "Hello, world!" << std::endl;
   *   out << "Indented text." << std::endl;
   * @endcode
   * 
   * @note This class inherits from `std::ostream` and uses a custom stream buffer to handle indentation.
   */
  class indented_ostream : public std::ostream {

    class indented_streambuf : public std::streambuf {
      std::streambuf *dest;
      std::string head;
      bool at_line_start = true;

      public:
      indented_streambuf(std::streambuf *dest, int indent) : dest(dest), head(indent, ' ') {}

      protected:
      int_type overflow(int_type c) override {
        if (c == EOF) return !EOF;
        if (at_line_start && c != '\n') dest->sputn(head.c_str(), long(head.size()));
        at_line_start = (c == '\n');
        return dest->sputc(c); //NOLINT
      }
      int sync() override { return dest->pubsync(); }
    };
    indented_streambuf buffer;

    public:
    /**
     * @brief Constructor
     * 
     * @param os The underlying std::ostream to write into.
     * @param indent The number of spaces to use for indentation.
     */
    indented_ostream(std::ostream &os, int indent) : std::ostream(&buffer), buffer(os.rdbuf(), indent) {}
  };

} 
