//----------------------------------------------------
//Interface for XClassDelay
//Created automatically.
//----------------------------------------------------
//Page Main
//

//Int Hours
//Delay time in hours
bool was_changed_hours() { return was_changed_("hours"); }
int geti_hours() { return geti_("hours"); }

//Int Minutes
//Delay time in minutes
bool was_changed_minutes() { return was_changed_("minutes"); }
int geti_minutes() { return geti_("minutes"); }

//Float Seconds
//Delay time in seconds
bool was_changed_seconds() { return was_changed_("seconds"); }
float getf_seconds() { return getf_("seconds"); }

//----------------------------------------------------
