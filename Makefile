.PHONY: clean All

All:
	@echo "----------Building project:[ Hello - Debug ]----------"
	@cd "Hello" && "$(MAKE)" -f  "Hello.mk"
clean:
	@echo "----------Cleaning project:[ Hello - Debug ]----------"
	@cd "Hello" && "$(MAKE)" -f  "Hello.mk" clean
