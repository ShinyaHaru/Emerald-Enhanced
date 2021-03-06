EverGrandeCity_SidneysRoom_MapScripts:: @ 8227F01
	map_script ON_LOAD , EverGrandeCity_SidneysRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_SidneysRoom_OnWarp
	map_script ON_TRANSITION, EverGrandeCity_SidneysRoom_OnTransition
	map_script ON_FRAME, EverGrandeCity_SidneysRoom_OnFrame
	.byte 0

EverGrandeCity_SidneysRoom_OnTransition: @ 8227F16
	setflag FLAG_MET_SCOTT_IN_EVERGRANDE
	setflag FLAG_HIDE_EVER_GRANDE_POKEMON_CENTER_1F_SCOTT
	end

EverGrandeCity_SidneysRoom_OnLoad: @ 8227F1D
	call_if_set FLAG_DEFEATED_ELITE_4_SIDNEY, EverGrandeCity_SidneysRoom_EventScript_ResetAdvanceToNextRoom
	compare VAR_ELITE_4_STATE, 1
	call_if_eq EverGrandeCity_SidneysRoom_EventScript_CloseDoor
	end
	
EGC_SkipE4::
	special RyuDevCheck
	compare VAR_RESULT, 69
	goto_if_ne ryu_end
	warpsilent MAP_EVER_GRANDE_CITY_HALL4, 255, 5, 4
	release
	end

EverGrandeCity_SidneysRoom_EventScript_ResetAdvanceToNextRoom:: @ 8227F32
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_SidneysRoom_EventScript_CloseDoor:: @ 8227F38
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_SidneysRoom_OnWarp: @ 8227F3E
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_SidneysRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_SidneysRoom_EventScript_PlayerTurnNorth:: @ 8227F48
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_SidneysRoom_OnFrame: @ 8227F4D
	map_script_2 VAR_ELITE_4_STATE, 0, EverGrandeCity_SidneysRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_SidneysRoom_EventScript_WalkInCloseDoor:: @ 8227F57
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 1
	releaseall
	end

EverGrandeCity_SidneysRoom_EventScript_Sidney:: @ 8227F64
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_SIDNEY, EverGrandeCity_SidneysRoom_EventScript_PostBattleSpeech
	playbgm MUS_SITENNOU, 0
	msgbox EverGrandeCity_SidneysRoom_Text_PreBattleSpeech, MSGBOX_DEFAULT
	setvar VAR_RYU_AUTOSCALE_MIN_LEVEL, 82
	setflag FLAG_RYU_BOSS_SCALE
	setflag FLAG_RYU_WAYSTONE_DISABLED
	goto_if_set FLAG_SYS_GAME_CLEAR, EGC_AltSidney
	goto_if_set FLAG_RYU_HAS_FOLLOWER, EGC_FollowerSidney
	trainerbattle_no_intro TRAINER_SIDNEY, EverGrandeCity_SidneysRoom_Text_Defeat
	goto EverGrandeCity_SidneysRoom_EventScript_Defeated
	end

EGC_FollowerSidney::
	call RyuFollowerAllySelector
	choose_mons
	compare VAR_RESULT, FALSE
	goto_if_eq EGC_ChooseValidMons
	multi_2_vs_1 TRAINER_SIDNEY, EverGrandeCity_SidneysRoom_Text_Defeat, VAR_0x8008, VAR_0x8009
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Ryu_PlayerLostTheGame
	goto EverGrandeCity_SidneysRoom_EventScript_Defeated
	end
	
EGC_ChooseValidMons::
	msgbox EGC_NeedToChoose
	closemessage
	goto_if_set FLAG_TEMP_B, EGC_FollowerSidneyRematch
	goto EGC_FollowerSidney
	
EGC_NeedToChoose:
	.string "You must make a valid selection.$"
	
EGC_FollowerSidneyRematch::
	setflag FLAG_TEMP_B
	call RyuFollowerAllySelector
	choose_mons
	compare VAR_RESULT, FALSE
	goto_if_eq EGC_ChooseValidMons
	multi_2_vs_1 TRAINER_SIDNEY, EverGrandeCity_SidneysRoom_Text_Defeat, VAR_0x8008, VAR_0x8009
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Ryu_PlayerLostTheGame
	goto Ryu_CheckForMega
	goto EverGrandeCity_SidneysRoom_EventScript_Defeated
	end

EGC_AltSidney::
	goto_if_set FLAG_RYU_HAS_FOLLOWER, EGC_FollowerSidneyRematch
	trainerbattle_no_intro TRAINER_SIDNEY_REMATCH, EverGrandeCity_SidneysRoom_Text_Defeat
	goto Ryu_CheckForMega
	end

Ryu_CheckForMega::
	goto_if_set FLAG_RYU_SIDNEY_MEGA EverGrandeCity_SidneysRoom_EventScript_Defeated
	msgbox SidneyAbsolGiftMsg
	additem ITEM_ABSOLITE
	setflag FLAG_RYU_SIDNEY_MEGA
	goto EverGrandeCity_SidneysRoom_EventScript_Defeated

SidneyAbsolGiftMsg::
	.string "You've got talent, kid. Take\nthis gift from me, You should\lbe able to put it to good use!$"


EverGrandeCity_SidneysRoom_EventScript_PostBattleSpeech:: @ 8227F8B
	msgbox EverGrandeCity_SidneysRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_SidneysRoom_EventScript_Defeated:: @ 8227F95
	setflag FLAG_DEFEATED_ELITE_4_SIDNEY
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_SidneysRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	call Ryu_CheckForPartnerReward
	release
	end

EGC_SidneyPrebattle:
	.string "Testing first Null$"

EverGrandeCity_SidneysRoom_Text_PreBattleSpeech: @ 8227FA7
	.string "Welcome, challenger!\n"
	.string "I'm Sidney of the Elite Four.\p"
	.string "I like that look you're giving me.\n"
	.string "I guess you'll give me a good match.\l"
	.string "That's good! Looking real good!\p"
	.string "All right! You and me, let's enjoy\n"
	.string "a battle that can only be staged\l"
	.string "here in the Pokémon League!$"

EverGrandeCity_SidneysRoom_Text_Defeat: @ 82280A2
	.string "Well, how do you like that? I lost!\n"
	.string "Eh, it was fun, so it doesn't matter.$"

EverGrandeCity_SidneysRoom_Text_PostBattleSpeech: @ 82280EC
	.string "Well, listen to what this loser has\n"
	.string "to say.\p"
	.string "You've got what it takes to go far.\n"
	.string "Now, go on to the next room and enjoy\l"
	.string "your next battle!$"

