# Generated automatically from Makefile.in by configure.
# ------------------------------ MAKEFILE ----------------------- 
 


# --- 1.- Opciones del sistema base ---

MAKE          = gmake
SRCDIR        = .
INCLUDE_PATH  = -I./
DIR           = test_run  test_reduce  xmp_run  mpi_exec


# --- 2.- Reglas de compilacion -------

all:    init  compo
fast:         compo


init:
	@echo [2J 
	@echo "[1;1f" 
	@echo "" 
	@echo "    Utilities" 
	@echo "   -----------" 
	@echo "" 

compo:
	@set -e;  for i in $(DIR);   do $(MAKE) -C $$i -f Makefile       fast ;  done



clean: 
	@echo "   Removing trash..."
	@set -e;  for i in $(DIR);   do $(MAKE) -C $$i -f Makefile       clean ;  done
	@echo "   Trash succesfully removed !."



# ----------------------------- END MAKEFILE -------------------- 

