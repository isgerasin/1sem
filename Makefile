.PHONY: clean All

All:
	@echo "----------Building project:[ Differ - Debug ]----------"
	@cd "Differ" && "$(MAKE)" -f  "Differ.mk"
clean:
	@echo "----------Cleaning project:[ Differ - Debug ]----------"
	@cd "Differ" && "$(MAKE)" -f  "Differ.mk" clean
