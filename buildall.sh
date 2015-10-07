#!/bin/sh

platform='unknown'
unamestr=$(uname)

cd exe
maya fullclean debug release debug64 release64

cd ../dll.svr1
maya fullclean debug
cd ../dll.svr2
maya fullclean debug
cd ../exe
if [[ $unamestr == "Linux" ]]; then
bin/lin_debug_32/exportingexe
else
bin/mac_debug_32/exportingexe
fi

cd ../dll.svr1
maya fullclean release
cd ../dll.svr2
maya fullclean release
cd ../exe
if [[ $unamestr == "Linux" ]]; then
bin/lin_release_32/exportingexe
else
bin/mac_release_32/exportingexe
fi

cd ../dll.svr1
maya fullclean debug64
cd ../dll.svr2
maya fullclean debug64
cd ../exe
if [[ $unamestr == "Linux" ]]; then
bin/lin_debug_64/exportingexe
else
bin/mac_debug_64/exportingexe
fi

cd ../dll.svr1
maya fullclean release64
cd ../dll.svr2
maya fullclean release64
cd ../exe
if [[ $unamestr == "Linux" ]]; then
bin/lin_release_64/exportingexe
else
bin/mac_release_64/exportingexe
fi


