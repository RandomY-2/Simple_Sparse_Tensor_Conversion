COMPILER = g++
CFLAGS = -Wall -ggdb -O0
INCL_PATHS =

csr: csr.cpp utils.cpp
	$(COMPILER) -std=c++20 $(INCL_PATHS) csr.cpp utils.cpp -o $@ $(CFLAGS)

clean_csr:
	rm -rf csr
	rm -rf *.dSYM

csf: csf.cpp utils.cpp
	$(COMPILER) -std=c++20 $(INCL_PATHS) csf.cpp utils.cpp -o $@ $(CFLAGS)

clean_csf:
	rm -rf csf
	rm -rf *.dSYM
