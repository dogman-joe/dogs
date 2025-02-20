MODULES=libdogs kenr arch drivers

all:
	for dir in $(MODULES); do \
	  (cd $$dir; ${MAKE} all);\
	  done
