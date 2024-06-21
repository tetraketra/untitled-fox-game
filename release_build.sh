gcc-12 $(find . -print | grep -i "\.c" | tr -s '\n' ' ') -o ./bin/manafield \
    -lGL -lglfw -lm -O3 -iquote ./src/modules

chmod a+x ./bin/manafield