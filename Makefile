# this flag selects the rack version to compile against.
# 
# possible values are v040 and v_dev

# FLAGS += -D v040
FLAGS += -D v_dev

SOURCES = $(wildcard src/*.cpp)

include ../../plugin.mk


dist: all
	mkdir -p dist/Autodafe
	cp LICENSE* dist/Autodafe/
	cp plugin.* dist/Autodafe/
	cp -R res dist/Autodafe/
