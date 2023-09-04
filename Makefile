ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please create an environment variable PVSNESLIB_HOME with path to its folder and restart application. (you can do it on windows with <setx PVSNESLIB_HOME "/c/snesdev">)")
endif

include ${PVSNESLIB_HOME}/devkitsnes/snes_rules

.PHONY: bitmaps all

#---------------------------------------------------------------------------------
# ROMNAME is used in snes_rules file
export ROMNAME := transparency

all: bitmaps $(ROMNAME).sfc

cleanGfxBackground:
	@echo clean Background graphics data
	@rm -f res/*.pic res/*.pal res/*.map

clean: cleanBuildRes cleanRom cleanGfx cleanGfxBackground

background.pic: res/background.png
	@echo convert bitmap ... $(notdir $@)
	$(GFXCONV) -pc16 -n -gs8 -pe0 -m -fpng  $<

bitmaps : background.pic
