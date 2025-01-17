#ifndef SIMPLE_MATRIX_H
#define SIMPLE_MATRIX_H

#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include <QString>

// TODO forward declare json
namespace impl {
struct CharPair {
    QChar row_char;
    QChar col_char;
    double probability{};
    size_t correct{};
    size_t wrong{};
    long typing_time{};     // typing time for this char
    double frequency = 1.0; // freq is from 0 - 1
};

void to_json(nlohmann::json &, const CharPair &);
void from_json(const nlohmann::json &, CharPair &);

} // namespace impl

class ProbabilityMatrix {
    // TODO use set for characters to get uniqueness
    QString characters;
    // TODO turn data into unique_ptr in order to be able to forward declare
    // CharPair and hide it inside the implementation file. This will require
    // the "rule-of-five" in order to work.
    std::vector<std::vector<impl::CharPair>> data;
    std::map<QChar, int> char_map;
    std::vector<int> typing_time; // history of full sentence typing times
    long average_typing_time{};

    friend void to_json(nlohmann::json &, const ProbabilityMatrix &);
    friend void from_json(const nlohmann::json &, ProbabilityMatrix &);

public:
    ProbabilityMatrix();
    ProbabilityMatrix(QString const);
    ProbabilityMatrix(std::map<QChar, double>);

    void update_time(int);
    QString get_characters();
    std::string to_string();
    void update_element(char const, char const, long const, bool const);
    QString generate_sentence(int);
    double proficiency();
    std::size_t size();
    long get_avg();
};

void to_json(nlohmann::json &, const ProbabilityMatrix &);
void from_json(const nlohmann::json &, ProbabilityMatrix &);

#endif /* SIMPLE_MATRIX_H */
