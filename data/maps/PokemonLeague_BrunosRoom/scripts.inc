.set LOCALID_BRUNO, 1

PokemonLeague_BrunosRoom_MapScripts:: @ 8162685
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_BrunosRoom_OnResume
	map_script MAP_SCRIPT_ON_LOAD, PokemonLeague_BrunosRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PokemonLeague_BrunosRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PokemonLeague_BrunosRoom_OnFrame
	.byte 0

PokemonLeague_BrunosRoom_OnResume:: @ 816269A
	setvar VAR_0x8004, 1
	call PokemonLeague_EventScript_DoLightingEffect
	end

PokemonLeague_BrunosRoom_OnLoad:: @ 81626A5
	call_if_set FLAG_DEFEATED_BRUNO, PokemonLeague_BrunosRoom_EventScript_SetDoorOpen
	compare VAR_MAP_SCENE_POKEMON_LEAGUE, 2
	call_if_eq PokemonLeague_BrunosRoom_EventScript_CloseEntry
	end

PokemonLeague_BrunosRoom_EventScript_CloseEntry:: @ 81626BA
	call PokemonLeague_EventScript_CloseEntry
	return

PokemonLeague_BrunosRoom_EventScript_SetDoorOpen:: @ 81626C0
	call PokemonLeague_EventScript_SetDoorOpen
	return

PokemonLeague_BrunosRoom_OnWarp:: @ 81626C6
	map_script_2 VAR_TEMP_1, 0, PokemonLeague_BrunosRoom_EventScript_TurnPlayerNorth
	.2byte 0

PokemonLeague_BrunosRoom_EventScript_TurnPlayerNorth:: @ 81626D0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

PokemonLeague_BrunosRoom_OnFrame:: @ 81626D5
	map_script_2 VAR_MAP_SCENE_POKEMON_LEAGUE, 1, PokemonLeague_BrunosRoom_EventScript_EnterRoom
	.2byte 0

PokemonLeague_BrunosRoom_EventScript_EnterRoom:: @ 81626DF
	lockall
	call PokemonLeague_EventScript_EnterRoom
	setvar VAR_MAP_SCENE_POKEMON_LEAGUE, 2
	releaseall
	end

PokemonLeague_BrunosRoom_EventScript_Bruno:: @ 81626EC
	lock
	faceplayer
	famechecker FAMECHECKER_BRUNO, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	goto_if_set FLAG_DEFEATED_BRUNO, PokemonLeague_BrunosRoom_EventScript_PostBattle
	famechecker FAMECHECKER_BRUNO, 0
	famechecker FAMECHECKER_BRUNO, 1
	call_if_unset FLAG_SYS_GAME_CLEAR, PokemonLeague_BrunosRoom_EventScript_Intro
	call_if_set FLAG_SYS_GAME_CLEAR, PokemonLeague_BrunosRoom_EventScript_RematchIntro
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	specialvar VAR_RESULT, ShouldDoE4R2
	compare VAR_RESULT, TRUE
	call_if_ne PokemonLeague_BrunosRoom_EventScript_Battle
	specialvar VAR_RESULT, ShouldDoE4R2
	compare VAR_RESULT, TRUE
	call_if_eq PokemonLeague_BrunosRoom_EventScript_Rematch
	clearflag FLAG_TEMP_5
	goto PokemonLeague_BrunosRoom_EventScript_DefeatedBruno
	end

PokemonLeague_BrunosRoom_EventScript_Intro:: @ 8162751
	msgbox PokemonLeague_BrunosRoom_Text_Intro
	return

PokemonLeague_BrunosRoom_EventScript_RematchIntro:: @ 816275A
	msgbox PokemonLeague_BrunosRoom_Text_RematchIntro
	return

PokemonLeague_BrunosRoom_EventScript_Battle:: @ 8162763
	trainerbattle_no_intro TRAINER_ELITE_FOUR_BRUNO, PokemonLeague_BrunosRoom_Text_Defeat
	return

PokemonLeague_BrunosRoom_EventScript_Rematch:: @ 816276E
	trainerbattle_no_intro TRAINER_ELITE_FOUR_BRUNO_2, PokemonLeague_BrunosRoom_Text_Defeat
	return

PokemonLeague_BrunosRoom_EventScript_PostBattle:: @ 8162779
	msgbox PokemonLeague_BrunosRoom_Text_PostBattle
	closemessage
	compare VAR_FACING, DIR_NORTH
	call_if_eq PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayRight
	compare VAR_FACING, DIR_SOUTH
	call_if_eq PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayLeft
	compare VAR_FACING, DIR_WEST
	call_if_eq PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayDown
	compare VAR_FACING, DIR_EAST
	call_if_eq PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayDown
	release
	end

PokemonLeague_BrunosRoom_EventScript_DefeatedBruno:: @ 81627B0
	setflag FLAG_DEFEATED_BRUNO
	call PokemonLeague_EventScript_OpenDoor
	msgbox PokemonLeague_BrunosRoom_Text_PostBattle
	closemessage
	compare VAR_FACING, DIR_NORTH
	call_if_eq PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayRight
	compare VAR_FACING, DIR_SOUTH
	call_if_eq PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayLeft
	compare VAR_FACING, DIR_WEST
	call_if_eq PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayDown
	compare VAR_FACING, DIR_EAST
	call_if_eq PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayDown
	release
	end

PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayLeft:: @ 81627EF
	applymovement LOCALID_BRUNO, Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayRight:: @ 81627FA
	applymovement LOCALID_BRUNO, Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

PokemonLeague_BrunosRoom_EventScript_BrunoLookAwayDown:: @ 8162805
	applymovement LOCALID_BRUNO, Movement_WalkInPlaceFastestDown
	waitmovement 0
	return
