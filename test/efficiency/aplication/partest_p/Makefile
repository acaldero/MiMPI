# Generated automatically from Makefile.in by configure.
#---------------------- partest' MAKEFILE -------------------- 
 



# --- 1.- Opciones del sistema base ---

CC             = gcc
LIB_PATH       = ./../../../../lib
INCLUDE_PATH   = -I./ -I./../../../../src/ -I./../../../../include/
SOURCE_PATH    = .
CFLAGS         = -DHAVE_CONFIG_H  -D__LINUX__
LIBLINK        = -lmpi -lpthread -lz -llzo



# --- 2.- Perfil de la libreria -------

OBJETOS   = \
            $(SOURCE_PATH)/partest.o



 
#--------------------------
# Reglas de compilacion ...
#-------------------------- 

all:    init    partest
refast: clean   partest
fast:   partest

partest: $(OBJETOS)
	@echo "   Building partest :"
	@echo "     partest.linux.xmp ..."
	@$(CC)  $(CFLAGS) -L$(LIB_PATH) -o partest.linux.xmp  $(SOURCE_PATH)/partest.o  $(LIBLINK)


init:
	@echo [2J 
	@echo "[1;1f" 
	@echo "" 
	@echo "    partest" 
	@echo "   ---------"
	@echo "" 
	@echo "   Computer  :"
	@echo "     "`uname -a` 
	@echo "   Options   :"
	@echo "     "$(CFLAGS)
	@echo "   Directory :"
	@echo "     "$(INCLUDE_PATH)
	@echo "   Compiling :"

%.o: %.c
	@echo "     $< ..." 
	@$(CC)  $(CFLAGS) $(INCLUDE_PATH) -c $< -o $@ 


clean: 
	@echo "   Removing trash..."
	@rm -fr $(OBJETOS) ./partest.linux.xmp
	@echo "   Trash succesfully removed !."




# ---------------------- partest' MAKEFILE -------------------- 

