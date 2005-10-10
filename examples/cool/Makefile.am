
bin_PROGRAMS = cool

cool_SOURCES = \
	decoder.cpp \
	cool.cpp \
	cool-lexer.ll \
	main.cpp

noinst_HEADERS = \
	cool.h

# set the include path found by configure
INCLUDES= \
	-I$(top_srcdir)/include \
	$(all_includes)

# the library search path.
cool_LDADD =

cool_LDFLAGS = \
	$(all_libraries)

parser: $(top_srcdir)/examples/cool/cool.g
	$(top_builddir)/src/kdev-pg --output=cool $(top_srcdir)/examples/cool/cool.g
