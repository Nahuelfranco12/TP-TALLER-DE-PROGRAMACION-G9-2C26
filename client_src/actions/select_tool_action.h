#ifndef SELECT_TOOL_ACTION_H_
#define SELECT_TOOL_ACTION_H_

#include "../../common_src/game_dtos.h"
#include "client_action.h"

class SelectToolAction: public ClientAction {
private:
    ToolTypeDto tool;

public:
    explicit SelectToolAction(ToolTypeDto tool): tool(tool) {}

    void send_by(ClientProtocol& protocol) const override {
        protocol.send_select_tool(tool);
    }
};

#endif