//----------------------------------------------------
//Interface for XClassTelegramBot
//Created automatically.
//----------------------------------------------------
//Page Main
//

//Checkbox Show Token
//Disable this to hide token.
bool was_changed_show_token() { return was_changed_("show_token"); }
int geti_show_token() { return geti_("show_token"); }

//String Bot Token
//Place bot token here.
bool was_changed_bot_token() { return was_changed_("bot_token"); }
QString gets_bot_token() { return gets_("bot_token"); }
QStringList get_strings_bot_token() { return get_strings_("bot_token"); }

//String Chat Id
//Chat id.
bool was_changed_chat_id() { return was_changed_("chat_id"); }
QString gets_chat_id() { return gets_("chat_id"); }
QStringList get_strings_chat_id() { return get_strings_("chat_id"); }


//String Message
//Message to send.
bool was_changed_message_send() { return was_changed_("message_send"); }
QString gets_message_send() { return gets_("message_send"); }
QStringList get_strings_message_send() { return get_strings_("message_send"); }

//Button Send
//Press to send.
bool was_changed_button_send() { return was_changed_("button_send"); }
int geti_button_send() { return geti_("button_send"); }
QString button_button_send() { return "button_send"; }

//----------------------------------------------------
