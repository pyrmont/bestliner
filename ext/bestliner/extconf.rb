require "mkmf"
dir_config("bestline")
have_header("bestline.h")
create_makefile "bestliner/bestliner"
