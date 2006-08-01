
bin_PROGRAMS = csharp

csharp_SOURCES = \
	decoder.cpp \
	csharp.cpp \
	csharp_pp.cpp \
	csharp_lexer.ll \
	csharp_io.cpp \
	csharp_pp_scope.cpp \
	csharp_pp_handler_visitor.cpp \
	main.cpp

noinst_HEADERS = \
	csharp.h \
	csharp_pp.h \
	csharp_pp_scope.h \
	csharp_pp_handler_visitor.h

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

pp_parser: $(top_srcdir)/examples/csharp/csharp_pp.g
	$(top_builddir)/src/kdev-pg --output=csharp_pp $(top_srcdir)/examples/csharp/csharp_pp.g
