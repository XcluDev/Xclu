//----------------------------------------------------
//Interface for XClassDelay
//Created automatically at 2020.09.14 11:01:46
//----------------------------------------------------
//Page Main
//

//Int Hours
//Delay time in hours
bool was_changed_hours() { return was_changed("hours"); }
int geti_hours() { return geti("hours"); }

//Int Minutes
//Delay time in minutes
bool was_changed_minutes() { return was_changed("minutes"); }
int geti_minutes() { return geti("minutes"); }

//Float Seconds
//Delay time in seconds
bool was_changed_seconds() { return was_changed("seconds"); }
float getf_seconds() { return getf("seconds"); }

//----------------------------------------------------
