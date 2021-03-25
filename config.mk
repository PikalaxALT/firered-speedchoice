GAME_VERSION   ?= FIRERED
GAME_REVISION  ?= 1
GAME_LANGUAGE  ?= ENGLISH
MODERN         ?= 0
COMPARE        ?= 0
TITLE          := PKFIRE SPEED
GAME_CODE      := MBDN
BUILD_NAME     := firered-speedchoice
__CLION_IDE__  ?= 0
ifeq ($(__CLION_IDE__),1)
MODERN          = 1
endif
