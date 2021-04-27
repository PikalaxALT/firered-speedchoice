PewterCity_Mart_MapScripts:: @ 816A6CD
	.byte 0

PewterCity_Mart_EventScript_Youngster:: @ 816A6CE
	msgbox PewterCity_Mart_Text_BoughtWeirdFishFromShadyGuy, MSGBOX_NPC
	end

PewterCity_Mart_EventScript_Boy:: @ 816A6D7
	msgbox PewterCity_Mart_Text_GoodThingsIfRaiseMonsDiligently, MSGBOX_NPC
	end

PewterCity_Mart_EventScript_Clerk:: @ 816A6E0
	goto_if_questlog EventScript_ReleaseEnd
	lock
	faceplayer
	message Text_MayIHelpYou
	waitmessage
	checkspeedchoice BETTER_MARTS, MARTS_ON
	goto_if_eq PewterCity_Mart_EventScript_BetterMart
	pokemart PewterCity_Mart_Items
	msgbox Text_PleaseComeAgain
	release
	end

PewterCity_Mart_EventScript_BetterMart::
	pokemart PewterCity_BetterMart_Items
	msgbox Text_PleaseComeAgain
	release
	end

	.align 2
PewterCity_Mart_Items:: @ 816A708
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_NONE
	release
	end

	.align 2
PewterCity_BetterMart_Items::
	.2byte
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SPECIAL
	.2byte ITEM_X_ACCURACY
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_NONE
	release
	end
