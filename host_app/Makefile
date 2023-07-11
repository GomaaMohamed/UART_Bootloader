#Home of the Work Space
#Edit the path of the project here
HOME := /home/gomaa/Desktop/Tech/Interview/Projects/02-Bootloader/host_burner
CC := gcc
#Directories that will be searched for Headers
INCLUDES = -I $(HOME)/include 
#Source Files 
SRCS = $(wildcard $(HOME)/*.c) \
       $(wildcard $(HOME)/sources/*.c) 
PATH_TO_OBJECT := "burner"

build:
	@$(CC) -g  $(SRCS) -o $(PATH_TO_OBJECT)  $(INCLUDES)
	@echo "===================================="
	@echo "===================================="
	@echo "........ Successfully Built ........"
	@date -R
	@echo "===================================="
	@echo "===================================="

clean:
	@rm -f burner *.o *.s *.i *.exe *.bin
	@echo "===================================="
	@echo "===================================="
	@echo ".............. Done ................"
	@date -R
	@echo "===================================="
	@echo "===================================="


        


