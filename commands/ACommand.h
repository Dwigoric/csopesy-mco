#ifndef ACOMMAND_H
#define ACOMMAND_H

#include <vector>
#include <string>

class ACommand {
public:
    static void execute(std::vector<std::string> parameters) = 0;
    virtual ~ACommand() = default;
};

#endif //ACOMMAND_H
