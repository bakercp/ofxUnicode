#! /bin/bash
#
# ucdn
# Unicode Database and Normalization
# https://github.com/grigorig/ucdn
#
# notes on build system, reference links, etc

# array of build types supported by this formula
# you can delete this to implicitly support *all* types

#FORMULA_TYPES=( "osx" "msys2" "vs" )


VER=72df0a11789f5e61f3a5985a7575773e68906fe0


# download the source code and unpack it into LIB_NAME
function download() {
	git clone https://github.com/grigorig/ucdn.git
	cd ucdn/
	git checkout ${VER} 
}


# prepare the build environment, executed inside the lib src dir
function prepare() {
	:
}


# executed inside the lib src dir
function build() {
	echo "Nothing to build."
}

# executed inside the lib src dir, first arg $1 is the dest libs dir root
function copy() {
	mkdir -p $1/src
	cp -v ucdn.c $1/src/
	cp -v ucdn.h $1/src/
	cp -v ucdn_db.h $1/src/

	# copy license file
	rm -rf $1/license # remove any older files if exists
	mkdir -p $1/license
	cp -v README $1/license/

}

# executed inside the lib src dir
function clean() {
	echo "Nothing to clean."
}
