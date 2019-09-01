# SimpleGameOfMine

This README was created for release v0.1.0.

This is a simple RPG game made using Qt, with C++17.

This game was not tested using Windows or Mac OS, and probably will need some adaptations to work.

## Requirements

This game was tested using g++-7 and g++-8, it does not work for gcc-6 or below but may work with a higher version

This game also need Qt5, worked with Qt5.11

For Ubuntu 18.04 the installing Qt5-default should be enough

    sudo apt update
    sudo apt qt5-default

## Download with git

    git clone https://github.com/SamuelPossamai/SimpleGameOfMine.git
    git submodule update --init --recursive

## How to run without installing for linux

    qmake
    make run

## How to install for linux

    qmake
    sudo make install

## How to run after installing

    SGOM
