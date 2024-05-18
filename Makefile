SOURCE_FILES=$(wildcard *.cpp *.hpp)

all:
	$(CXX) -shared -fPIC --no-gnu-unique $(SOURCE_FILES)  -o hykeys.so -g `pkg-config --cflags pixman-1 libdrm hyprland` -std=c++2b -DWLR_USE_UNSTABLE
