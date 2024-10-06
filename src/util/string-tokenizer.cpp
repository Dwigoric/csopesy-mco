//
// Created by Dwigoric on 27 Sep 2024.
//

#include "string-tokenizer.h"

std::vector<std::string> tokenize(const std::string &str, const std::string &delimiters) {
    const std::regex regex(delimiters);
    const std::sregex_token_iterator it(str.begin(), str.end(), regex, -1);
    const std::sregex_token_iterator end;

    std::vector<std::string> tokens(it, end);

    return tokens;
}
