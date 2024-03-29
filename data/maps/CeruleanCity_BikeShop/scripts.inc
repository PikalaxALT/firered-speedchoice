CeruleanCity_BikeShop_MapScripts:: @ 816ABBC
	.byte 0

CeruleanCity_BikeShop_EventScript_Clerk:: @ 816ABBD
	lock
	faceplayer
	goto_if_set FLAG_GOT_BICYCLE, CeruleanCity_BikeShop_EventScript_AlreadyGotBicycle
	goto_if_set FLAG_GOT_BIKE_VOUCHER, CeruleanCity_BikeShop_EventScript_ExchangeBikeVoucher
	showmoneybox 0, 0, 0
	message CeruleanCity_BikeShop_Text_WelcomeToBikeShop
	waitmessage
	multichoice 11, 0, MULTICHOICE_BIKE_SHOP, FALSE
	switch VAR_RESULT
	case 0, CeruleanCity_BikeShop_EventScript_TryPurchaseBicycle
	case 1, CeruleanCity_BikeShop_EventScript_ClerkGoodbye
	case 127, CeruleanCity_BikeShop_EventScript_ClerkGoodbye
	end

@ The Bicycle price / players money is never actually checked
CeruleanCity_BikeShop_EventScript_TryPurchaseBicycle:: @ 816AC07
	msgbox CeruleanCity_BikeShop_Text_SorryYouCantAffordIt
	goto CeruleanCity_BikeShop_EventScript_ClerkGoodbye
	end

CeruleanCity_BikeShop_EventScript_ClerkGoodbye:: @ 816AC15
	msgbox CeruleanCity_BikeShop_Text_ThankYouComeAgain
	hidemoneybox 0, 0
	release
	end

CeruleanCity_BikeShop_EventScript_ExchangeBikeVoucher:: @ 816AC22
	msgbox CeruleanCity_BikeShop_Text_OhBikeVoucherHereYouGo
	msgreceiveditem CeruleanCity_BikeShop_Text_ExchangedVoucherForBicycle, ITEM_BICYCLE, 1, MUS_OBTAIN_KEY_ITEM
	setflag FLAG_GOT_BICYCLE
	checkspeedchoice EARLY_BIKE, EARLY_BIKE_YES
	goto_if_eq CeruleanCity_BikeShop_EventScript_RandomizedItem
	additem ITEM_BICYCLE
	goto CeruleanCity_BikeShop_EventScript_TakeBikeVoucher

CeruleanCity_BikeShop_EventScript_RandomizedItem::
	additem ITEM_BICYCLE  @ overwritten by rando
CeruleanCity_BikeShop_EventScript_TakeBikeVoucher::
	removeitem ITEM_BIKE_VOUCHER
	msgbox CeruleanCity_BikeShop_Text_ThankYouComeAgain
	release
	end

CeruleanCity_BikeShop_EventScript_AlreadyGotBicycle:: @ 816AC58
	msgbox CeruleanCity_BikeShop_Text_HowDoYouLikeNewBicycle
	release
	end

@ Unused
CeruleanCity_BikeShop_EventScript_NoRoomForBicycle:: @ 816AC62
	msgbox CeruleanCity_BikeShop_Text_MakeRoomForBicycle
	release
	end

CeruleanCity_BikeShop_EventScript_Woman:: @ 816AC6C
	msgbox CeruleanCity_BikeShop_Text_CityBikeGoodEnoughForMe, MSGBOX_NPC
	end

CeruleanCity_BikeShop_EventScript_Youngster:: @ 816AC75
	lock
	faceplayer
	goto_if_set FLAG_GOT_BICYCLE, CeruleanCity_BikeShop_EventScript_YoungsterHaveBike
	msgbox CeruleanCity_BikeShop_Text_BikesCoolButExpensive
	release
	end

CeruleanCity_BikeShop_EventScript_YoungsterHaveBike:: @ 816AC8A
	msgbox CeruleanCity_BikeShop_Text_WowYourBikeIsCool
	release
	end

CeruleanCity_BikeShop_EventScript_Bicycle:: @ 816AC94
	msgbox CeruleanCity_BikeShop_Text_ShinyNewBicycle, MSGBOX_SIGN
	end
