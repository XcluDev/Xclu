@rem This program reads string and writes it back in a loop
@rem @echo Runs... > 0.txt
@:loop
@set /p stuff=
@echo resulted %stuff%
@rem @echo Save: %stuff% > 1.txt
@goto loop