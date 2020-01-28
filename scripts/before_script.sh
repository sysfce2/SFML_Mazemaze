#!/bin/bash

set -xe

export VERSION=0.2

if [[ $WINDOWS = "TRUE" ]]
then
    sudo echo "deb http://pkg.mxe.cc/repos/apt bionic main" \
        | sudo tee /etc/apt/sources.list.d/mxeapt.list

    sudo apt-key adv --keyserver keyserver.ubuntu.com \
        --recv-keys C6BF758A33A3A276

    export MXE_TARGET=x86_64-w64-mingw32.static
    export MXE2_TARGET=$(echo "$MXE_TARGET" | sed 's/_/-/g')
    export MXE_DIR=/usr/lib/mxe
    export CMAKE="${MXE_DIR}/usr/bin/${MXE_TARGET}-cmake \
        -DMXE_USE_CCACHE=FALSE"

    sudo apt-get --yes update
    sudo apt-get --yes \
        --no-install-suggests \
        --no-install-recommends \
        install \
        mxe-$MXE2_TARGET-sfml \
        mxe-$MXE2_TARGET-jsoncpp
    sudo apt-get --yes remove mxe-$MXE2_TARGET-sfml

    # Hack to fix linking error
    sudo ln -s ${MXE_DIR}/usr/$MXE_TARGET/lib/libopengl32.a \
               ${MXE_DIR}/usr/$MXE_TARGET/lib/libOpenGL32.a

    # SFML

    wget https://www.sfml-dev.org/files/SFML-2.5.1-sources.zip
    unzip SFML-2.5.1-sources.zip
    cd SFML-2.5.1
    mkdir build
    cd build
    $CMAKE \
        -DSFML_USE_STATIC_STD_LIBS=TRUE \
        -BUILD_SHARED_LIBS=FALSE \
        -DSFML_BUILD_EXAMPLES=FALSE \
        -DSFML_BUILD_DOC=FALSE \
        -DSFML_BUILD_AUDIO=FALSE \
        -DSFML_BUILD_GRAPHICS=TRUE \
        -DSFML_BUILD_WINDOW=TRUE \
        -DSFML_BUILD_NETWORK=FALSE \
        ..
    $CMAKE --build .
    sudo make install
    cd ../..
else
    export CMAKE=cmake

    sudo echo "deb http://us.archive.ubuntu.com/ubuntu/ disco universe" >> \
        /etc/apt/sources.list

    sudo apt-get --yes update
    sudo apt-get --yes install libsfml-dev
fi

# SFGUI

git clone https://github.com/TankOs/SFGUI.git
cd SFGUI
sed '138{s/^/#/}' CMakeLists.txt > tmp    # hack to disable SFGUI warnings
mv tmp CMakeLists.txt                     #
mkdir build
cd build
CMAKE_SFGUI_FLAGS="-DSFGUI_BUILD_EXAMPLES=FALSE"
if [[ $WINDOWS = "TRUE" ]]
then
    CMAKE_SFGUI_FLAGS="$CMAKE_SFGUI_FLAGS  \
        -DSFGUI_BUILD_SHARED_LIBS=FALSE  \
        -DSFGUI_STATIC_STD_LIBS=TRUE  \
        -DSFML_STATIC_LIBRARIES=TRUE  \
        -DSFGUI_BUILD_EXAMPLES=FALSE"
fi
$CMAKE $CMAKE_SFGUI_FLAGS ..
$CMAKE --build .
sudo make install
cd ../..

set +xe
