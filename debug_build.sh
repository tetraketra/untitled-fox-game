#!/bin/bash

sudo sysctl vm.mmap_rnd_bits=28 > /dev/null 2>&1
sudo sysctl vm.mmap_rnd_compat_bits=8 > /dev/null 2>&1

FILES=$(find . -print | grep -i "\.c" | tr -s '\n' ' ')
WARNS="-W -Wall -Wextra -Wuninitialized -Wno-multichar -Wno-comment -Wno-misleading-indentation"
FSANS="-fsanitize=address -fsanitize=undefined -fsanitize-address-use-after-scope"
CGENS=""
LINKS="-lGL -lglfw -lm"
DEBUG="-Og -g3 -D _DEBUG"
INCLD="-iquote ./src/modules"

echo "\n\nExecuting with..."
echo "FILES: $FILES"
echo "WARNS: $WARNS"
echo "FSANS: $FSAN"
echo "CGENS: $CGEN"
echo "LINKS: $LINKS"
echo "DEBUG: $DEBUG"
echo "INCLD: $INCLD"

echo "\n\nReporting lines..."
if command -v scc &> /dev/null; then
    scc \
        --not-match="(.gitignore|.gitattributes|dummy.txt|LICENSE|ext/*|ext)" \
        --no-large --large-line-count 3000
else
    find ./ -type f \( -iname \*.c -o -iname \*.h \) \
        | xargs wc -l \
        | sort -nr
fi

echo "\nReporting build times..."
gcc-12 $FILES -o ./bin/manafield \
    $WARNS $LINKS $DEBUG $FSANS $CGENS $INCLD \
    -ftime-report \
    > time.txt 2>&1
cat time.txt \
    | grep -E --color=never '^(Time variable| [[:alnum:]])' \
    | cut -c1-36,69-79 \
    | sed 's/   wall/ /' \
    | awk -v list="$FILES" 'BEGIN { file_index=1 }
        {
            if (gsub("Time variable", (file_index <= split(list, arr) ? arr[file_index] : "File"))) {
                file_index = (file_index < length(arr) ? file_index + 1 : 1)
            }
            print 
        }'

echo "\n\nReporting build warnings and errors..."
cat time.txt \
    | grep -v -E '^(Time variable| [[:alnum:]])' \
    | grep -v '^$'

rm time.txt

find ./bin -type f -print -quit | xargs chmod a+x

echo "\n\nExecute \"sh debug_run.sh\" to start the program."