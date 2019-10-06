#include "scores-graphics.hpp"
#include "color.hpp"
#include "scores.hpp"
#include <iomanip>
#include <sstream>
#include <vector>

namespace Scoreboard {
namespace Graphics {

std::string ScoreboardOverlay() {
  constexpr auto no_save_text = "No saved scores.";
  const auto score_attributes_text = {
      "No.", "Name", "Score", "Won?", "Moves", "Largest Tile", "Duration"};
  //  constexpr auto num_of_score_attributes_text = 7;
  constexpr auto header_border_text =
      "┌─────┬────────────────────┬──────────┬──────┬───────┬──────────────┬──────────────┐";
  constexpr auto mid_border_text =
      "├─────┼────────────────────┼──────────┼──────┼───────┼──────────────┼──────────────┤";
  constexpr auto bottom_border_text =
      "└─────┴────────────────────┴──────────┴──────┴───────┴──────────────┴──────────────┘";
  constexpr auto score_title_text = "SCOREBOARD";
  constexpr auto divider_text = "──────────";
  constexpr auto sp = "  ";

  std::ostringstream str_os;

  std::vector<Score> scoreList{};
  // bool loaded_scorelist;
  // Warning: Does not care if file exists or not!
  std::tie(std::ignore, scoreList) = loadFromFileScore("../data/scores.txt");

  str_os << green << bold_on << sp << score_title_text << bold_off << def
         << "\n";
  str_os << green << bold_on << sp << divider_text << bold_off << def << "\n";

  const auto number_of_scores = scoreList.size();
  if (number_of_scores) {
    str_os << sp << header_border_text << "\n";
    str_os << std::left;
    str_os << sp << "│ " << bold_on << std::begin(score_attributes_text)[0]
           << bold_off << " │ " << bold_on << std::setw(18)
           << std::begin(score_attributes_text)[1] << bold_off << " │ "
           << bold_on << std::setw(8) << std::begin(score_attributes_text)[2]
           << bold_off << " │ " << bold_on
           << std::begin(score_attributes_text)[3] << bold_off << " │ "
           << bold_on << std::begin(score_attributes_text)[4] << bold_off
           << " │ " << bold_on << std::begin(score_attributes_text)[5]
           << bold_off << " │ " << bold_on << std::setw(12)
           << std::begin(score_attributes_text)[6] << bold_off << " │"
           << "\n";
    str_os << std::right;
    str_os << sp << mid_border_text << "\n";

    auto counter{1};
    const auto print_score_stat = [&counter, &str_os](const Score i) {
      constexpr auto number_of_fields = 7;
      auto data_stats = std::array<std::string, number_of_fields>{};
      data_stats = {std::to_string(counter),     i.name,
                    std::to_string(i.score),     i.win ? "Yes" : "No",
                    std::to_string(i.moveCount), std::to_string(i.largestTile),
                    secondsFormat(i.duration)};
      str_os << sp << "│ " << std::setw(2) << data_stats[0] << ". │ "
             << std::left << std::setw(18) << data_stats[1] << std::right
             << " │ " << std::setw(8) << data_stats[2] << " │ " << std::setw(4)
             << data_stats[3] << " │ " << std::setw(5) << data_stats[4] << " │ "
             << std::setw(12) << data_stats[5] << " │ " << std::setw(12)
             << data_stats[6] << " │"
             << "\n";
      counter++;
    };

    for (const auto s : scoreList) {
      print_score_stat(s);
    }
    str_os << sp << bottom_border_text << "\n";
  } else {
    str_os << sp << no_save_text << "\n";
  }
  str_os << "\n\n";
  return str_os.str();
}

} // namespace Graphics

} // namespace Scoreboard
