### glew ###
make -C lib/glew/auto/

### assimp ###
make lib/assimp/

make -j4 -C lib/glew/auto/

cmake .
make
