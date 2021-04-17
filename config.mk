GAME_VERSION   ?= FIRERED
GAME_REVISION  ?= 1
GAME_LANGUAGE  ?= ENGLISH
DEVMODE        ?= 0
MODERN         ?= 0
COMPARE        ?= 0
TITLE          := PKFIRE SPEED
GAME_CODE      := MBDN
BUILD_NAME     := firered-speedchoice
ifeq ($(DEVMODE),1)
BUILD_NAME     := $(BUILD_NAME)-dev
endif
__CLION_IDE__  ?= 0
ifeq ($(__CLION_IDE__),1)
MODERN          = 1
endif
