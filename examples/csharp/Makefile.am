
bin_PROGRAMS = csharp

csharp_SOURCES = \
	decoder.cpp \
	csharp.cpp \
	csharp-lexer.ll \
	main.cpp

noinst_HEADERS = \
	csharp.h

# set the include path found by configure
INCLUDES= \
	-I$(top_srcdir)/include \
	$(all_includes)

# the library search path.
csharp_LDADD =

csharp_LDFLAGS = \
	$(all_libraries)

parser: $(top_srcdir)/examples/csharp/csharp.g
	$(top_builddir)/src/kdev-pg --output=csharp $(top_srcdir)/examples/csharp/csharp.g
