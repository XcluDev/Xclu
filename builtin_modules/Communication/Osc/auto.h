//----------------------------------------------------
//Interface for XClassOsc
//Created automatically at 2020.09.14 11:01:46
//----------------------------------------------------
//Page Main
//General settings

//String Send Address
//Address with port: localhost:12345
bool was_changed_addr() { return was_changed("addr"); }
QString gets_addr() { return gets("addr"); }
QStringList get_strings_addr() { return get_strings("addr"); }

//----------------------------------------------------
