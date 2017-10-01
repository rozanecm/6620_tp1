python ./cpplint.py --extensions=h,cpp,hpp,c --filter=`cat filter_options` `find -regextype posix-egrep -regex '.*\.(h|hpp|c|cpp)'`
