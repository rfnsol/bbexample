AUTOMAKE_OPTIONS = foreign

CFLAGS = -Wall -pedantic -O2
include_HEADERS = bbexample.h host.h

#lib_LTLIBRARIES = libbbexample.la
#libbbexample_la_SOURCES  = bbexamplelib.c host.c
#libbbexample_la_LDFLAGS= -version-info 1:0:0

bin_PROGRAMS = bbexample
bbexample_SOURCES = bbexample.c host.c
bbexample_LDADD = libbbexample.la
