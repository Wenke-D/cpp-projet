RM = rm -rf
EXE =
OPT = -O2
#
#	Compilation on Windows for Windows
#
ifeq '$(OS)' "Windows_NT"
FLTK_VERSION = lib/fltk-1.4-windows
EXE = .exe
LD = ld
RM = del
CXX = g++
CXXFLAGS =		-Wall $(OPT)

CONSOLE =		-Wl,--subsystem,console
LINKFLTK_IMG =	$(CONSOLE) -mwindows -L$(FLTK_VERSION) \
				-lfltk_images -lfltk_png -lfltk_z -lfltk_jpeg -lfltk_gl -lfltk \
				-lwinmm -lglu32 -lopengl32 -lole32 -luuid \
				-lcomctl32 -lws2_32 -lwinpthread -static

else
#
#	Compilation on MacOSX for MacOSX
#
ifeq '$(shell uname -s)' "Darwin"
FLTK_VERSION = lib/fltk-1.4-macosx
OS = Darwin
FMOD = lib/fmod/Developer/FMOD\ Programmers\ API\ Mac/api
CXX = g++
LD = ld
CXXFLAGS =		-Wall -Wno-invalid-source-encoding -Wno-deprecated-declarations \
				-I /usr/include/freetype2 -I /usr/X11/include -I $(FMOD)/inc $(OPT)

LINKFLTK_IMG =	-L$(FLTK_VERSION) -lfltk_png -lfltk_z -lfltk_jpeg -lfltk_gl \
				-lfltk -framework Cocoa -framework AGL -framework OpenGL \
				-framework ApplicationServices $(FMOD)/lib/libfmodex.dylib
else
#
#	Compilation on Linux for Linux
#
FLTK_VERSION = lib/fltk-1.4-linux
FMOD = lib/fmod/4.3
CXX = g++
LD = ld
CXXFLAGS =		-Wall -I $(FMOD) -I /usr/include/freetype2 -I /usr/X11/include $(OPT)

LINKFLTK_IMG =	$(FMOD)/libfmodex64.so -L$(FLTK_VERSION) -lfltk_jpeg \
				-lfltk_png -lfltk_z -lfltk_gl -lfltk -lGLU -lGL \
				-lXext -lXft -lXrender -lfontconfig -ldl -lm -lX11 -lXfixes
endif
endif

#
#	Début du Makefile propre au projet
#

TARGET	:= labh$(EXE)

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
LIB_DIR = lib

SRC_EXT = cc

# ======================== Need Manual Update =======================
FIXED_HEADERS = Environnement.h Mover.h FireBall.h Sound.h

OBJS = Chasseur Labyrinthe config MapData Location Decoration Picture

SINGLE_HEADERS = Gardien.h

# source filenames
SOURCES = $(addsuffix .cc,$(OBJS))
# header filenames
HEADERS = $(FIXED_HEADERS) $(addsuffix .h,$(OBJS)) $(SINGLE_HEADERS)
# ===================================================================

# all source filenames with path and extension
SRC = 	$(addprefix $(SRC_DIR)/,$(SOURCES))
# all header filenames with path and extension
H	=   $(addprefix $(INC_DIR)/,$(HEADERS))
# all objective filenames with path and extension
O	=	$(addsuffix .o,$(addprefix $(BUILD_DIR)/,$(basename $(SOURCES))))

INC = -I $(INC_DIR)

ifeq '$(OS)' "Darwin"
OPENGL_O = $(LIB_DIR)/OpenGL-macosx.o
else
	ifeq '$(OS)' "Windows_NT"
	OPENGL_O = $(LIB_DIR)/OpenGL-windows.o
	else
	OPENGL_O = $(LIB_DIR)/OpenGL-linux.o
	endif
endif

$(TARGET): $(O)
	@echo "$(O)"
	$(CXX) -no-pie -o $@ $^ $(OPENGL_O) $(LINKFLTK_IMG)
ifeq '$(OS)' "Darwin"
	install_name_tool -change ./libfmodex.dylib fmod/Developer/FMOD\ Programmers\ API\ Mac/api/lib/libfmodex.dylib $@
endif


# Labyrinthe.o: Labyrinthe.h Environnement.h Chasseur.h Mover.h Gardien.h
# 	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

# Chasseur.o:	Chasseur.cc Chasseur.h Mover.h
# 	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

# Default rule for .o file with corresponding .h file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT) $(INC_DIR)/%.h $(H)
	@echo Making $@
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

# Default rule for individual .o file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT) $(H)
	@echo Making $@
	$(CXX) $(CXXFLAGS)  -c $< -o $@ 

ifeq '$(OS)' "Windows_NT"
clean_targets =  $(subst /,\,$(TARGET) $(O))
else
clean_targets =  $(TARGET) $(O)
endif
clean:
	$(RM) $(clean_targets)

run: $(TARGET)
	$< .\res\map\labyrinthe.txt


.PHONY: clean test