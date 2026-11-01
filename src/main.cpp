#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(HelloMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		auto sprite = CCSprite::create("hello-btn.png"_spr);
		auto btn = CCMenuItemSpriteExtra::create(
			sprite, this, menu_selector(HelloMenuLayer::onHello)
		);
		btn->setID("hello-button"_spr);

		if (auto menu = this->getChildByID("bottom-menu")) {
			menu->addChild(btn);
			menu->updateLayout();
		}
		return true;
	}

	void onHello(CCObject*) {
		auto mod = Mod::get();
		auto clicks = mod->getSavedValue<int>("clicks", 0) + 1;
		mod->setSavedValue<int>("clicks", clicks);

		auto msg = mod->getSettingValue<std::string>("message");
		FLAlertLayer::create(
			"Hello Button",
			fmt::format("{}\n\nYou've pressed this {} time(s).", msg, clicks),
			"OK"
		)->show();
	}
};
