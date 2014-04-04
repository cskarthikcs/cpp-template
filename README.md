C++ template with potentially useful libraries pre-installed.

Quickstart Debian 7.2

    sudo apt-get update
    sudo apt-get install git
    git clone --recursive https://github.com/google-hash-code-paris-2014-tmo/cpp-template
    cd cpp-template
    ./configure
    make run

Header only implementation because this is a coding context, so writing faster is more important than compiling faster.

Based on: <https://github.com/cirosantilli/cpp-template>

All input data must be put under directory `in/`.
