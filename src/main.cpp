#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/GameStatsManager.hpp>
#include <Geode/modify/LevelPage.hpp>
#include <Geode/modify/GameManager.hpp>

static bool isCheckingLocked = false;

class $modify(GameStatsManager) {
	int getStat(char const* p0) {
		if (isCheckingLocked) {
			return 999;
		}
		return GameStatsManager::getStat(p0);
	}
};
class $modify(LevelPage) {
	void onPlay(cocos2d::CCObject * sender) {
		isCheckingLocked = true;
		LevelPage::onPlay(sender);
		isCheckingLocked = false;
	}
};

// In case LevelPage::onPlay errors and doesnt change isCheckingLocked back to false.
class $modify(GameManager) {
	virtual void update(float p0) {
		isCheckingLocked = false;
		GameManager::update(p0);
	}
};