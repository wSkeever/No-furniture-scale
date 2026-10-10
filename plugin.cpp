#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
using namespace RE;

namespace NoFurnitureScale {
    void RemoveRaceToScaleKeyword() {
        TESDataHandler* dataHandler = TESDataHandler::GetSingleton();
        if (!dataHandler) {
            return;
        }
        BGSKeyword* raceToScaleKeyword = TESForm::LookupByID<BGSKeyword>(0xFD0E1);
        if (!raceToScaleKeyword) {
            return;
        }
        auto forms = dataHandler->GetFormArray<RE::TESFurniture>();
        for (auto* form : forms) {
            if (form) {
                form->RemoveKeyword(raceToScaleKeyword);
            }
        }
    }

    SKSEPluginLoad(const SKSE::LoadInterface* skse) {
        SKSE::Init(skse);
        SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* message) {
            if (message->type == SKSE::MessagingInterface::kDataLoaded) {
                RemoveRaceToScaleKeyword();
            }
        });

        return true;
    }
}