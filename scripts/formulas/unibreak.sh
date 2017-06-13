#! /bin/bash
#
# libunibreak
# Breaks lines and words according to the unicode standard.
# https://github.com/adah1972/libunibreak
#
# notes on build system, reference links, etc

# array of build types supported by this formula
# you can delete this to implicitly support *all* types

FORMULA_TYPES=( "osx", "msys2", "vs" )

VER=4_0

GIT_URL=https://github.com/adah1972/libunibreak.git
GIT_TAG=libunibreak_$VER

# download the source code and unpack it into LIB_NAME
function download() {
	curl -LO https://github.com/adah1972/libunibreak/archive/libunibreak_$VER.tar.gz
	tar -xf libunibreak_$VER.tar.gz
	mv libunibreak-libunibreak_$VER unibreak
	rm libunibreak_$VER.tar.gz
}

# prepare the build environment, executed inside the lib src dir
function prepare() {
	# initialize the repository
	if [ "$TYPE" == "osx" ] ; then
		# generate the configure script if it's not there
		if [ ! -f configure ] ; then
			./autogen.sh
		fi
  fi

}


# executed inside the lib src dir
function build() {

	if [ "$TYPE" == "osx" ] ; then
		# set flags for osx 32 & 64 bit fat lib
		./configure LDFLAGS="-arch i386 -stdlib=libstdc++ -arch x86_64 -Xarch_x86_64 -stdlib=libc++" \
					CFLAGS="-Os -arch i386 -stdlib=libstdc++ -arch x86_64 -Xarch_x86_64 -stdlib=libc++" \
					--prefix=$BUILD_ROOT_DIR \
					--disable-shared

		make -j${PARALLEL_MAKE}
		make install
	elif [ "$TYPE" == "msys2" ]; then
		cd src/
		make -f Makefile.gcc release -j${PARALLEL_MAKE}
	elif [ "$TYPE" == "vs" ]; then
		cd src/
		# Just need to call this. But, it doesn't work ...
		# CMD //c /c/Program\ Files\ \(x86\)/Microsoft\ Visual\ Studio\ 14.0/VC/bin/nmake.exe -f Makefile.msvc
		# or Calling nmake -f Makefile.msvc CFG="libunibreak - Win32 Release"

	fi

}

# executed inside the lib src dir, first arg $1 is the dest libs dir root
function copy() {
	if [ "$TYPE" == "osx" ] ; then
		INSTALLED_INCLUDE_DIR=$BUILD_ROOT_DIR/include
		INSTALLED_LIB_DIR=$BUILD_ROOT_DIR/lib/libunibreak.a
	elif [ "$TYPE" == "msys2" ] ; then
		INSTALLED_INCLUDE_DIR=src
		INSTALLED_LIB=src/ReleaseDir/libunibreak.a
	elif [ "$TYPE" == "vs" ] ; then
		INSTALLED_INCLUDE_DIR=src
		INSTALLED_LIB=src/Release/unibreak.lib
	fi

	mkdir -p $1/include/
	cp -v $INSTALLED_INCLUDE_DIR/graphemebreak.h $1/include/
	cp -v $INSTALLED_INCLUDE_DIR/linebreak.h $1/include/
	cp -v $INSTALLED_INCLUDE_DIR/linebreakdef.h $1/include/
	cp -v $INSTALLED_INCLUDE_DIR/unibreakbase.h $1/include/
	cp -v $INSTALLED_INCLUDE_DIR/unibreakdef.h $1/include/
	cp -v $INSTALLED_INCLUDE_DIR/wordbreak.h $1/include/

	mkdir -p $1/lib/$TYPE/
	cp -v $INSTALLED_LIB $1/lib/$TYPE/

	# copy license file
	rm -rf $1/license # remove any older files if exists
	mkdir -p $1/license
	# yes, they spelled it licence
	cp -v LICENCE $1/license/
}

# executed inside the lib src dir
function clean() {
	if [ "$TYPE" == "osx" ] ; then
		make clean
	elif [ "$TYPE" == "msys2" ]; then
		cd src/
		make clean
	fi
}
