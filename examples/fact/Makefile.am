
bin_PROGRAMS = fact

fact_SOURCES = \
	decoder.cpp \
	fact.cpp \
	fact_io.cpp \
	fact_lexer.ll \
	main.cpp

noinst_HEADERS = \
	fact.h

# set the include path found by configure
INCLUDES= \
	-I$(top_srcdir)/include \
	$(all_includes)

# the library search path.
fact_LDADD =

fact_LDFLAGS = \
	$(all_libraries)

parser: $(top_srcdir)/examples/fact/fact.g
	$(top_builddir)/src/kdev-pg --output=fact $(top_srcdir)/examples/fact/fact.g
