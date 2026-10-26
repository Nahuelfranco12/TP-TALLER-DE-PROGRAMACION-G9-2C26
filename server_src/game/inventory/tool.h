#ifndef TOOL_H_
#define TOOL_H_

enum class AvailableTools { SWORD, PICKAXE, SHOVEL, WATERING_CAN };

class Tool {
public:
    AvailableTools toolType;

    explicit Tool(AvailableTools toolType) : toolType(toolType) {}
    virtual ~Tool() = default;
};

#endif // TOOL_H_
