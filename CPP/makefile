# All targets with # symbol are self-documenting, i.e. make help or simply make will
# show the targets among available options
#
# User targets are at the bottom
#
ifndef ROOTSYS
all:
	@echo "ROOTSYS is not set. Please set ROOT environment properly"; echo
else
ifndef ROOFITSYS
all:
	@echo "ROOFITSYS is not set. Please set ROOT environment properly"; echo
else


RM  = /bin/rm

MELADIR = $(shell pwd)/../JHUGenMELA/MELA/
MELASRCDIR = $(MELADIR)/src
MELAOBJDIR = $(MELADIR)/obj
# Modify MELALIBDIR for the gcc version as needed
MELALIBDIR = ${MELA_LIB_PATH}
# _melapkgpath_ should refer to the root compilation path just like MELADIR with an extra '/'.
# If environment variables need to be inserted without expansion for portability,
# you can use '.oODOLLAROo..oOOPEN_BRACKETOo.[YOUR_ENV_VARIABLE].oOCLOSE_BRACKETOo.',
# e.g. '.oODOLLAROo..oOOPEN_BRACKETOo.CMSSW_BASE.oOCLOSE_BRACKETOo.' in place of '${CMSSW_BASE}' as used in the CMS-specific compilation.
MELAPKGPATH = $(MELADIR)/
LIB = libJHUGenMELAMELA.so
LIBRULE = $(MELALIBDIR)/$(LIB)

pyLIB = Mela$(shell python3-config --extension-suffix)
pyLIBRULE = $(MELALIBDIR)/$(pyLIB)
pyLINKFILE = $(MELADIR)/python/mela_binding.cpp

ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs) -Lrootlib
NLIBS = $(ROOTLIBS)
NLIBS += -L$(ROOFITSYS)/lib -lMinuit -lRooFitCore -lRooFit -lgfortran
LIBS = $(filter-out -lNew, $(NLIBS))

ROOFITINC = -I$(ROOFITSYS)/include
ROOTINC = $(ROOFITINC)

CC = g++
CPPINC = -I$(MELADIR)/interface $(ROOTINC)
CPPLOAD = -L$(MELALIBDIR) -lmcfm_709 -ljhugenmela -lcollier $(LIBS)
CPPOPTS =  -fPIC -O2 -ftree-vectorize -fipa-pta -felide-constructors -fvisibility-inlines-hidden -fno-math-errno \
	--param vect-max-version-for-alias-checks=50 -fmessage-length=0 -fdiagnostics-show-option \
	-Werror=unused-value \
	 $(shell root-config --cflags) -D_melapkgpath_=$(MELAPKGPATH)
CPPFLAGS = $(CPPOPTS) $(CPPINC) $(CPPLOAD)

LINKER = g++
LINKERFLAGS = -Wl,-rpath=$(MELALIBDIR),-soname,$(LIB) $(CPPLOAD)

SOURCESCC = $(wildcard $(MELASRCDIR)/*.cc)
SOURCESCXX = $(wildcard $(MELASRCDIR)/*.cxx)
OBJECTSPRIM = $(SOURCESCC:.cc=.o) $(SOURCESCXX:.cxx=.o)
OBJECTS = $(subst $(MELASRCDIR),$(MELAOBJDIR),$(OBJECTSPRIM))
DEPS = $(OBJECTS:.o=.d)

all: tutorial

tutorial: tutorial_link.cpp
	@g++ $(CPPFLAGS) -L$(MELALIBDIR) -lJHUGenMELAMELA tutorial_link.cpp



include $(DEPS)


endif
endif
