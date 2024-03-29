CeladonCity_Condominiums_1F_MapScripts:: @ 816C320
	.byte 0

CeladonCity_Condominiums_1F_EventScript_TeaWoman:: @ 816C321
	lock
	faceplayer
	goto_if_set FLAG_TALKED_TO_TEA_LADY_AFTER_HOF, CeladonCity_Condominiums_1F_EventScript_TeaWomanAfterTea
	goto_if_set FLAG_SYS_GAME_CLEAR, CeladonCity_Condominiums_1F_EventScript_TeaWomanMentionDaisy
	goto_if_set FLAG_GOT_TEA, CeladonCity_Condominiums_1F_EventScript_TeaWomanAfterTea
	msgbox CeladonCity_Condominiums_1F_Text_TryThisDrinkInstead
	setflag FLAG_GOT_TEA
	giveitem ITEM_TEA
	compare VAR_RESULT, FALSE
	goto_if_eq EventScript_BagIsFull
	checkspeedchoice PLOTLESS, PLOT_KEEP
	call_if_ne CeladonCity_Condominiums_1F_Plotless
	msgbox CeladonCity_Condominiums_1F_Text_NothingBeatsThirstLikeTea
	release
	end

CeladonCity_Condominiums_1F_Plotless::
	giveitem ITEM_LIFT_KEY
	giveitem ITEM_SILPH_SCOPE
	giveitem ITEM_CARD_KEY
	setflag FLAG_HIDE_TOWER_FUJI
	clearflag FLAG_HIDE_POKEHOUSE_FUJI
	setflag FLAG_RESCUED_MR_FUJI
	setflag FLAG_CAN_USE_ROCKET_HIDEOUT_LIFT
	checkspeedchoice PLOTLESS, PLOT_FULL
	goto_if_eq CeladonCity_Condominiums_1F_FullPlotless
	return
	end

CeladonCity_Condominiums_1F_FullPlotless::
	setflag FLAG_HIDE_TOWER_ROCKET_1
	setflag FLAG_HIDE_TOWER_ROCKET_2
	setflag FLAG_HIDE_TOWER_ROCKET_3
	setflag FLAG_HIDE_HIDEOUT_GIOVANNI
	clearflag FLAG_HIDE_LIFT_KEY
	clearflag FLAG_HIDE_SILPH_SCOPE
	setflag FLAG_HIDE_CELADON_ROCKETS
	setvar VAR_MAP_SCENE_SILPH_CO_11F, 1
	setflag FLAG_HIDE_SILPH_ROCKETS
	setflag FLAG_HIDE_SAFFRON_ROCKETS
	clearflag FLAG_HIDE_SAFFRON_CIVILIANS
	setflag FLAG_HIDE_MISC_KANTO_ROCKETS
	settrainerflag TRAINER_TEAM_ROCKET_GRUNT_12
	return
	end

CeladonCity_Condominiums_1F_EventScript_TeaWomanAfterTea:: @ 816C36A
	msgbox CeladonCity_Condominiums_1F_Text_MyDearMonsKeepMeCompany
	release
	end

CeladonCity_Condominiums_1F_EventScript_TeaWomanMentionDaisy:: @ 816C374
	famechecker FAMECHECKER_DAISY, 4
	setflag FLAG_TALKED_TO_TEA_LADY_AFTER_HOF
	msgbox CeladonCity_Condominiums_1F_Text_DaisyComesToBuyTea
	release
	end

CeladonCity_Condominiums_1F_EventScript_Meowth:: @ 816C38E
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MEOWTH, 0
	msgbox CeladonCity_Condominiums_1F_Text_Meowth
	waitmoncry
	release
	end

CeladonCity_Condominiums_1F_EventScript_Clefairy:: @ 816C3A1
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CLEFAIRY, 0
	msgbox CeladonCity_Condominiums_1F_Text_Clefairy
	waitmoncry
	release
	end

CeladonCity_Condominiums_1F_EventScript_Nidoran:: @ 816C3B4
	lock
	faceplayer
	waitse
	playmoncry SPECIES_NIDORAN_F, 0
	msgbox CeladonCity_Condominiums_1F_Text_Nidoran
	waitmoncry
	release
	end

CeladonCity_Condominiums_1F_EventScript_SuiteSign:: @ 816C3C7
	msgbox CeladonCity_Condominiums_1F_Text_ManagersSuite, MSGBOX_SIGN
	end
