OUTPUT=blowfish

NCC=nvcc
CC_OPT=-std=c99

.PHONY: all
all: $(OUTPUT)

$(OUTPUT) : $(OUTPUT).cu $(OUTPUT)_test.cu $(OUTPUT).h 
	$(NCC) -o $(OUTPUT) $(OUTPUT).cu $(OUTPUT)_test.cu

.PHONY: clean
clean:
	rm $(OUTPUT)
