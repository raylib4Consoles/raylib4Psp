# Install for Psp
- Install last pspdev/pspsdk follow steps from https://pspdev.github.io/
- clone this repository and execute if you are in Unix like environtment including wsl2:
```
./pspbuild.sh
```

# Samples
- in each sample use make to build
```
% cd samples
% ls
models  shapes
% cd models
% ls
cubicmap
% cd cubicmap
% ls
Makefile		cubicmap_atlas.png
cubicmap.png		main.c
% make
psp-gcc -I. -I/usr/local/pspdev/psp/include -I/usr/local/pspdev/psp/sdk/include -Wall -D_PSP_FW_VERSION=600   -c -o main.o main.c
psp-gcc -I. -I/usr/local/pspdev/psp/include -I/usr/local/pspdev/psp/sdk/include -Wall -D_PSP_FW_VERSION=600  -L. -L/usr/local/pspdev/psp/lib -L/usr/local/pspdev/psp/sdk/lib -specs=/usr/local/pspdev/psp/sdk/lib/prxspecs -Wl,-q,-T/usr/local/pspdev/psp/sdk/lib/linkfile.prx  -Wl,-zmax-page-size=128  main.o /usr/local/pspdev/psp/sdk/lib/prxexports.o -lraylib -lpng -lz  -lglut -lGLU -lGL -lpspvfpu  -lpspdebug -lpspdisplay -lpspge -lpspctrl -lpspnet -lpspnet_apctl -o raylib.elf
psp-fixup-imports raylib.elf
psp-prxgen raylib.elf raylib.prx
mksfoex -d MEMSIZE=1  'raylib cubicmap' PARAM.SFO
pack-pbp EBOOT.PBP PARAM.SFO NULL  \
		NULL NULL NULL  \
		NULL  raylib.prx NULL
[0]        320 bytes | PARAM.SFO
[1]          0 bytes | NULL
[2]          0 bytes | NULL
[3]          0 bytes | NULL
[4]          0 bytes | NULL
[5]          0 bytes | NULL
[6]    1251274 bytes | raylib.prx
[7]          0 bytes | NULL
```
- You can load generated prx with pspsh and psplink
```
host0:/models/cubicmap/> ./raylib.prx
Load/Start host0:/models/cubicmap/raylib.prx UID: 0x03FF9137 Name: cubicmap
host0:/models/cubicmap/> [PSP][INFO]Initializing raylib 5.5-dev
[PSP][INFO]Platform backend: PSP
[PSP][INFO]Supported raylib modules:
[PSP][INFO]    > rcore:..... loaded (mandatory)
[PSP][INFO]    > rlgl:...... loaded (mandatory)
[PSP][INFO]    > rshapes:... loaded (optional)
[PSP][INFO]    > rtextures:. loaded (optional)
[PSP][INFO]    > rtext:..... loaded (optional)
[PSP][INFO]    > rmodels:... loaded (optional)
[PSP][INFO]    > raudio:.... not loaded (optional)
[PSP][INFO]PLATFORM: eglChooseConfig success.
[PSP][INFO]PLATFORM: eglCreateWindowSurface success.
[PSP][INFO]PLATFORM: Device initialized successfully
[PSP][INFO]    > Display size: 480 x 272
[PSP][INFO]    > Screen size:  480 x 272
[PSP][INFO]    > Render size:  480 x 272
[PSP][INFO]    > Viewport offsets: 0, 0
[PSP][INFO]PLATFORM: GL_VENDOR:   "pspGL"
[PSP][INFO]PLATFORM: GL_VERSION:  "1.3 (pspGL build Oct 11 2024, 18:02:26)"
[PSP][INFO]PLATFORM: GL_RENDERER: "OpenGL ES-CM 1.1"
[PSP][INFO]PLATFORM: Initialized
[PSP][INFO]TEXTURE: [ID 1] Texture loaded successfully (128x128 | GRAY_ALPHA | 1 mipmaps)
[PSP][INFO]FONT: Default font loaded successfully (224 glyphs)
[PSP][INFO]SYSTEM: Working Directory: host0:/models/cubicmap
[PSP][INFO]FILEIO: [host0:/models/cubicmap/cubicmap.png] File loaded successfully
[PSP][INFO]IMAGE: Data loaded successfully (32x16 | R8G8B8 | 1 mipmaps)
[PSP][INFO]TEXTURE: [ID 2] Texture loaded successfully (32x16 | R8G8B8 | 1 mipmaps)
[PSP][INFO]FILEIO: [host0:/models/cubicmap/cubicmap_atlas.png] File loaded successfully
[PSP][INFO]IMAGE: Data loaded successfully (256x256 | R8G8B8A8 | 1 mipmaps)
[PSP][INFO]TEXTURE: [ID 3] Texture loaded successfully (256x256 | R8G8B8A8 | 1 mipmaps)
[PSP][INFO]TIMER: Target time per frame: 16.667 milliseconds
```


Enjoy!!!!

