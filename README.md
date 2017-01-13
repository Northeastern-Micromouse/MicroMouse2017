# Master
Northeastern University Micromouse 2017

Installing Homebrew:

1. If you are a mac user type 

/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"


into your terminal.


We are using Bazel to build all of our code. The docs can be found at https://bazel.io/
It is an open source tool created by Google used to build code. 

Installation instructions for Mac:

1. If you have homebrew installed just type brew install bazel into your terminal.
2. If you encounter problems, make sure homebrew is updated. Do this by running brew update twice.
3. If you still have problems run brew doctor. 

Installation instructions for PC: https://bazel.io/versions/master/docs/windows.html

1. Get a mac

Currently it is only supported for 64 bit Windows 7 or higher and we compile Bazel as a msys2 binary.

You will also need: 

1. Java JDK 8 or later
2. Visual Studio (Community Edition is okay)
3. msys2 (need to be installed at C:\tools\msys64\).
4. Several msys2 packages. Use the pacman command to install them: pacman -Syuu gcc git curl zip unzip zlib-devel


To get Git Autocomplete:
	
1. http://code-worrier.com/blog/autocomplete-git/


Visual GDB Licenses:
    NEU Micromouse - [name].



