#include "GSPlay.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSSetting.h"
#include "GSInfo.h"
#include "GSRoundOption.h"

#include "GameStatebase.h"

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateTypes stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case STATE_INVALID:
		break;
	case STATE_Intro:
		gs = std::make_shared<GSIntro>();
		break;
	case STATE_Menu:
		gs = std::make_shared<GSMenu>();
		break;
	case STATE_Play:
		gs = std::make_shared<GSPlay>();
		break;
	case STATE_Setting:
		gs = std::make_shared<GSSetting>();
		break;
	case STATE_Info:
		gs = std::make_shared<GSInfo>();
		break;
	case STATE_RoundOption:
		gs = std::make_shared<GSRoundOption>();
		break;
	default:
		break;
	}
	return gs;
}