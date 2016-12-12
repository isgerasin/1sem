.PHONY: clean All

All:
	@echo "----------Building project:[ compiler - Debug ]----------"
	@cd "compiler" && "$(MAKE)" -f  "compiler.mk"
clean:
	@echo "----------Cleaning project:[ compiler - Debug ]----------"
	@cd "compiler" && "$(MAKE)" -f  "compiler.mk" clean
