Module implementation can deal with buttons in two ways:
1. Implement `virtual void impl_button_pressed(QString button_id);` - this way allows to process button presses even if project is not running. The names of buttons are in auto.h, such as `button_...()`. It's crucial for such tasks as printing connected devices to set the device ID in settings of module. Also, it's crucial for situations when it's important to process button immediately, for example, as camera callback. For simpler cases - use second approach.
2. Check `geti_button....()` function corresponding the button (from `auto.h`) inside impl_update(). This value resets each update.

Please, note, if you will implement a button processing twice (by both ways) - it can be processed twice, so we recommend to avoid this.