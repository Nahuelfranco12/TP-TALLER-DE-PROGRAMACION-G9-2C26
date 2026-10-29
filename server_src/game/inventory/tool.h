#ifndef TOOL_H_
#define TOOL_H_

#include "../game_constants.h"

class Tool {
public:
    AvailableTools toolType;

    explicit Tool(AvailableTools toolType) : toolType(toolType) {}
    virtual ~Tool() = default;
};

#endif // TOOL_H_
