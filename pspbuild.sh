
## Check if $PSPDEV is set.
if test ! $PSPDEV; then { echo "ERROR: Set \$PSPDEV installing pspdev toolchain and pspsdk before continuing."; exit 1; } fi

git clone https://github.com/raylib4Consoles/raylib -b raylib4Consoles
cd raylib/src
make PLATFORM=PLATFORM_PSP
make PLATFORM=PLATFORM_PSP install
