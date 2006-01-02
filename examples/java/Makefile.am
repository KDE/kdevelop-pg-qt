
bin_PROGRAMS = java

java_SOURCES = \
	decoder.cpp \
	java.cpp \
	java_lookahead.cpp \
	java-lexer.ll \
	main.cpp

noinst_HEADERS = \
	java.h

# set the include path found by configure
INCLUDES= \
	-I$(top_srcdir)/include \
	$(all_includes)

# the library search path.
java_LDADD =

java_LDFLAGS = \
	$(all_libraries)

parser: $(top_srcdir)/examples/java/java.g
	$(top_builddir)/src/kdev-pg --output=java $(top_srcdir)/examples/java/java.g
