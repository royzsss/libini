AUTMAKE_OPTIONS = foreign

inidir = $(libdir)
ini_PROGRAMS = libini.so
libini_so_SOURCES = ini.c list.c parse.c
libini_sodir = /usr/local/lib/

include_HEADERS = ini.h
noinst_HEADERS = ini-def.h list.h parse.h

AM_CFLAGS = -fPIC
AM_LDFLAGS = -shared

SUBDIRS = . test
