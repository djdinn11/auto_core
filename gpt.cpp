#include <gpt.hpp>

string gpt_5 = "Hi GPT-5, this is DJ. I am building a C++ project named Auto Core specialized for Windows 11 systems.";
string gpt_4_point_5 = "Hi GPT-4.5, this is DJ. I am developing a hypothetical military and cultural system.";
string gpt_default = "Hi GPT-4, this is DJ.";

string get_gpt_message() {
	ss prompt;
	prompt << "Enter the GPT model:\n"
		<< "1 for GPT-5\n"
		<< "2 for GPT-4.5\n"
		<< "> ";
	print(prompt.str());
	string selection_str;
	bool string_converted = false;
	while (!string_converted) {
		getline(cin, selection_str);
		if (selection_str.empty())
		{
			return gpt_default;
		}
		try {
			int green_line_check = stoi(selection_str);
			string_converted = true;
		}
		catch (const std::invalid_argument&) {
			print("Incorrect input\nEnter again: ");
		}
	}
	int selection = stoi(selection_str);
	if (selection == 1) {
		return gpt_5;
	}
	else if (selection == 2) {
		return gpt_4_point_5;
	}
	return gpt_default;
}
void print_gpt_message() {
	HWND currentWindowHandle = GetForegroundWindow();
	activate_Auto_Core();
	string gpt_message = get_gpt_message();
	print(gpt_message + "\n");
	wss ws;
	ws << gpt_message.c_str();
	set_clipboard_text(ws.str());
	SetForegroundWindow(currentWindowHandle);
	simulate_paste();
}