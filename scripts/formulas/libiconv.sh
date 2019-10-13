#! /bin/bash
#
# libiconv
#
# https://www.gnu.org/software/libiconv
#
# notes on build system, reference links, etc

FORMULA_TYPES=( "osx" "linux" "linux64")

VER=1.16

# download the source code and unpack it into LIB_NAME
function download() {
	curl -LO https://ftp.gnu.org/pub/gnu/libiconv/libiconv-${VER}.tar.gz
	tar -xf libiconv-${VER}.tar.gz
	mv libiconv-${VER} libiconv
	rm libiconv-${VER}.tar.gz
}


# prepare the build environment, executed inside the lib src dir
function prepare() {
	# generate the configure script if it's not there
	if [ ! -f configure ] ; then
		./bootstrap
	fi
}


# executed inside the lib src dir
function build() {

	_LDFLAGS=
	_CFLAGS=

	if [ "$TYPE" == "osx" ] ; then
		# set flags for osx 32 & 64 bit fat lib
		_LDFLAGS="-arch i386 -stdlib=libstdc++ -arch x86_64 -Xarch_x86_64 -stdlib=libc++"
		_CFLAGS="-Os -arch i386 -stdlib=libstdc++ -arch x86_64 -Xarch_x86_64 -stdlib=libc++"
	fi
# We enable-extra-encodings to get better european and other language support.
	./configure LDFLAGS="${_LDFLAGS}" \
							CFLAGS="${_CFLAGS}" \
							--prefix="${BUILD_ROOT_DIR}" \
							--disable-shared \
							--enable-extra-encodings

	make -j${PARALLEL_MAKE}
	make install

}

# executed inside the lib src dir, first arg $1 is the dest libs dir root
function copy() {
	mkdir -p $1/include/
	cp -v $BUILD_ROOT_DIR/include/iconv.h $1/include/
	cp -v $BUILD_ROOT_DIR/include/libcharset.h $1/include/

	mkdir -p $1/lib/$TYPE/
	cp -R $BUILD_ROOT_DIR/lib/libiconv.a $1/lib/$TYPE/
	cp -R $BUILD_ROOT_DIR/lib/libcharset.a $1/lib/$TYPE/

	# copy license file
	rm -rf $1/license # remove any older files if exists
	mkdir -p $1/license
	# yes, they spelled it licence
	cp -v COPYING $1/license/
}

# executed inside the lib src dir
function clean() {
	make clean
}
