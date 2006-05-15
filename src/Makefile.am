
bin_PROGRAMS = kdev-pg

kdev_pg_SOURCES = \
	ASBeautifier.cpp \
	ASFormatter.cpp \
	kdev-pg.cpp \
	kdev-pg-visitor.cpp \
	kdev-pg-default-visitor.cpp \
	kdev-pg-pretty-printer.cpp \
	kdev-pg-global.cpp \
	kdev-pg-code-gen.cpp \
	kdev-pg-ast-gen.cpp \
	kdev-pg-visitor-gen.cpp \
	kdev-pg-visitor-bits-gen.cpp \
	kdev-pg-default-visitor-gen.cpp \
	kdev-pg-beautifier.cpp \
	kdev-pg-checker.cpp \
	kdev-pg-main.cpp \
	kdev-pg-utils.cpp \
	kdev-pg-first.cpp \
	kdev-pg-follow.cpp \
	kdev-pg-clone-tree.cpp \
	kdev-pg-parser.yy \
	kdev-pg-lexer.ll

# set the include path found by configure
INCLUDES= -I$(top_srcdir)/include $(all_includes)

# the library search path.
kdev_pg_LDFLAGS = $(all_libraries)

# let yacc create a header file
AM_YFLAGS = -d
