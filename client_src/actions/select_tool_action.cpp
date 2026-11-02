SelectToolAction::SelectToolAction(ToolTypeDto tool): tool(tool) {}

void SelectToolAction::send_by(ClientProtocol& protocol) const {
    protocol.send_select_tool(tool);
}