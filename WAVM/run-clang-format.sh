find . \( -iname *.h -o -iname *.cpp \) -not -path "./ThirdParty/*" | xargs clang-format-7 -i