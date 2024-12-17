find ./kenr -iname *.h | xargs ./cpplint.py
find ./kenr -iname *.c | xargs ./cpplint.py 
find ./arch -iname *.h | xargs ./cpplint.py
find ./arch -iname *.c | xargs ./cpplint.py 
find ./libdogs -iname *.h | xargs ./cpplint.py
find ./libdogs -iname *.c | xargs ./cpplint.py 
