/**
DFS Sudoku solver CLI.

Input:
  argv[1]: 81-char board string. Use digits 1-9 for filled cells and '.' or '0' for empty.
  argv[2] (optional): max number of solutions to print (positive integer).

Output:
  Prints each full solution as a single 81-char line.
*/

#include <array>
#include <cstdint>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace {

struct SudokuState
{
    std::array<int, 81> cells{};
    std::array<uint16_t, 9> row_mask{};
    std::array<uint16_t, 9> col_mask{};
    std::array<uint16_t, 9> box_mask{};
};

constexpr uint16_t kAllDigitsMask = 0x03FE; // bits 1..9

int
box_index(int row, int col)
{
    return (row / 3) * 3 + (col / 3);
}

bool
place_digit(SudokuState& state, int index, int digit)
{
    const int row = index / 9;
    const int col = index % 9;
    const int box = box_index(row, col);
    const uint16_t bit = static_cast<uint16_t>(1u << digit);

    if ((state.row_mask[row] & bit) != 0 || (state.col_mask[col] & bit) != 0 || (state.box_mask[box] & bit) != 0) {
        return false;
    }

    state.cells[index] = digit;
    state.row_mask[row] |= bit;
    state.col_mask[col] |= bit;
    state.box_mask[box] |= bit;
    return true;
}

void
remove_digit(SudokuState& state, int index, int digit)
{
    const int row = index / 9;
    const int col = index % 9;
    const int box = box_index(row, col);
    const uint16_t bit = static_cast<uint16_t>(1u << digit);

    state.cells[index] = 0;
    state.row_mask[row] &= static_cast<uint16_t>(~bit);
    state.col_mask[col] &= static_cast<uint16_t>(~bit);
    state.box_mask[box] &= static_cast<uint16_t>(~bit);
}

uint16_t
candidate_mask(const SudokuState& state, int index)
{
    const int row = index / 9;
    const int col = index % 9;
    const int box = box_index(row, col);
    const uint16_t used = static_cast<uint16_t>(state.row_mask[row] | state.col_mask[col] | state.box_mask[box]);
    return static_cast<uint16_t>(kAllDigitsMask & static_cast<uint16_t>(~used));
}

int
popcount16(uint16_t x)
{
    int count = 0;
    while (x != 0) {
        x = static_cast<uint16_t>(x & static_cast<uint16_t>(x - 1));
        ++count;
    }
    return count;
}

std::optional<SudokuState>
parse_board(std::string_view input)
{
    if (input.size() != 81) {
        return std::nullopt;
    }

    SudokuState state{};
    for (size_t i = 0; i < input.size(); ++i) {
        const char c = input[i];
        if (c == '.' || c == '0') {
            state.cells[i] = 0;
            continue;
        }
        if (c < '1' || c > '9') {
            return std::nullopt;
        }

        const int digit = c - '0';
        if (!place_digit(state, static_cast<int>(i), digit)) {
            return std::nullopt;
        }
    }

    return state;
}

std::string
board_to_string(const SudokuState& state)
{
    std::string out;
    out.reserve(81);
    for (int value : state.cells) {
        out.push_back(static_cast<char>('0' + value));
    }
    return out;
}

bool
choose_next_cell(const SudokuState& state, int& out_index)
{
    int best_index = -1;
    int best_count = 10;

    for (int i = 0; i < 81; ++i) {
        if (state.cells[i] != 0) {
            continue;
        }

        const uint16_t mask = candidate_mask(state, i);
        const int count = popcount16(mask);

        if (count == 0) {
            out_index = -1;
            return true;
        }
        if (count < best_count) {
            best_count = count;
            best_index = i;
            if (best_count == 1) {
                break;
            }
        }
    }

    out_index = best_index;
    return false;
}

void
solve_dfs(SudokuState& state, std::vector<std::string>& solutions, size_t max_solutions)
{
    if (max_solutions != 0 && solutions.size() >= max_solutions) {
        return;
    }

    int index = -1;
    const bool dead_end = choose_next_cell(state, index);

    if (dead_end) {
        return;
    }

    if (index == -1) {
        solutions.push_back(board_to_string(state));
        return;
    }

    uint16_t mask = candidate_mask(state, index);
    while (mask != 0) {
        const uint16_t bit = static_cast<uint16_t>(mask & static_cast<uint16_t>(-static_cast<int16_t>(mask)));

        int digit = 1;
        while ((bit & static_cast<uint16_t>(1u << digit)) == 0) {
            ++digit;
        }

        if (place_digit(state, index, digit)) {
            solve_dfs(state, solutions, max_solutions);
            remove_digit(state, index, digit);

            if (max_solutions != 0 && solutions.size() >= max_solutions) {
                return;
            }
        }

        mask = static_cast<uint16_t>(mask & static_cast<uint16_t>(mask - 1));
    }
}

std::optional<size_t>
parse_positive_limit(const std::string& s)
{
    if (s.empty()) {
        return std::nullopt;
    }

    size_t value = 0;
    for (char c : s) {
        if (c < '0' || c > '9') {
            return std::nullopt;
        }
        value = value * 10 + static_cast<size_t>(c - '0');
    }

    if (value == 0) {
        return std::nullopt;
    }

    return value;
}

void
print_usage(const char* program)
{
    std::cerr << "Usage: " << program << " <81-char-board> [max_solutions]\n"
              << "Board chars: 1-9 for fixed cells, '.' or '0' for empty cells.\n";
}

} // namespace

int
main(int argc, char* argv[])
{
    if (argc < 2 || argc > 3) {
        print_usage(argv[0]);
        return 0;
    }

    size_t max_solutions = 0; // 0 means unlimited
    if (argc == 3) {
        const auto parsed_limit = parse_positive_limit(argv[2]);
        if (!parsed_limit.has_value()) {
            std::cerr << "Error: max_solutions must be a positive integer.\n";
            return 1;
        }
        max_solutions = *parsed_limit;
    }

    auto parsed_state = parse_board(argv[1]);
    if (!parsed_state.has_value()) {
        std::cerr << "Error: invalid board input. Expected 81 chars and no row/column/box conflicts.\n";
        return 1;
    }

    SudokuState state = *parsed_state;
    std::vector<std::string> solutions;
    solve_dfs(state, solutions, max_solutions);

    if (solutions.empty()) {
        std::cout << "No solutions found.\n";
        return 0;
    }

    std::cout << "Found " << solutions.size() << " solution(s).\n";
    for (const auto& solution : solutions) {
        std::cout << solution << "\n";
    }

    return 0;
}
