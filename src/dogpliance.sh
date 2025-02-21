find ./kenr -iname *.h | xargs ./cpplint.py --clint
find ./kenr -iname *.c | xargs ./cpplint.py --clint
find ./arch -iname *.h | xargs ./cpplint.py --clint
find ./arch -iname *.c | xargs ./cpplint.py --clint
find ./libdogs -iname *.h | xargs ./cpplint.py --clint
find ./libdogs -iname *.c | xargs ./cpplint.py --clint
find ../inc -iname *.h | xargs ./cpplint.py --clint
find ./drivers -iname *.c | xargs ./cpplint.py --clint
