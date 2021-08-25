# Author: strawberryhacker

project_path = $(shell pwd)/..
output_path  = $(project_path)/output
output_name  = allocator

#---------------------------------------------------------------------------------------------------

source += $(project_path)/allocator.c
source += $(project_path)/main.c

include += $(project_path)/allocator.h
include += $(project_path)/utilities.h

#---------------------------------------------------------------------------------------------------

.PHONY: main

main: $(source) $(include)
	@mkdir -p $(output_path)
	@$(CC) $(source) -o $(output_path)/$(output_name)
	@$(output_path)/$(output_name)
	@rm -rf $(output_path)
