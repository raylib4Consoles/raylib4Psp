
## Check if $PSPDEV is set.
if test ! $PSPDEV; then { echo "ERROR: Set \$PSPDEV installing pspdev toolchain and pspsdk before continuing."; exit 1; } fi

# git clone https://github.com/raylib4Consoles/raylib -b raylib4Consoles
git clone https://github.com/mcidclan/raylib4Consoles -b raylib4Consoles raylib # tmp
cd raylib/src
make PLATFORM=PLATFORM_PSP_SDL clean
make PLATFORM=PLATFORM_PSP_SDL
make PLATFORM=PLATFORM_PSP_SDL install

