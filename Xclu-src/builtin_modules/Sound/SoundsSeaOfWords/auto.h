//----------------------------------------------------
//Interface for XClassSoundsSeaOfWords
//Created automatically.
//----------------------------------------------------
//Page Inputs
//Conecting pedal and other controls.

//Checkbox Pedal State
//Use Arduino-based or MIDI pedal.
bool was_changed_pedal_state() { return was_changed_("pedal_state"); }
int geti_pedal_state() { return geti_("pedal_state"); }
void repaint_pedal_state() { repaint_("pedal_state"); }

//----------------------------------------------------
//Page DSP
//Sound processing

//Float Volume
//Volume.
bool was_changed_output_volume() { return was_changed_("output_volume"); }
float getf_output_volume() { return getf_("output_volume"); }
void repaint_output_volume() { repaint_("output_volume"); }

//----------------------------------------------------
