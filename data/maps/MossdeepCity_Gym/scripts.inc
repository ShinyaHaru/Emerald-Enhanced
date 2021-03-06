MossdeepCity_Gym_MapScripts:: @ 8220800
	.byte 0

MossdeepCity_Gym_EventScript_TateAndLiza:: @ 8220898
	lock
	faceplayer
	setflag FLAG_RYU_IN_MOSSDEEP_GYM
	setflag FLAG_RYU_BOSS_SCALE
	special checkbadgecount
	switch VAR_RESULT
    case 0, SABRINA1
	case 1, SABRINA1
	case 2, SABRINA1
	case 3, SABRINA2
	case 4, SABRINA2
	case 5, SABRINA3
	case 6, SABRINA3
	case 7, SABRINA4
	case 8, SABRINA4
	end

MDG_Reset::
	setvar VAR_TEMP_8, 7
	special checkbadgecount
	compare VAR_RESULT, 8
	call_if_eq RyuTier8GymMegaStoneReward
	setflag FLAG_BADGE07_GET
	setflag FLAG_DEFEATED_MOSSDEEP_GYM
	cleartrainerflag TRAINER_TATE_AND_LIZA_1
	cleartrainerflag TRAINER_TATE_AND_LIZA_2
	cleartrainerflag TRAINER_TATE_AND_LIZA_3
	cleartrainerflag TRAINER_TATE_AND_LIZA_4
	cleartrainerflag TRAINER_TATE_AND_LIZA_SINGLE
	clearflag FLAG_RYU_BOSS_SCALE
	clearflag FLAG_RYU_IN_MOSSDEEP_GYM
	goto_if_set FLAG_RYU_HARDCORE_MODE, RyuScripts_HardcoreGymReward
	call_if_set FLAG_RYU_NUZLOCKEMODE, RyuHealedGym
	call_if_unset FLAG_RYU_GYM7HANDOUT, RyuGymItemReward7
	release
	end

SABRINA1::
	trainerbattle_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaPreBattle, MossdeepCity_Gym_Text_TateAndLizaDefeat, MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons, MDG_Reset, NO_MUSIC
	release
	end

SABRINA2::
	trainerbattle_double TRAINER_TATE_AND_LIZA_2, MossdeepCity_Gym_Text_TateAndLizaPreBattle, MossdeepCity_Gym_Text_TateAndLizaDefeat, MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons, MDG_Reset, NO_MUSIC
	release
	end

SABRINA3::
	trainerbattle_double TRAINER_TATE_AND_LIZA_3, MossdeepCity_Gym_Text_TateAndLizaPreBattle, MossdeepCity_Gym_Text_TateAndLizaDefeat, MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons, MDG_Reset, NO_MUSIC
	release
	end

SABRINA4::
	goto_if_set FLAG_RYU_HAS_FOLLOWER, MG_FollowerMatch
	goto_if_set FLAG_RYU_DS_HAS_PARTNER, MG_PartnerQuery
	trainerbattle_double TRAINER_TATE_AND_LIZA_4, MossdeepCity_Gym_Text_TateAndLizaPreBattle, MossdeepCity_Gym_Text_TateAndLizaDefeat, MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons, MDG_Reset, NO_MUSIC
	release
	end
	
MG_PartnerQuery::
    msgbox RyuPartnerMultiText MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq MG_RelDialog
	goto MG_NoRelGymBattle
	return
	
	
MG_RelDialog::
	call RyuPartnerBattleMultichoice
	compare VAR_0x8008, TRAINER_REL_SHELLY
	goto_if_eq MG_GymBattleIntroShelly
	compare VAR_0x8008, TRAINER_REL_DAWN
	goto_if_eq MG_GymBattleIntroDawn
	compare VAR_0x8008, TRAINER_REL_BRENDAN
	goto_if_eq MG_GymBattleIntroBrendan
	compare VAR_0x8008, TRAINER_REL_LANA
	goto_if_eq MG_GymBattleIntroLana
	compare VAR_0x8008, TRAINER_REL_LANETTE
	goto_if_eq MG_GymBattleIntroLanette
	compare VAR_0x8008, TRAINER_REL_COURTNEY_2
	goto_if_eq MG_GymBattleIntroCourtney
	compare VAR_0x8008, TRAINER_REL_NURSE
	goto_if_eq MG_GymBattleIntroJoy
	goto MG_NoRelGymBattle
	
MG_NoRelGymBattle::
	trainerbattle_double TRAINER_TATE_AND_LIZA_4, MossdeepCity_Gym_Text_TateAndLizaPreBattle, MossdeepCity_Gym_Text_TateAndLizaDefeat, MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons, MDG_Reset, NO_MUSIC
	release
	end

MG_FollowerMatch::
	msgbox MossdeepCity_Gym_Text_TateAndLizaPreBattle
	closemessage
	call RyuFollowerAllySelector
	choose_mons
	compare VAR_RESULT, FALSE
	goto_if_eq MG_ChooseValidMons
	multi_2_vs_1 TRAINER_TATE_AND_LIZA_SINGLE, MossdeepCity_Gym_Text_TateAndLizaDefeat, VAR_0x8008, VAR_0x8009
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Ryu_PlayerLostTheGame
	goto MG_Reset
	end
	
MG_NoRelationship1::
	msgbox Ryu_NOREL MSGBOX_DEFAULT
	closemessage
	goto MG_RelDialog
	
MG_GymBattleIntroShelly::
	msgbox Ryu_PlayerCalledShelly MSGBOX_DEFAULT
	closemessage
	delay 30
	goto_if_unset FLAG_RYU_DS_SHELLY_PARTNERS, MG_NoRelationship1
	addobject 38
	playse SE_TK_WARPIN
	applymovement 38, MG_PartnerEnter
	waitmovement 0
	msgbox MG_SHELLY_INTRO MSGBOX_DEFAULT
	goto MG_AltGymBattle
	
MG_GymBattleIntroDawn::
	goto_if_unset FLAG_RYU_DS_DAWN_PARTNERS, MG_NoRelationship1
	msgbox Ryu_PlayerCalledDawn MSGBOX_DEFAULT
	closemessage
	delay 30
	addobject 39
	playse SE_TK_WARPIN
	applymovement 39, MG_PartnerEnter
	waitmovement 0
	msgbox MG_DAWN_INTRO MSGBOX_DEFAULT
	goto MG_AltGymBattle
	
MG_GymBattleIntroLana::
	goto_if_unset FLAG_RYU_DS_LEAF_PARTNERS, MG_NoRelationship1
	msgbox Ryu_PlayerCalledLana MSGBOX_DEFAULT
	closemessage
	delay 30
	addobject 41
	playse SE_TK_WARPIN
	applymovement 41, MG_PartnerEnter
	waitmovement 41
	msgbox MG_LEAF_INTRO MSGBOX_DEFAULT
	goto MG_AltGymBattle
	
MG_GymBattleIntroLanette::
	goto_if_unset FLAG_RYU_DS_LANETTE_PARTNERS, MG_NoRelationship1
	msgbox Ryu_PlayerCalledLanette MSGBOX_DEFAULT
	closemessage
	delay 30
	addobject 42
	playse SE_TK_WARPIN
	applymovement 42, MG_PartnerEnter
	waitmovement 42
	msgbox MG_LANETTE_INTRO MSGBOX_DEFAULT
	goto MG_AltGymBattle
	
MG_GymBattleIntroBrendan::
	goto_if_unset FLAG_RYU_DS_BRENDAN_PARTNERS, MG_NoRelationship1
	msgbox Ryu_PlayerCalledBrendan MSGBOX_DEFAULT
	closemessage
	delay 30
	addobject 40
	playse SE_TK_WARPIN
	applymovement 40, MG_PartnerEnter
	waitmovement 0
	msgbox MG_BRENDAN_INTRO MSGBOX_DEFAULT
	goto MG_AltGymBattle

MG_GymBattleIntroCourtney::
	goto_if_unset FLAG_RYU_DS_COURTNEY_PARTNERS, MG_NoRelationship1
	msgbox Ryu_PlayerCalledCourtney MSGBOX_DEFAULT
	closemessage
	delay 30
	addobject 43
	playse SE_DOOR
	applymovement 43, MG_PartnerEnter
	waitmovement 0
	msgbox MG_COURTNEY_INTRO MSGBOX_DEFAULT
	goto MG_AltGymBattle

MG_GymBattleIntroJoy::
	goto_if_unset FLAG_RYU_DS_JOY_PARTNERS, MG_NoRelationship1
	msgbox Ryu_PlayerCalledJoy MSGBOX_DEFAULT
	closemessage
	delay 30
	addobject 44
	playse SE_DOOR
	applymovement 44, MG_PartnerEnter
	waitmovement 0
	msgbox MG_JOY_INTRO MSGBOX_DEFAULT
	goto MG_AltGymBattle
	
MG_AltGymBattle::
	msgbox MG_PreBattleText MSGBOX_DEFAULT
	choose_mons
	compare VAR_RESULT, FALSE
	goto_if_eq MG_ChooseValidMons
	multi_2_vs_1 TRAINER_TATE_AND_LIZA_SINGLE, MG_DefeatText, VAR_0x8008, VAR_0x8009
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Ryu_PlayerLostTheGame
	delay 10
	goto MG_GymBattleEnd
	
MG_ChooseValidMons::
	msgbox EGC_NeedToChoose
	closemessage
	goto_if_set FLAG_RYU_HAS_FOLLOWER, MG_FollowerMatch
	goto MG_AltGymBattle
	
MG_GymBattleEnd::
	compare VAR_0x8008, TRAINER_REL_DAWN
	goto_if_eq MG_GymBattleEndDawn
	compare VAR_0x8008, TRAINER_REL_SHELLY
	goto_if_eq MG_GymBattleEndShelly
	compare VAR_0x8008, TRAINER_REL_BRENDAN
	goto_if_eq MG_GymBattleEndBrendan
	compare VAR_0x8008, TRAINER_REL_LANA
	goto_if_eq MG_GymBattleEndLana
	compare VAR_0x8008, TRAINER_REL_LANETTE
	goto_if_eq MG_GymBattleEndLanette
	compare VAR_0x8008, TRAINER_REL_COURTNEY_2
	goto_if_eq MG_GymBattleEndCourtney
	release
	end
	
MG_GymBattleEndShelly::
	msgbox MG_ShellyGymBattleComplete MSGBOX_DEFAULT
	closemessage
	applymovement 38, MG_PartnerExit
	waitmovement 0
	playse SE_TK_WARPOUT
	removeobject 38
	goto MDG_Reset
	release
	end
	
MG_GymBattleEndDawn::
	msgbox MG_DawnGymBattleComplete MSGBOX_DEFAULT
	closemessage
	applymovement 39, MG_PartnerExit
	waitmovement 0
	playse SE_TK_WARPOUT
	removeobject 39
	goto MDG_Reset
	release
	end
	
MG_GymBattleEndLana::
	msgbox MG_LanaGymBattleComplete MSGBOX_DEFAULT
	closemessage
	applymovement 41, MG_PartnerExit
	waitmovement 41
	playse SE_TK_WARPOUT
	removeobject 41
	goto MDG_Reset
	release
	end
	
MG_GymBattleEndBrendan::
	msgbox MG_BrendanGymBattleComplete MSGBOX_DEFAULT
	closemessage
	applymovement 40, MG_PartnerExit
	waitmovement 0
	playse SE_TK_WARPOUT
	removeobject 40
	goto MDG_Reset
	release
	end
	
MG_GymBattleEndLanette::
	msgbox MG_LanetteGymBattleComplete MSGBOX_DEFAULT
	closemessage
	applymovement 42, MG_PartnerExit
	waitmovement 42
	playse SE_TK_WARPOUT
	removeobject 42
	goto MDG_Reset
	release
	end

MG_GymBattleEndCourtney::
	delay 15
	playmoncry SPECIES_MIGHTYENA, 0
	waitmoncry
	msgbox MG_CourtneyGymBattleComplete MSGBOX_DEFAULT
	closemessage
	applymovement 43, MG_PartnerExit
	waitmovement 43
	playse SE_DOOR
	removeobject 43
	goto MG_Reset
	release
	end

MG_GymBattleEndJoy::
	msgbox MG_JoyGymBattleComplete MSGBOX_DEFAULT
	closemessage
	applymovement 44, MG_PartnerExit
	waitmovement 44
	playse SE_DOOR
	removeobject 44
	goto MG_Reset
	release
	end
	
MG_SHELLY_INTRO:
    .string "{COLOR LIGHT_RED}{SHADOW RED}I've technically got an\n"
    .string "edge here, but I can't help but\l"
    .string "feel uncomfortable...$"
	
MG_DAWN_INTRO:
    .string "{COLOR LIGHT_RED}{SHADOW RED}This gym is so creepy...\n"
    .string "I'll power through it!$"
	
MG_LEAF_INTRO:
    .string "{COLOR LIGHT_RED}{SHADOW RED}Hmm, I didn't know gym leaders\n"
    .string "were allowed to be this young.\p"
    .string "Oh well, I won't be nice about it.$"

MG_LANETTE_INTRO:
    .string "{COLOR LIGHT_RED}{SHADOW RED}This will be quite the\nbout. May the smartest team win!$"

MG_BRENDAN_INTRO:
    .string "{COLOR LIGHT_RED}{SHADOW RED}Brainpower really isn't\n"
    .string "my specialty, So, you take the lead!$"

MG_COURTNEY_INTRO:
	.string "{COLOR LIGHT_RED}{SHADOW RED}No problem at all, pshychic types\ncan't stand up to my Mightyena.\pFree snack for the pupper!$"

MG_JOY_INTRO:
	.string "{COLOR LIGHT_RED}{SHADOW RED}They're so cute!\nTo think such young people\lcan be Gym Leaders!$"
	
MG_PreBattleText:
    .string "Tate: I see you levelled the\n"
	.string "playing field. Smart thinking.\p"
	.string "Liza: Our bond as twins is much\n"
	.string "stronger than yours. You don't\l"
	.string "stand a chance!$"

MG_DefeatText:
    .string "Both: How could you defeat\n"
	.string "our bond?$"
	
MG_ShellyGymBattleComplete:
    .string "{COLOR LIGHT_RED}{SHADOW RED}It worked itself out.\n"
    .string "I'm glad I had dark types with me!$"

MG_DawnGymBattleComplete:
    .string "{COLOR LIGHT_RED}{SHADOW RED} (Dawn seems a little off...)$"
	
MG_LanaGymBattleComplete:
    .string "{COLOR LIGHT_RED}{SHADOW RED}Impressive teamwork, but you\n"
	.string "should have known that the bond of\l"
	.string "love is stronger than any other.$"
	
MG_LanetteGymBattleComplete:
    .string "L{COLOR LIGHT_RED}{SHADOW RED}I had no doubts.\nLet's do this again sometime!$"

MG_BrendanGymBattleComplete:
    .string "{COLOR LIGHT_RED}{SHADOW RED}Brute strength wins again!\n"
    .string "Catch ya later, neighbor.$"

MG_CourtneyGymBattleComplete:
	.string "{COLOR LIGHT_RED}{SHADOW RED}My doggo looks very satisfied.$"

MG_JoyGymBattleComplete:
	.string "{COLOR LIGHT_RED}{SHADOW RED} $"
	
MG_PartnerEnter:
	walk_in_place_down
	walk_in_place_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_up
	walk_in_place_up
	walk_in_place_up
	step_end

MG_PartnerExit:
	walk_in_place_down
	walk_down
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_in_place_down
	step_end

MossdeepCity_Gym_EventScript_TateAndLizaDefeated:: @ 82208D1
	message MossdeepCity_Gym_Text_ReceivedMindBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_MOSSDEEP_GYM
	setflag FLAG_BADGE07_GET
	setflag FLAG_HIDE_AQUA_HIDEOUT_GRUNTS
	clearflag FLAG_HIDE_SLATEPORT_CITY_STERNS_SHIPYARD_MR_BRINEY
	setvar VAR_0x8008, 7
	call Common_EventScript_SetGymTrainers
	setvar VAR_MOSSDEEP_CITY_STATE, 1
	setflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_STEVEN
	setvar VAR_MOSSDEEP_SPACE_CENTER_STATE, 1
	call MossdeepCity_Gym_EventScript_GiveCalmMind
	closemessage
	delay 30
	playfanfare MUS_ME_TORE_EYE
	msgbox MossdeepCity_Gym_Text_RegisteredTateAndLiza, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind2:: @ 8220937
	additem ITEM_TM04
	compare VAR_RESULT, 0
	goto_if_eq Common_EventScript_ShowBagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM04
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind:: @ 822095B
	additem ITEM_TM04
	compare VAR_RESULT, 0
	goto_if_eq Common_EventScript_BagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM04
	return

MossdeepCity_Gym_EventScript_TateAndLizaRematch:: @ 822097E
	trainerbattle_rematch_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaPreRematch, MossdeepCity_Gym_Text_TateAndLizaRematchDefeat, MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons
	msgbox MossdeepCity_Gym_Text_TateAndLizaPostRematch, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_WarpToEntrance:: @ 8220AF1
	lockall
	warpmossdeepgym MAP_MOSSDEEP_CITY_GYM, 255, 7, 30
	waitstate
	releaseall
	end

MossdeepCity_Gym_EventScript_Preston:: @ 8220AFD
	trainerbattle_single TRAINER_PRESTON, MossdeepCity_Gym_Text_PrestonPreBattle, MossdeepCity_Gym_Text_PrestonDefeat
	msgbox MossdeepCity_Gym_Text_PrestonPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Virgil:: @ 8220B14
	trainerbattle_single TRAINER_VIRGIL, MossdeepCity_Gym_Text_VirgilPreBattle, MossdeepCity_Gym_Text_VirgilDefeat
	msgbox MossdeepCity_Gym_Text_VirgilPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Blake:: @ 8220B2B
	trainerbattle_single TRAINER_BLAKE, MossdeepCity_Gym_Text_BlakePreBattle, MossdeepCity_Gym_Text_BlakeDefeat
	msgbox MossdeepCity_Gym_Text_BlakePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Hannah:: @ 8220B42
	trainerbattle_single TRAINER_HANNAH, MossdeepCity_Gym_Text_HannahPreBattle, MossdeepCity_Gym_Text_HannahDefeat
	msgbox MossdeepCity_Gym_Text_HannahPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Samantha:: @ 8220B59
	trainerbattle_single TRAINER_SAMANTHA, MossdeepCity_Gym_Text_SamanthaPreBattle, MossdeepCity_Gym_Text_SamanthaDefeat
	msgbox MossdeepCity_Gym_Text_SamanthaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Maura:: @ 8220B70
	trainerbattle_single TRAINER_MAURA, MossdeepCity_Gym_Text_MauraPreBattle, MossdeepCity_Gym_Text_MauraDefeat
	msgbox MossdeepCity_Gym_Text_MauraPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Sylvia:: @ 8220B87
	trainerbattle_single TRAINER_SYLVIA, MossdeepCity_Gym_Text_SylviaPreBattle, MossdeepCity_Gym_Text_SylviaDefeat
	msgbox MossdeepCity_Gym_Text_SylviaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nate:: @ 8220B9E
	trainerbattle_single TRAINER_NATE, MossdeepCity_Gym_Text_NatePreBattle, MossdeepCity_Gym_Text_NateDefeat
	msgbox MossdeepCity_Gym_Text_NatePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Macey:: @ 8220BB5
	trainerbattle_single TRAINER_MACEY, MossdeepCity_Gym_Text_MaceyPreBattle, MossdeepCity_Gym_Text_MaceyDefeat
	msgbox MossdeepCity_Gym_Text_MaceyPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Clifford:: @ 8220BCC
	trainerbattle_single TRAINER_CLIFFORD, MossdeepCity_Gym_Text_CliffordPreBattle, MossdeepCity_Gym_Text_CliffordDefeat
	msgbox MossdeepCity_Gym_Text_CliffordPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nicholas:: @ 8220BE3
	trainerbattle_single TRAINER_NICHOLAS, MossdeepCity_Gym_Text_NicholasPreBattle, MossdeepCity_Gym_Text_NicholasDefeat
	msgbox MossdeepCity_Gym_Text_NicholasPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Kathleen:: @ 8220BFA
	trainerbattle_single TRAINER_KATHLEEN, MossdeepCity_Gym_Text_KathleenPreBattle, MossdeepCity_Gym_Text_KathleenDefeat
	msgbox MossdeepCity_Gym_Text_KathleenPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_GymGuide:: @ 8220C11
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MOSSDEEP_GYM, MossdeepCity_Gym_EventScript_GymGuidePostVictory
	msgbox MossdeepCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_GymGuidePostVictory:: @ 8220C26
	msgbox MossdeepCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_LeftGymStatue:: @ 8220C33
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_RightGymStatue:: @ 8220C43
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_GymStatueCertified:: @ 8220C53
	msgbox MossdeepCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_GymStatue:: @ 8220C5D
	msgbox MossdeepCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_YellowFloorSwitch:: @ 8220C67
	playse SE_MU_PACHI
	waitse
	playse SE_TU_SAA
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 0
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_BlueFloorSwitch:: @ 8220C7D
	playse SE_MU_PACHI
	waitse
	playse SE_TU_SAA
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 1
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_GreenFloorSwitch:: @ 8220C93
	playse SE_MU_PACHI
	waitse
	playse SE_TU_SAA
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 2
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_PurpleFloorSwitch:: @ 8220CA9
	playse SE_MU_PACHI
	waitse
	playse SE_TU_SAA
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 3
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_RedFloorSwitch:: @ 8220CBF
	playse SE_MU_PACHI
	waitse
	playse SE_TU_SAA
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 4
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_Text_GymGuideAdvice: @ 8220CD5
	.string "Yo, how's it going, Champion-bound\n"
	.string "{PLAYER}?\p"
	.string "The Gym Leaders here use\n"
	.string "PSYCHIC-type Pokémon.\p"
	.string "If you go up against them with\n"
	.string "FIGHTING- or POISON-type Pokémon,\l"
	.string "they'll inflict horrible damage!\p"
	.string "Plus, they'll come at you with\n"
	.string "outstanding combination attacks.\p"
	.string "If you want to win, you'll need to show\n"
	.string "them how tight you are with your\l"
	.string "Pokémon. Go for it!$"

MossdeepCity_Gym_Text_GymGuidePostVictory: @ 8220E2A
	.string "Wow, you're astounding!\n"
	.string "You're one great Trainer!$"

MossdeepCity_Gym_Text_PrestonPreBattle: @ 8220E5C
	.string "Battles hinge on the strength of your\n"
	.string "spirit! The weak-spirited will never win!$"

MossdeepCity_Gym_Text_PrestonDefeat: @ 8220EAC
	.string "I lost!\n"
	.string "I must temper my spirit again!$"

MossdeepCity_Gym_Text_PrestonPostBattle: @ 8220ED3
	.string "The indecisive lose.\n"
	.string "That's my warning to you.$"

MossdeepCity_Gym_Text_VirgilPreBattle: @ 8220F02
	.string "Let me see your talent!$"

MossdeepCity_Gym_Text_VirgilDefeat: @ 8220F1A
	.string "You possess spectacular talent!$"

MossdeepCity_Gym_Text_VirgilPostBattle: @ 8220F3A
	.string "If there are prodigies in the world,\n"
	.string "then our Gym Leaders are them!\p"
	.string "However, you may be even more talented\n"
	.string "than them…$"

MossdeepCity_Gym_Text_BlakePreBattle: @ 8220FB0
	.string "Fufufufu… Watch me levitate a POKé\n"
	.string "Ball telekinetically!\p"
	.string "Wrooooooooaaaar!\n"
	.string "… … … … … … …\p"
	.string "Sometimes, I'm out of sync…$"

MossdeepCity_Gym_Text_BlakeDefeat: @ 8221024
	.string "My Pokémon battling skills are out\n"
	.string "of sync, too!$"

MossdeepCity_Gym_Text_BlakePostBattle: @ 8221055
	.string "A Poké ball was too heavy to lift\n"
	.string "psychically. But this dust bunny…\p"
	.string "Whoooooooooooooooh!\n"
	.string "… … … … … …\p"
	.string "No, I'm not cheating!\n"
	.string "I didn't blow on it! Honestly!$"

MossdeepCity_Gym_Text_HannahPreBattle: @ 82210EE
	.string "When you lose to me, don't be too hard\n"
	.string "on yourself.\p"
	.string "It's not that you're weak--I'm just\n"
	.string "too strong!$"

MossdeepCity_Gym_Text_HannahDefeat: @ 8221152
	.string "You're just too strong!$"

MossdeepCity_Gym_Text_HannahPostBattle: @ 822116A
	.string "I'm not going to get down on myself for\n"
	.string "losing. I just need to train harder.\p"
	.string "Positive thinking--that's my strong\n"
	.string "point!$"

MossdeepCity_Gym_Text_SamanthaPreBattle: @ 82211E2
	.string "I see it…\n"
	.string "I see your future…\p"
	.string "If you can beat me, I will tell you\n"
	.string "your future!$"

MossdeepCity_Gym_Text_SamanthaDefeat: @ 8221230
	.string "I surrender!$"

MossdeepCity_Gym_Text_SamanthaPostBattle: @ 822123D
	.string "You will wage a terrifically intense\n"
	.string "battle with our Gym Leaders…\p"
	.string "The result…\n"
	.string "You won't hear it from me!$"

MossdeepCity_Gym_Text_MauraPreBattle: @ 82212A6
	.string "The roads you have traveled…\n"
	.string "What you have experienced…\p"
	.string "Come at me with everything you've\n"
	.string "learned!$"

MossdeepCity_Gym_Text_MauraDefeat: @ 8221309
	.string "You've traveled a path of greatness!$"

MossdeepCity_Gym_Text_MauraPostBattle: @ 822132E
	.string "A bright future awaits those who have\n"
	.string "worked diligently.\p"
	.string "For those who lazed idly, there is\n"
	.string "only despair at the end.\p"
	.string "What goes around comes around…$"

MossdeepCity_Gym_Text_SylviaPreBattle: @ 82213C2
	.string "Even at the risk of life, I will win\n"
	.string "this battle!$"

MossdeepCity_Gym_Text_SylviaDefeat: @ 82213F4
	.string "What you do…\n"
	.string "It horrifies me…$"

MossdeepCity_Gym_Text_SylviaPostBattle: @ 8221412
	.string "How dare you beat me…\p"
	.string "It won't be my fault if something\n"
	.string "horrible befalls you…$"

MossdeepCity_Gym_Text_NatePreBattle: @ 8221460
	.string "Hohoho.\p"
	.string "You need me to show you how tenacious\n"
	.string "the Psychic type can be.$"

MossdeepCity_Gym_Text_NateDefeat: @ 82214A7
	.string "Oh! My, my!\n"
	.string "Your battle style is fantastic!$"

MossdeepCity_Gym_Text_NatePostBattle: @ 82214D3
	.string "I… I don't let defeat rattle m-me,\n"
	.string "however b-badly.$"

MossdeepCity_Gym_Text_KathleenPreBattle: @ 8221507
	.string "Let me show you a perfectly awful,\n"
	.string "horrifying time!$"

MossdeepCity_Gym_Text_KathleenDefeat: @ 822153B
	.string "N-nooooo!$"

MossdeepCity_Gym_Text_KathleenPostBattle: @ 8221545
	.string "Your vitality is contagious!\n"
	.string "Get away from me quickly!$"

MossdeepCity_Gym_Text_CliffordPreBattle: @ 822157C
	.string "I may be past my prime, but I suggest\n"
	.string "you not patronize me.$"

MossdeepCity_Gym_Text_CliffordDefeat: @ 82215B8
	.string "Ah, you overflow with the power\n"
	.string "of youth!$"

MossdeepCity_Gym_Text_CliffordPostBattle: @ 82215E2
	.string "It seems that I could not overcome\n"
	.string "your youthful energy.$"

MossdeepCity_Gym_Text_MaceyPreBattle: @ 822161B
	.string "You're not getting through to the end!\n"
	.string "Not if I can help it!$"

MossdeepCity_Gym_Text_MaceyDefeat: @ 8221658
	.string "How could you be so ludicrously\n"
	.string "strong?$"

MossdeepCity_Gym_Text_MaceyPostBattle: @ 8221680
	.string "Humph! You may be strong, but you're\n"
	.string "not suitable for the Psychic type!\p"
	.string "The way you battle is somehow brutal!$"

MossdeepCity_Gym_Text_NicholasPreBattle: @ 82216EE
	.string "Wroooar! Have a taste of my super\n"
	.string "Pokémon hard-battling power!$"

MossdeepCity_Gym_Text_NicholasDefeat: @ 822172D
	.string "Oh!\n"
	.string "Done in!$"

MossdeepCity_Gym_Text_NicholasPostBattle: @ 822173A
	.string "All right! I think I'll develop a special\n"
	.string "invincible Pokémon power next.$"

MossdeepCity_Gym_Text_TateAndLizaPreBattle: @ 8221783
	.string "Tate: Hehehe… Were you surprised?\p"
	.string "Liza: Fufufu… Were you surprised?\p"
	.string "Tate: That there are two Gym Leaders?\n"
	.string "Liza: That there are two Gym Leaders?\p"
	.string "Tate: We're twins!\n"
	.string "Liza: We're twins!\p"
	.string "Tate: We don't need to talk because…\n"
	.string "Liza: We can each determine what…\p"
	.string "Tate: The other is thinking…\n"
	.string "Liza: All in our minds!\p"
	.string "Tate: This combination of ours…\n"
	.string "Liza: Can you beat it?$"

MossdeepCity_Gym_Text_TateAndLizaDefeat: @ 82218EC
	.string "Tate: What?! Our combination…\n"
	.string "Liza: Was shattered!\p"
	.string "Tate: It can't be helped. You've won…\n"
	.string "Liza: So, in recognition, take this.$"

MossdeepCity_Gym_Text_ReceivedMindBadge: @ 822196A
	.string "{PLAYER} received the MIND badge\n"
	.string "from Tate and Liza.$"

MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis: @ 8221999
	.string "Tate: The Mind badge enhances the\n"
	.string "SP. Atk and SP. Def of Pokémon.\p"
	.string "Liza: It also lets you use the HM move\n"
	.string "Dive outside of battle.\p"
	.string "Tate: You should also take this, too.$"

MossdeepCity_Gym_Text_ExplainCalmMind: @ 8221A40
	.string "Tate: That TM04 contains…\n"
	.string "Liza: Calm Mind!\p"
	.string "Tate: It raises SP. Atk and…\n"
	.string "Liza: It raises SP. Def!\p"
	.string "Tate: It's a move that's perfect…\n"
	.string "Liza: For Psychic Pokémon!\p"
	.string "… … … … … …$"

MossdeepCity_Gym_Text_RegisteredTateAndLiza: @ 8221AEA
	.string "Registered Gym Leaders Tate & Liza\n"
	.string "in the Pokénav.$"

MossdeepCity_Gym_Text_TateAndLizaPostBattle: @ 8221B1D
	.string "Tate: Looks like the bond between you\n"
	.string "and your Pokémon is far stronger than\l"
	.string "the bond that we share as twins.\p"
	.string "Liza: You will become even stronger!\n"
	.string "We've battled you, so we know.$"

MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons: @ 8221BCE
	.string "Tate: Hehehe… Were you surprised?\p"
	.string "Liza: That there are two Gym Leaders?\p"
	.string "Tate: Oops, you have only one…\n"
	.string "Liza: Pokémon that can battle.\p"
	.string "Tate: We can't battle that way!\p"
	.string "Liza: If you want to challenge us,\n"
	.string "bring some more Pokémon.$"

MossdeepCity_Gym_Text_GymStatue: @ 8221CB0
	.string "Mossdeep City Pokémon Gym$"

MossdeepCity_Gym_Text_GymStatueCertified: @ 8221CCA
	.string "Mossdeep City Pokémon Gym\p"
	.string "Liza And Tate's Certified Trainers:\n"
	.string "{PLAYER}$"

MossdeepCity_Gym_Text_TateAndLizaPreRematch: @ 8221D0B
	.string "Tate: Pokémon…\n"
	.string "Liza: Pokémon…\p"
	.string "Tate: By changing the party's mix…\n"
	.string "Liza: The battle style changes.\p"
	.string "Tate: But me…\n"
	.string "Liza: But me…\p"
	.string "Tate: I'll always be with Liza!\n"
	.string "Liza: I'll always be with Tate!\p"
	.string "Tate: Our combination…\n"
	.string "Liza: We'll show you again and again!$"

MossdeepCity_Gym_Text_TateAndLizaRematchDefeat: @ 8221E05
	.string "Tate: You and your Pokémon…\n"
	.string "Liza: It's as if you were siblings!$"

MossdeepCity_Gym_Text_TateAndLizaPostRematch: @ 8221E45
	.string "Tate: You can knock us down,\n"
	.string "but we'll never stay down!\p"
	.string "Liza: Because the two of us,\n"
	.string "we always support each other!$"

MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons: @ 8221EB8
	.string "Tate: You're back again…\n"
	.string "Liza: You're back again…\p"
	.string "Tate: To give us a rematch.\n"
	.string "Liza: To give us a rematch.\p"
	.string "Tate: But…\n"
	.string "Liza: For our match…\p"
	.string "Tate: You brought just one Pokémon!\n"
	.string "Liza: You brought just one Pokémon!\p"
	.string "Tate: We need you to bring at least…\n"
	.string "Liza: Two Pokémon when you come back.$"
