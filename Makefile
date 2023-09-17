# Urnukh Tsogt URT633
# 11267557
#
# Mitchell Risling
# MJR810
# 11221612
#
# CMPT332
# ASSIGNMENT


# platform and architecture
PLATFORM = $(shell uname -s)
ARCH = $(shell uname -m)
# based on which platform we are on only compile # files used by all 4 parts of A # files used by all 4 parts of A # files used by all 4 parts of A
ifeq ($(PLATFORM), Linux)
	AVAILABLE = part2 part3 part4 partC partE
else
	AVAILABLE = part1
endif
# compiler and flgas
#

# compiler and flags
CC = gcc
CFLAGS = -g -L ./
CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic -g -D$(ARCH) -I ./

# Source files for each executable
WINSRC   = partA1_WIN_main.c partA_check_input.c partA_calc_fib.c \
		   partA_create_windows_threads.c

UBCSRC 	 = partA2_UBC_main.c partA_check_input.c partA_calc_fib.c \
		   partA_create_linux_threads.c

POSIXSRC = partA3_POSIX_main.c partA_check_input.c partA_calc_fib.c \
		   partA_create_linux_threads.c

LISTSRC  = list_adders.c list_movers.c list_removers.c mytestlist.c

SHELLSRC = partE_shell_main.c  partE_shell_get_input.c partE_shell_common.c \
		   partE_shell_commands.c

# Object files
# windows onject files will be same name as src files
# except _win32.o in place of .c
WINOBJ = $(WINSRC:.c=_win32.o)
# linux obj files will be same name as src files
# except _linux.o in place of c
UBCOBJ = $(UBCSRC:.c=_linux.o)
POSIXOBJ = $(POSIXSRC:.c=_linux.o)
LISTOBJ = $(LISTSRC:.c=_linux.o)
SHELLOBJ= $(SHELLSRC:.c=.o)

# binary names
WINBIN  =  partA1
UBCBIN = partA2
POSIXBIN = partA3
#UNIXBIN = partA4
LISTBIN = mytestlist
SHELLBIN = partEShell

#
# recipes
#

# target for each part
all: $(AVAILABLE)
part1: $(WINBIN)
part2: $(UBCBIN)
part3: $(POSIXBIN)
#part4: $(UNIXBIN)
partC: $(LISTBIN) your_test_list
# partD
partE: $(SHELLBIN)

# windows recipes - partA1
$(WINBIN) : $(WINOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

partA1_WIN_main_win32.o : partA1_WIN_main.c
	$(CC) -o $@ partA1_WIN_main.c -c $(CPPFLAGS)

partA_calc_fib_win32.o : partA_calc_fib.c
	$(CC) -o $@ partA_calc_fib.c -c $(CPPFLAGS)

partA_check_input_win32.o : partA_check_input.c
	$(CC) -o $@ partA_check_input.c -c $(CPPFLAGS)

partA_create_windows_threads_win32.o : partA_create_windows_threads.c
	$(CC) -o $@ partA_create_windows_threads.c -c $(CPPFLAGS)

# linux recipes
LIBDIR = /student/cmpt332/pthreads/lib/
INCDIR = /student/cmpt332/pthreads

# partA2
$(UBCBIN) : $(UBCOBJ)
	$(CC) -o $@ $^ $(CFLAGS) -L $(LIBDIR)/$(PLATFORM)$(ARCH)/ -l:libpthreads.a


partA2_UBC_main_linux.o : partA2_UBC_main.c
	$(CC) -o $@ -c $^ $(CPPFLAGS) -I$(INCDIR)

# partA3
$(POSIXBIN) : $(POSIXOBJ)
	$(CC) -o $@ $(POSIXOBJ) -L $(LIBDIR)/$(PLATFORM)$(ARCH)/ -l:libpthreads.a

partA3_POSIX_main_linux.o : partA3_POSIX_main.c
	$(CC) -o $@ -c $^ $(CPPFLAGS) -I$(INCDIR)


# shared object files for linux execs
partA_calc_fib_linux.o : partA_calc_fib.c
	$(CC) -o $@ -c $^ $(CPPFLAGS) -I$(INCDIR)

partA_check_input_linux.o : partA_check_input.c
	$(CC) -o $@ -c $^ $(CPPFLAGS) -I$(INCDIR)


partA_create_linux_threads_linux.o : partA_create_linux_threads.c
	$(CC) -o $@ -c $^ $(CPPFLAGS) -I$(INCDIR)

# partC

your_test_list : $(LISTBIN)
	$(CC) -c testlist.c $(CPPFLAGS)
	$(CC) -o your_test_list  list_adders_linux.o list_movers_linux.o\
		list_removers_linux.o mytestlist_linux.o $(CFLAGS)

$(LISTBIN) : $(LISTOBJ)
	$(CC) -o $@ $(LISTOBJ) $(CPPFLAGS)
	ar rcs liblist.a $(LISTOBJ)

list_adders_linux.o : list_adders.c
	$(CC) -o $@ -c list_adders.c $(CPPFLAGS)

list_movers_linux.o : list_movers.c
	$(CC) -o $@ -c list_movers.c $(CPPFLAGS)

list_removers_linux.o : list_removers.c
	$(CC) -o $@ -c list_removers.c $(CPPFLAGS)

mytestlist_linux.o : mytestlist.c
	$(CC) -o $@ -c mytestlist.c $(CPPFLAGS)


testA: test_partA_linux
	$(CC) -o test_partA_linux $(CFLAGS) partA_test_linux.o check_input.o \
		calc_fib.o -L ./

test_partA_linux : partA_test_linux.o check_input.o calc_fib.o
	$(CC) $(CPPFLAGS) partA_test_linux.c check_input.c calc_fib.c

$(SHELLBIN) : $(SHELLOBJ)
	$(CC) -o $@ $(SHELLOBJ) $(CFLAGS)

partE_shell_main.o : partE_shell_main.c partE_shell_get_input.o\
	partE_shell_commands.o
	$(CC) -c  partE_shell_main.c  $(CPPFLAGS)

partE_shell_get_input.o : partE_shell_get_input.c partE_shell_common.o
	$(CC) -c  partE_shell_get_input.c  $(CPPFLAGS)

partE_shell_commands.o : partE_shell_commands.c
	$(CC) -c partE_shell_commands.c  $(CPPFLAGS)

partE_shell_common.o : partE_shell_common.c
	$(CC) -c partE_shell_common.c $(CPPFLAGS)

# remove all .o files and .a files created
clean:
	rm -f ./*.o *./a
	rm -f $(WINBIN) $(UBCBIN) $(POSIXBIN) $(UNIXBIN) $(LISTBIN) $(SHELLBIN)
	rm -f ./your_test_list ./liblist.a

.PHONY: all clean part1 part2 part3 part4 partC partE testA
