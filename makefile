#
# MIT License
#
# Copyright(c) 2021 João Vicente Souto <joaovicentesouto@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

#
# Default make rule.
#
.DEFAULT_GOAL := all

#===============================================================================
# Build Options
#===============================================================================

# Verbose Build?
export VERBOSE ?= no

# Release Version?
export RELEASE ?= no

# Extras
export ADDONS ?=

# Name of the Executable
export EXEC = program

export JOGADORES_POR_EQUIPE ?=
export GRUPO_MIN            ?=
export GRUPO_MAX            ?=
export DANO_MIN             ?=
export DANO_MAX             ?=
export DANO_CURA            ?=
export DELAY_MIN            ?=
export DELAY_MAX            ?=
export DELAY_GERENTE        ?=
export DELAY_LIMPADOR       ?=
export PARTIDAS_MAX         ?=
export PARTIDA_TEMPO_MAX    ?=

#===============================================================================
# Directories
#===============================================================================

export ROOTDIR    := $(CURDIR)
export BINDIR     := $(ROOTDIR)/bin
export BUILDDIR   := $(ROOTDIR)/build
export INCDIR     := $(ROOTDIR)/include
export SRCDIR     := $(ROOTDIR)/src

#===============================================================================
# Toolchain Configuration
#===============================================================================

# Builds everything.
all:
	$(MAKE) -C $(SRCDIR) all

# Cleans build.
clean: distclean
	$(MAKE) -C $(SRCDIR) clean

# Cleans everything.
distclean:
	$(MAKE) -C $(SRCDIR) distclean

